#ifndef STORAGE_MANAGER_STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_STORAGE_MANAGER_HPP

#include <array>
#include <filesystem>

namespace fs = std::filesystem;


static const fs::path selLogDir = fs::current_path().root_path() / "var" / "log";
static const fs::path selLogFilename = "ipmi_sel";

class StorageManager {
public:
    explicit StorageManager(fs::path storagePath);

    void checkStorage() const;

    [[nodiscard]] fs::path getPath() const;

    [[nodiscard]] size_t countEntries() const;

    void clearStorage();

protected:
    fs::path _path;
};


#endif //STORAGE_MANAGER_STORAGE_MANAGER_HPP
