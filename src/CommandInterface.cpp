
#include "CommandInterface.h"
#include <iostream>
#include <sstream>

CommandInterface::CommandInterface() : dbStore(11) {
    trie.insert("create");
    trie.insert("select");
    trie.insert("insert");
    trie.insert("update");
    trie.insert("delete");
    trie.insert("print");
    trie.insert("save");
    trie.insert("load");
}

void CommandInterface::processCommand(const std::string &input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    if (tokens.empty())
        return;

    if (tokens[0] != "RR") {
        std::cout << "El comando debe iniciar con 'RR'" << std::endl;
        return;
    }
    if (tokens.size() < 2) {
        std::cout << "Comando incompleto." << std::endl;
        return;
    }

    std::string command = tokens[1];
    if (!trie.search(command)) {
        std::string suggestion = trie.suggest(command);
        if (!suggestion.empty()) {
            std::cout << "Comando desconocido: " << command << std::endl;
            std::cout << "¿Quiso decir?: " << suggestion << "." << std::endl;
        } else {
            std::cout << "Comando desconocido: " << command << std::endl;
        }
        return;
    }

    if (command == "create") {
        if (tokens.size() < 5) {
            std::cout << "Uso: RR create <nombreBD> <tipoDato> <capacidad>" << std::endl;
            return;
        }
        std::string name = tokens[2];
        std::string dataType = tokens[3];
        int cap = atoi(tokens[4].c_str());
        Database* db = new Database(name, dataType, cap);
        if (dbStore.insert(db))
            std::cout << "Base de datos '" << name << "' creada exitosamente." << std::endl;
        else {
            std::cout << "Error al crear la base de datos." << std::endl;
            delete db;
        }

    } else if (command == "select") {
        if (tokens.size() < 4) {
            std::cout << "Uso: RR select <nombreBD> <índice>" << std::endl;
            return;
        }
        std::string name = tokens[2];
        int index = atoi(tokens[3].c_str());
        Database* db = dbStore.find(name);
        if (!db) {
            std::cout << "Base de datos '" << name << "' no encontrada." << std::endl;
            return;
        }
        std::string value = db->getValue(index);
        if (!value.empty())
            std::cout << "Valor en el nodo " << index << " es: " << value << std::endl;
        else
            std::cout << "Índice fuera de rango." << std::endl;

    } else if (command == "insert") {
        if (tokens.size() < 4) {
            std::cout << "Uso: RR insert <nombreBD> <valor>" << std::endl;
            return;
        }
        std::string name = tokens[2];
        std::string value = tokens[3];
        Database* db = dbStore.find(name);
        if (!db) {
            std::cout << "Base de datos '" << name << "' no encontrada." << std::endl;
            return;
        }
        if (db->insertValue(value))
            std::cout << "Valor '" << value << "' insertado en la base de datos '" << name << "'." << std::endl;
        else
            std::cout << "La cola está llena." << std::endl;

    } else if (command == "update") {
        if (tokens.size() < 5) {
            std::cout << "Uso: RR update <nombreBD> <índice> <nuevoValor>" << std::endl;
            return;
        }
        std::string name = tokens[2];
        int index = atoi(tokens[3].c_str());
        double newVal = atof(tokens[4].c_str());
        Database* db = dbStore.find(name);
        if (!db) {
            std::cout << "Base de datos '" << name << "' no encontrada." << std::endl;
            return;
        }
        if (db->queue->updateAt(index, newVal))
            std::cout << "Valor en el nodo " << index << " actualizado a " << newVal << "." << std::endl;
        else
            std::cout << "Índice fuera de rango." << std::endl;

    } else if (command == "delete") {
        if (tokens.size() < 3) {
            std::cout << "Uso: RR delete <nombreBD>" << std::endl;
            return;
        }
        std::string name = tokens[2];
        if (dbStore.remove(name))
            std::cout << "Base de datos '" << name << "' eliminada." << std::endl;
        else
            std::cout << "Base de datos '" << name << "' no encontrada." << std::endl;

    } else if (command == "print") {
        if (tokens.size() < 3) {
            std::cout << "Uso: RR print <nombreBD>" << std::endl;
            return;
        }
        std::string name = tokens[2];
        Database* db = dbStore.find(name);
        if (!db) {
            std::cout << "Base de datos '" << name << "' no encontrada." << std::endl;
            return;
        }
        std::cout << "Contenido de la base de datos '" << name << "': ";
        db->queue->printQueue();

    } else if (command == "save") {
        if (tokens.size() < 3) {
            std::cout << "Uso: RR save <filename>" << std::endl;
            return;
        }
        std::string filename = tokens[2];
        dbStore.guardarEnArchivo(filename);

    } else if (command == "load") {
        if (tokens.size() < 3) {
            std::cout << "Uso: RR load <filename>" << std::endl;
            return;
        }
        std::string filename = tokens[2];
        if (dbStore.cargarDesdeArchivo(filename))
            std::cout << "Tabla cargada correctamente." << std::endl;
        else
            std::cout << "Error al cargar la tabla." << std::endl;
    }
}
