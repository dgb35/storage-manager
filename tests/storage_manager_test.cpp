#include <filesystem>

#include "storage_manager.hpp"
#include "constants.hpp"

#include "gtest/gtest.h"

namespace fs = std::filesystem;

TEST(StorageManager, FileExist) {
    StorageManager manager(selLogDir / selLogFilename);

    ASSERT_TRUE(fs::exists(selLogDir / selLogFilename));
}

TEST(StorageManager, ExistAfterClear) {
    StorageManager manager(selLogDir / selLogFilename);
    manager.clearStorage();

    ASSERT_TRUE(fs::exists(selLogDir / selLogFilename));
}

TEST(StorageManager, PathsMatch) {
    StorageManager manager(selLogDir / selLogFilename);

    ASSERT_EQ(manager.getPath(), selLogDir / selLogFilename);
}

TEST(StorageManager, Streams) {
    StorageManager manager(selLogDir / selLogFilename);

    auto stream = manager.getFileStream();

    stream << "123";

    std::string temp;
    stream.seekg(0);
    std::getline(stream, temp);

    stream.close();

    ASSERT_EQ(temp, "123");
}