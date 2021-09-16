#include "storage_manager.hpp"

#include <boost/algorithm/string.hpp>

#include <fstream>
#include <cassert>
#include <utility>

StorageManager::StorageManager(fs::path storagePath)
        : _path{std::move(storagePath)}, _fileStream{} {
    checkStorage();
}

size_t StorageManager::countEntries() {
    size_t count = 0;

    auto in = getFileStream();

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

void StorageManager::checkStorage() {
    if (!fs::exists(_path)) {
        if (!fs::exists(_path.parent_path())) {
            fs::create_directories(_path.parent_path());
        }
        // Creating an empty file
        _fileStream.open(_path, std::ios::out);
        _fileStream.close();
    }
}

fs::path StorageManager::getPath() const {
    return _path;
}

std::fstream &&StorageManager::getFileStream() {
    if (_fileStream.is_open())
        _fileStream.close();

    _fileStream.open(_path, std::ios::in | std::ios::out | std::ios::app);

    return std::move(_fileStream);
}
