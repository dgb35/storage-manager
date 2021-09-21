#ifndef STORAGE_MANAGER_SEL_STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_SEL_STORAGE_MANAGER_HPP

#include "example/sel_event_record.hpp"
#include "storage_manager.hpp"

class SelStorageManager : public StorageManager<SelEventRecord>
{
  public:
    explicit SelStorageManager(fs::path path);

  public:
    void delete_record(uint16_t id);
    SelEventRecord get_record(uint16_t id);
};

#endif // STORAGE_MANAGER_SEL_STORAGE_MANAGER_HPP
