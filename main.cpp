#include "CommandInterface.h"
#include <iostream>
#include <string>

int main() {
    CommandInterface ci;
    std::string line;

    std::cout << "Ingrese comandos (escriba 'exit' para salir):" << std::endl;
    while (std::getline(std::cin, line)) {
        if (line == "exit")
            break;
        ci.processCommand(line);
    }

    return 0;
}
