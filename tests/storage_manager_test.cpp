#include "constants.hpp"
#include "storage_manager.hpp"

#include <filesystem>

#include "gtest/gtest.h"

namespace fs = std::filesystem;

TEST(StorageManager, FileExist)
{
    StorageManager manager(dir / file_name);

    ASSERT_TRUE(fs::exists(dir / file_name));
}

TEST(StorageManager, ExistAfterClear)
{
    StorageManager manager(dir / file_name);
    manager.clearStorage();

    ASSERT_TRUE(fs::exists(dir / file_name));
}

TEST(StorageManager, PathsMatch)
{
    StorageManager manager(dir / file_name);

    ASSERT_EQ(manager.getPath(), dir / file_name);
}

TEST(StorageManager, Streams)
{
    StorageManager manager(dir / file_name);

    auto stream = manager.getFileStream();

    stream << "123";

    std::string temp;
    stream.seekg(0);
    std::getline(stream, temp);

    stream.close();

    ASSERT_EQ(temp, "123");
}