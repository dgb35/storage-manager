#include "storage_manager.hpp"

#include <boost/algorithm/string.hpp>

#include <fstream>
#include <utility>

StorageManager::StorageManager(fs::path storagePath) :
    _path{std::move(storagePath)}, _maxSize{16000}
{
    initialize_storage();
}

void StorageManager::clear_storage()
{
    fs::remove(_path);
    check_storage();
}

void StorageManager::check_storage()
{
    if (fs::exists(_path))
    {
        if (storage_size() >= _maxSize)
        {
            clear_storage();
        }
    }
    else
    {
        initialize_storage();
    }
}

fs::path StorageManager::path() const
{
    return _path;
}

std::ifstream StorageManager::read_binary_file_stream()
{
    std::shared_lock lock(file_mutex);
    std::ifstream read_stream(_path, std::ios::in | std::ios::binary);
    return read_stream;
}

std::ofstream StorageManager::write_binary_file_stream()
{
    std::unique_lock lock(file_mutex);
    std::ofstream write_stream(_path, std::ios::out | std::ios::app |
                                          std::ios::binary);
    return write_stream;
}

size_t StorageManager::storage_size() const
{
    return fs::file_size(_path);
}

void StorageManager::initialize_storage()
{
    if (!fs::exists(_path.parent_path()))
        fs::create_directories(_path.parent_path());

    // Creating an empty file
    write_binary_file_stream().close();
}
