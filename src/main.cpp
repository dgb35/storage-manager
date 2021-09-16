#include <iostream>

#include "storage_manager.hpp"
#include "constants.hpp"

int main() {
    StorageManager manager(selLogDir / selLogFilename);

    //    auto out = manager.getFileStream();
    //    out << "123" << std::endl << "321" << std::endl;
    //    out.close();

    manager.clearStorage();

    std::cout << "Path to file: " << selLogDir << std::endl;
    std::cout << "Number of entries: " << manager.countEntries() << std::endl << std::endl;

    std::cout << "Inside file: " << std::endl;

    auto in = manager.getFileStream();
    std::string temp;
    while (std::getline(in, temp)) {
        std::cout << temp << std::endl;
    }

    return 0;
}
