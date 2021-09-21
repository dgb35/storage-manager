#include "example/sel_event_record.hpp"
#include "storage_manager.hpp"

#include <filesystem>
#include <thread>

#include "gtest/gtest.h"

namespace fs = std::filesystem;

// constants
static const auto path = fs::current_path().root_path() / "var" / "log";
static const fs::path fileName = "ipmi_sel_test";

// tests
TEST(StorageManager, FileExist)
{
    StorageManager<SelEventRecord> manager(path / fileName);
    ASSERT_TRUE(fs::exists(path / fileName));
}

TEST(StorageManager, FileExistAfterClear)
{
    StorageManager<SelEventRecord> manager(path / fileName);
    manager.clear_storage();
    ASSERT_TRUE(fs::exists(path / fileName));
}

TEST(StorageManager, PathsMatch)
{
    StorageManager<SelEventRecord> manager(path / fileName);
    ASSERT_EQ(manager.path(), path / fileName);
}