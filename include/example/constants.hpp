#ifndef STORAGE_MANAGER_CONSTANTS_HPP
#define STORAGE_MANAGER_CONSTANTS_HPP

#include <filesystem>
namespace fs = std::filesystem;

static const auto path = fs::current_path().root_path() / "var" / "log";
static const fs::path fileName = "ipmi_sel";

#endif // STORAGE_MANAGER_CONSTANTS_HPP
