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