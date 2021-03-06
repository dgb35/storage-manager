#ifndef STORAGE_MANAGER_SEL_UTILS_HPP
#define STORAGE_MANAGER_SEL_UTILS_HPP

namespace ipmi::sel
{
static constexpr auto firstEntry = 0x0000;
static constexpr auto lastEntry = 0xFFFF;

static constexpr auto invalidSelRecordId = 0xFFFF;
static constexpr auto invalidSelReservationId = 0xFFFF;
} // namespace ipmi::sel

#endif // STORAGE_MANAGER_SEL_UTILS_HPP
