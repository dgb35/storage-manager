#include "storage_manager.hpp"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <example/sel_event_record.hpp>

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
    StorageManager manager(path / fileName);

    ASSERT_TRUE(fs::exists(path / fileName));
}

TEST(StorageManager, ExistAfterClear)
{
    StorageManager manager(path / fileName);
    manager.clear_storage();

    ASSERT_TRUE(fs::exists(path / fileName));
}

TEST(StorageManager, PathsMatch)
{
    StorageManager manager(path / fileName);

    ASSERT_EQ(manager.path(), path / fileName);
}

TEST(StorageManager, Streams)
{
    StorageManager manager(path / fileName);

    const SelEventRecord write{1, 2, 3, 4, 5, 6, 7, 8, {9, 10, 11}};
    SelEventRecord res1, res2;

    {
        auto write_stream_first = manager.write_binary_file_stream();
        auto write_stream_second = manager.write_binary_file_stream();

        boost::archive::binary_oarchive out_first(
            write_stream_first,
            boost::archive::no_header | boost::archive::no_tracking);

        boost::archive::binary_oarchive out_second(
            write_stream_second,
            boost::archive::no_header | boost::archive::no_tracking);

        auto fun1 = [&out_first, write]() { out_first << write; };
        auto fun2 = [&out_second, write]() { out_second << write; };

        std::thread thread1(fun1);
        std::thread thread2(fun2);

        thread1.join();
        thread2.join();
    }

    { // reading data
        auto read_stream_first = manager.read_binary_file_stream();
        boost::archive::binary_iarchive in_archive_first(
            read_stream_first,
            boost::archive::no_header | boost::archive::no_tracking);

        auto read_stream_second = manager.read_binary_file_stream();
        boost::archive::binary_iarchive in_archive_second(
            read_stream_second,
            boost::archive::no_header | boost::archive::no_tracking);

        auto fun1 = [&in_archive_first, &res1]() { in_archive_first >> res1; };
        auto fun2 = [&in_archive_second, &res2]() {
            in_archive_second >> res2;
        };

        std::thread thread1(fun1);
        std::thread thread2(fun2);

        thread1.join();
        thread2.join();
    }

    ASSERT_EQ(res1.recordID, write.recordID);
    ASSERT_EQ(res2.recordID, write.recordID);
}