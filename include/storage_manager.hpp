#ifndef STORAGE_MANAGER_STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_STORAGE_MANAGER_HPP

#include <filesystem>
#include <fstream>
#include <shared_mutex>

namespace fs = std::filesystem;

class StorageManager
{
  public:
    explicit StorageManager(fs::path storagePath);

    void check_storage();
    void clear_storage();

    [[nodiscard]] fs::path path() const;
    [[nodiscard]] size_t storage_size() const;

    [[nodiscard]] std::ofstream write_binary_file_stream();
    [[nodiscard]] std::ifstream read_binary_file_stream();

  protected:
    void initialize_storage();

  protected:
    std::shared_mutex file_mutex;

    fs::path _path;
    size_t _maxSize;
};

#endif // STORAGE_MANAGER_STORAGE_MANAGER_HPP
