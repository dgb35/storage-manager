#ifndef STORAGE_MANAGER_SEL_STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_SEL_STORAGE_MANAGER_HPP

#include "sel_event_record.hpp"
#include "storage_manager.hpp"
namespace storage
{
class SelStorageManager : public StorageManager<SelEventRecord>
{
  public:
    explicit SelStorageManager(fs::path path, size_t maxSize = 16000);

  public:
    void add_record(SelEventRecord object) override;
    void clear_storage() override;
    void delete_record(uint16_t id);
    [[nodiscard]] SelEventRecord get_record(uint16_t id);
    [[nodiscard]] uint16_t get_reservation_id() const;

    uint16_t reserve_sel();
    void cancel_sel_reservation();
    [[nodiscard]] bool check_sel_reservation(uint16_t id) const;

  protected:
    uint16_t selReservationId;
    bool selReservationValid;
};
} // namespace storage
#endif // STORAGE_MANAGER_SEL_STORAGE_MANAGER_HPP
