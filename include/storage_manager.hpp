#ifndef STORAGE_MANAGER_STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_STORAGE_MANAGER_HPP

#include <array>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class StorageManager {
public:
    explicit StorageManager(fs::path storagePath);

    void checkStorage();

    [[nodiscard]] fs::path getPath() const;

    [[nodiscard]] size_t countEntries();

    [[nodiscard]] std::fstream &&getFileStream();

    void clearStorage();

protected:
    std::fstream _fileStream;
    fs::path _path;
};


#endif //STORAGE_MANAGER_STORAGE_MANAGER_HPP
