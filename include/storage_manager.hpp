#ifndef STORAGE_MANAGER_STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_STORAGE_MANAGER_HPP

#include "serializer.hpp"

#include <filesystem>
#include <fstream>
#include <shared_mutex>
namespace fs = std::filesystem;

template <typename Serializable>
class StorageManager
{
  public:
    explicit StorageManager(fs::path storagePath, size_t maxSize = 16000);
    virtual ~StorageManager() = default;

    void check_storage();
    virtual void clear_storage();

    [[nodiscard]] fs::path path() const;
    [[nodiscard]] size_t storage_size() const;

    virtual void add_record(Serializable object);

    [[nodiscard]] std::vector<Serializable> load_records();
    [[nodiscard]] uint16_t get_records_count() const;

  protected:
    [[nodiscard]] std::ofstream write_binary_file_stream();
    [[nodiscard]] std::ifstream read_binary_file_stream();

    void initialize_storage();
    void archive_storage();

  protected:
    Serializer<Serializable> _serializer;
    std::shared_mutex _file_mutex;
    fs::path _path;
    size_t _maxSize;

    uint16_t _current_record_count;
};

template <typename Serializable>
StorageManager<Serializable>::StorageManager(fs::path storagePath,
                                             size_t maxSize) :
    _path{std::move(storagePath)},
    _maxSize{maxSize}, _current_record_count{0}
{
    initialize_storage();
    _current_record_count = load_records().size();
}

template <typename Serializable>
void StorageManager<Serializable>::clear_storage()
{
    fs::remove(_path);
    _current_record_count = 0;
    check_storage();
}

template <typename Serializable>
void StorageManager<Serializable>::check_storage()
{
    if (fs::exists(_path))
    {
        if (storage_size() >= _maxSize)
        {
            archive_storage();
            clear_storage();
        }
    }
    else
    {
        initialize_storage();
    }
}

template <typename Serializable>
fs::path StorageManager<Serializable>::path() const
{
    return _path;
}

template <typename Serializable>
std::ifstream StorageManager<Serializable>::read_binary_file_stream()
{
    std::shared_lock lock(_file_mutex);
    std::ifstream read_stream(_path, std::ios::in | std::ios::binary);
    return read_stream;
}

template <typename Serializable>
std::ofstream StorageManager<Serializable>::write_binary_file_stream()
{
    std::unique_lock lock(_file_mutex);
    std::ofstream write_stream(_path, std::ios::out | std::ios::app |
                                          std::ios::binary);
    return write_stream;
}

template <typename Serializable>
size_t StorageManager<Serializable>::storage_size() const
{
    return fs::file_size(_path);
}

template <typename Serializable>
void StorageManager<Serializable>::initialize_storage()
{
    if (!fs::exists(_path.parent_path()))
        fs::create_directories(_path.parent_path());

    // Creating an empty file
    write_binary_file_stream().close();
}

template <typename Serializable>
void StorageManager<Serializable>::archive_storage()
{
    if (storage_size() == 0)
        return;

    size_t i = 1;
    while (true)
    {
        if (!fs::exists(path().string() + "." + std::to_string(i)))
        {
            fs::rename(_path, path().string() + "." + std::to_string(i));
            break;
        }
        ++i;
    }
}

template <typename Serializable>
void StorageManager<Serializable>::add_record(Serializable object)
{
    _serializer.save(object, write_binary_file_stream());
    ++_current_record_count;
    check_storage();
}

template <typename Serializable>
std::vector<Serializable> StorageManager<Serializable>::load_records()
{
    return _serializer.load_all(read_binary_file_stream());
}

template <typename Serializable>
uint16_t StorageManager<Serializable>::get_records_count() const
{
    return _current_record_count;
}

#endif // STORAGE_MANAGER_STORAGE_MANAGER_HPP
