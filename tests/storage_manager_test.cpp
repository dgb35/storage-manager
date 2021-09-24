#include <example/sel/sel_event_record.hpp>
#include <example/sel/sel_storage_manager.hpp>
#include <example/sel/sel_utils.hpp>
#include <storage_manager.hpp>

#include <filesystem>
#include <thread>

#include "gtest/gtest.h"

namespace fs = std::filesystem;

// constants
static const auto path = fs::current_path().root_path() / "var" / "log";
static const auto fileName = "ipmi_sel_test";

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

TEST(SelStorageManager, DeleteFirstRecord)
{
    SelStorageManager manager(path / fileName);

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};

    manager.add_record(record_1);
    manager.add_record(record_2);

    manager.delete_record(ipmi::sel::firstEntry);

    auto entries = manager.load_records();

    ASSERT_EQ(record_2.recordID, entries.front().recordID);
}

TEST(SelStorageManager, DeleteLastRecord)
{
    SelStorageManager manager(path / fileName);

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};

    manager.add_record(record_1);
    manager.add_record(record_2);

    manager.delete_record(ipmi::sel::lastEntry);

    auto entries = manager.load_records();

    ASSERT_EQ(record_2.recordID, entries.front().recordID);
}

TEST(SelStorageManager, DeleteRecordById)
{
    SelStorageManager manager(path / fileName);

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};
    SelEventRecord record_3{3};

    manager.add_record(record_1);
    manager.add_record(record_2);
    manager.add_record(record_3);

    manager.delete_record(2);

    auto entries = manager.load_records();

    ASSERT_EQ(record_1.recordID, entries.front().recordID);
    ASSERT_EQ(record_3.recordID, entries.back().recordID);
}

TEST(SelStorageManager, GetFirstRecord)
{
    SelStorageManager manager(path / fileName);

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};

    manager.add_record(record_1);
    manager.add_record(record_2);

    manager.get_record(std::numeric_limits<uint16_t>::max());

    auto record = manager.get_record(ipmi::sel::firstEntry);

    ASSERT_EQ(record.recordID, record_1.recordID);
}

TEST(SelStorageManager, GetLastRecord)
{
    SelStorageManager manager(path / fileName);

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};

    manager.add_record(record_1);
    manager.add_record(record_2);

    auto record = manager.get_record(ipmi::sel::lastEntry);

    ASSERT_EQ(record.recordID, record_2.recordID);
}

TEST(SelStorageManager, GetRecordById)
{
    SelStorageManager manager(path / fileName);

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};
    SelEventRecord record_3{3};

    manager.add_record(record_1);
    manager.add_record(record_2);
    manager.add_record(record_3);

    auto record = manager.get_record(2);

    ASSERT_EQ(record.recordID, record_2.recordID);
}