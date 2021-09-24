#include <example/sel/sel_storage_manager.hpp>
#include <example/sel/sel_utils.hpp>

void SelStorageManager::delete_record(uint16_t id)
{
    auto entries = load_records();

    // TODO: report about the empty storage
    if (entries.empty())
    {
        cancel_sel_reservation();
        return;
    }

    if (id == ipmi::sel::firstEntry)
    {
        entries.erase(entries.begin());
    }
    else if (id == ipmi::sel::lastEntry)
    {
        entries.erase(entries.end() - 1);
    }
    else
    {
        auto entry = std::find_if(
            entries.begin(), entries.end(),
            [id](const SelEventRecord& entry) { return entry.recordId == id; });

        if (entry != entries.end())
            entries.erase(entry);
        // TODO: report about wrong entry id
        else
            ;
    }

    clear_storage();

    for (const auto& entry : entries)
        add_record(entry);
}

SelEventRecord SelStorageManager::get_record(uint16_t id)
{
    auto entries = load_records();

    // TODO: report about the empty storage
    if (entries.empty())
        return {};

    if (id == ipmi::sel::firstEntry)
    {
        return entries.front();
    }
    else if (id == ipmi::sel::lastEntry)
    {
        return entries.back();
    }
    else
    {
        auto entry = std::find_if(
            entries.begin(), entries.end(),
            [id](const SelEventRecord& entry) { return entry.recordId == id; });

        if (entry != entries.end())
            return *entry;
        // TODO: report about wrong entry id
        else
            return {};
    }
}

SelStorageManager::SelStorageManager(fs::path path, size_t maxSize) :
    StorageManager(std::move(path), maxSize), selReservationId{0xFFFF},
    selReservationValid{false}
{}

void SelStorageManager::cancel_sel_reservation()
{
    selReservationValid = false;
}

bool SelStorageManager::check_sel_reservation(uint16_t id) const
{
    return (selReservationValid && selReservationId == id);
}

uint16_t SelStorageManager::reserve_sel()
{
    // IPMI spec, Reservation ID, the value simply increases against each
    // execution of the Reserve SEL command.
    if (++selReservationId == 0)
        selReservationId = 1;

    selReservationValid = true;
    return selReservationId;
}

void SelStorageManager::add_record(SelEventRecord object)
{
    // object.recordId = get_records_count();
    StorageManager::add_record(object);
    cancel_sel_reservation();
}

void SelStorageManager::clear_storage()
{
    StorageManager::clear_storage();
    cancel_sel_reservation();
}

uint16_t SelStorageManager::get_reservation_id() const
{
    if (selReservationValid)
        return selReservationId;
    else
        return ipmi::sel::invalidSelReservationId;
}
