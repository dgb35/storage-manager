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

    [[nodiscard]] fs::path getPath() const;
    [[nodiscard]] std::fstream&& getFileStream();

    [[nodiscard]] size_t getStorageSize();
    [[nodiscard]] size_t countRecords();

  protected:
    std::fstream _fileStream;
    fs::path _path;
    size_t _maxSize;
};

#endif // STORAGE_MANAGER_STORAGE_MANAGER_HPP
