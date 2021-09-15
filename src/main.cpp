#include <iostream>
#include <storage_manager.hpp>

int main() {
    std::cout << selLogDir << std::endl;

    StorageManager manager(selLogDir / selLogFilename);
    
    manager.clearStorage();

    return 0;
}
