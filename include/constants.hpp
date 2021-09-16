#ifndef STORAGE_MANAGER_CONSTANTS_HPP
#define STORAGE_MANAGER_CONSTANTS_HPP

#include <filesystem>
namespace fs = std::filesystem;

static const fs::path dir = fs::current_path().root_path() / "var" / "log";
static const fs::path file_name = "ipmi_sel";

#endif // STORAGE_MANAGER_CONSTANTS_HPP
