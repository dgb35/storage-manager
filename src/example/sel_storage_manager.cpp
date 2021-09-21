#include "example/sel_storage_manager.hpp"

#include "example/sel_utils.hpp"

void SelStorageManager::delete_record(uint16_t id)
{
    auto entries = load_records();

    // TODO: report about the empty storage
    if (entries.empty())
        return;

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
            [id](const SelEventRecord& entry) { return entry.recordID == id; });


        if (entry != entries.end())
            entries.erase(entry);
        // TODO: report about wrong entry id
        else
            ;
    }

    clear_storage();

    for (const auto& entry : entries)
    {
        add_record(entry);
    }
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
            [id](const SelEventRecord& entry) { return entry.recordID == id; });


        if (entry != entries.end())
            return *entry;
        // TODO: report about wrong entry id
        else
            return {};
    }
}

SelStorageManager::SelStorageManager(fs::path path) :
    StorageManager(std::move(path))
{}
