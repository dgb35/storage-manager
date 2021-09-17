#include "storage_manager.hpp"

#include <boost/algorithm/string.hpp>

#include <cassert>
#include <fstream>
#include <utility>

StorageManager::StorageManager(fs::path storagePath) :
    _path{std::move(storagePath)}, _fileStream{}, _maxSize{16000}
{
    check_storage();
}

size_t StorageManager::count_records()
{
    size_t count = 0;

    check_storage();
    auto in = file_stream();

    std::string temp;
    while (std::getline(in, temp))
        ++count;

    in.close();

    return count;
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
        if (!fs::exists(_path.parent_path()))
        {
            fs::create_directories(_path.parent_path());
        }
        // Creating an empty file
        _fileStream.open(_path, std::ios::out);
        _fileStream.close();
    }
}

fs::path StorageManager::path() const
{
    return _path;
}

std::fstream&& StorageManager::file_stream()
{
    // Close already opened stream to avoid errors
    if (_fileStream.is_open())
        _fileStream.close();

    _fileStream.open(_path, std::ios::in | std::ios::out | std::ios::app);

    return std::move(_fileStream);
}

size_t StorageManager::storage_size()
{
    return fs::file_size(_path);
}
