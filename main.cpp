#include "include/CommandInterface.h"
#include <iostream>

using namespace std;

int main() {
    CommandInterface ci;
    string line;

    cout << "Ingrese comandos (escriba 'exit' para salir):" << endl;
    while (getline(cin, line)) {
        if (line == "exit")
            break;
        ci.processCommand(line);
    }
    return 0;
}
