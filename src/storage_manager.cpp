#include "storage_manager.hpp"

#include <boost/algorithm/string.hpp>

#include <fstream>
#include <cassert>
#include <utility>

StorageManager::StorageManager(fs::path storagePath)
        : _path{std::move(storagePath)} {
    checkStorage();
}

size_t StorageManager::countEntries() const {
    size_t count = 0;

    checkStorage();

    std::ifstream in(_path);
    if (!in.is_open())
        return -1;

    std::string temp;
    while (std::getline(in, temp))
        ++count;

    in.close();

    return count;
}

void StorageManager::clearStorage() {
    fs::remove(_path);
    checkStorage();
}

void StorageManager::checkStorage() const {
    if (!fs::exists(_path)) {
        if (!fs::exists(_path.parent_path())) {
            fs::create_directories(_path.parent_path());
        }
        std::ofstream out(_path);
        out.close();
    }
}

fs::path StorageManager::getPath() const {
    return _path;
}
