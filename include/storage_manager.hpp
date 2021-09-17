#ifndef STORAGE_MANAGER_STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_STORAGE_MANAGER_HPP

#include <array>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class StorageManager
{
  public:
    explicit StorageManager(fs::path storagePath);

    void checkStorage();
    void clearStorage();

    [[nodiscard]] fs::path path() const;
    [[nodiscard]] std::fstream&& file_stream();

    [[nodiscard]] size_t storage_size();
    [[nodiscard]] size_t count_records();

  protected:
    std::fstream _fileStream;
    fs::path _path;
    size_t _maxSize;
};

#endif // STORAGE_MANAGER_STORAGE_MANAGER_HPP
