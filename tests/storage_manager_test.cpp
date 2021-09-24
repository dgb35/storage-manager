#include <example/sel/sel_event_record.hpp>
#include <example/sel/sel_storage_manager.hpp>
#include <example/sel/sel_utils.hpp>
#include <storage_manager.hpp>

#include <filesystem>
#include <thread>

#include "gtest/gtest.h"

namespace fs = std::filesystem;
using namespace storage;

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
    manager.clear_storage();

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};

    manager.add_record(record_1);
    manager.add_record(record_2);

    manager.delete_record(ipmi::sel::firstEntry);

    auto entries = manager.load_records();

    ASSERT_EQ(record_2.recordId, entries.front().recordId);
}

TEST(SelStorageManager, DeleteLastRecord)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};

    manager.add_record(record_1);
    manager.add_record(record_2);

    manager.delete_record(ipmi::sel::lastEntry);

    auto entries = manager.load_records();

    ASSERT_EQ(record_1.recordId, entries.front().recordId);
}

TEST(SelStorageManager, DeleteRecordById)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};
    SelEventRecord record_3{3};

    manager.add_record(record_1);
    manager.add_record(record_2);
    manager.add_record(record_3);

    manager.delete_record(2);

    auto entries = manager.load_records();

    ASSERT_EQ(record_1.recordId, entries.front().recordId);
    ASSERT_EQ(record_3.recordId, entries.back().recordId);
}

TEST(SelStorageManager, GetFirstRecord)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};

    manager.add_record(record_1);
    manager.add_record(record_2);

    auto record = manager.get_record(ipmi::sel::firstEntry);

    ASSERT_EQ(record.recordId, record_1.recordId);
}

TEST(SelStorageManager, GetLastRecord)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};

    manager.add_record(record_1);
    manager.add_record(record_2);

    auto record = manager.get_record(ipmi::sel::lastEntry);

    ASSERT_EQ(record.recordId, record_2.recordId);
}

TEST(SelStorageManager, GetRecordById)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    SelEventRecord record_1{1};
    SelEventRecord record_2{2};
    SelEventRecord record_3{3};

    manager.add_record(record_1);
    manager.add_record(record_2);
    manager.add_record(record_3);

    auto record = manager.get_record(2);

    ASSERT_EQ(record.recordId, record_2.recordId);
}

TEST(SelStorageManager, CountEntries)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    static constexpr auto count = 3;

    SelEventRecord record{1};

    for (int i = 0; i < count; ++i)
        manager.add_record(record);

    auto sel_count = manager.get_records_count();

    ASSERT_EQ(sel_count, count);
}

TEST(SelStorageManager, ReserveSel)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    manager.reserve_sel();
    manager.reserve_sel();
    ASSERT_TRUE(manager.check_sel_reservation(2));
}

TEST(SelStorageManager, ReserveSelWithInvalidReservation)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    manager.reserve_sel();
    manager.reserve_sel();
    manager.cancel_sel_reservation();
    ASSERT_FALSE(manager.check_sel_reservation(2));
}

TEST(SelStorageManager, ReserveSelAfterAdd)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    manager.reserve_sel();
    SelEventRecord record{1};
    manager.add_record(record);

    ASSERT_FALSE(manager.check_sel_reservation(1));
}

TEST(SelStorageManager, ReserveSelAfterDelete)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    manager.reserve_sel();
    SelEventRecord record{1};
    manager.delete_record(1);

    ASSERT_FALSE(manager.check_sel_reservation(0));
    ASSERT_FALSE(manager.check_sel_reservation(1));
}

TEST(SelStorageManager, ReserveSelAfterClearStorage)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    manager.reserve_sel();
    SelEventRecord record{1};
    manager.add_record(record);

    manager.clear_storage();

    ASSERT_FALSE(manager.check_sel_reservation(0));
    ASSERT_FALSE(manager.check_sel_reservation(1));
}

TEST(SelStorageManager, ReserveSelAfterCancel)
{
    SelStorageManager manager(path / fileName);
    manager.clear_storage();

    manager.reserve_sel();
    manager.cancel_sel_reservation();
    manager.reserve_sel();

    ASSERT_TRUE(manager.check_sel_reservation(2));
}
