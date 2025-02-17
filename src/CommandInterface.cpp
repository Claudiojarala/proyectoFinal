
#include "CommandInterface.h"
#include <iostream>
#include <sstream>

using namespace std;

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

void CommandInterface::processCommand(const string &input) {
    istringstream iss(input);
    vector<string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    if (tokens.empty())
        return;

    if (tokens[0] != "RR") {
        cout << "El comando debe iniciar con 'RR'" << endl;
        return;
    }
    if (tokens.size() < 2) {
        cout << "Comando incompleto." << endl;
        return;
    }

    string command = tokens[1];
    if (!trie.search(command)) {
        string suggestion = trie.suggest(command);
        if (!suggestion.empty()) {
            cout << "Comando desconocido: " << command << endl;
            cout << "¿Quiso decir?: " << suggestion << "." << endl;
        } else {
            cout << "Comando desconocido: " << command << endl;
        }
        return;
    }

    if (command == "create") {
        if (tokens.size() < 5) {
            cout << "Uso: RR create <nombreBD> <tipoDato> <capacidad>" << endl;
            return;
        }
        string name = tokens[2];
        string dataType = tokens[3];
        int cap = atoi(tokens[4].c_str());
        Database* db = new Database(name, dataType, cap);
        if (dbStore.insert(db))
            cout << "Base de datos '" << name << "' creada exitosamente." << endl;
        else {
            cout << "Error al crear la base de datos." << endl;
            delete db;
        }

    } else if (command == "select") {
        if (tokens.size() < 4) {
            cout << "Uso: RR select <nombreBD> <índice>" << endl;
            return;
        }
        string name = tokens[2];
        int index = atoi(tokens[3].c_str());
        Database* db = dbStore.find(name);
        if (!db) {
            cout << "Base de datos '" << name << "' no encontrada." << endl;
            return;
        }
        string value = db->getValue(index);
        if (!value.empty())
            cout << "Valor en el nodo " << index << " es: " << value << endl;
        else
            cout << "Índice fuera de rango." << endl;

    } else if (command == "insert") {
        if (tokens.size() < 4) {
            cout << "Uso: RR insert <nombreBD> <valor>" << endl;
            return;
        }
        string name = tokens[2];
        string value = tokens[3];
        Database* db = dbStore.find(name);
        if (!db) {
            cout << "Base de datos '" << name << "' no encontrada." << endl;
            return;
        }
        if (db->insertValue(value))
            cout << "Valor '" << value << "' insertado en la base de datos '" << name << "'." << endl;
        else
            cout << "La cola está llena." << endl;

    } else if (command == "update") {
        if (tokens.size() < 5) {
            cout << "Uso: RR update <nombreBD> <índice> <nuevoValor>" << endl;
            return;
        }
        string name = tokens[2];
        int index = atoi(tokens[3].c_str());
        double newVal = atof(tokens[4].c_str());
        Database* db = dbStore.find(name);
        if (!db) {
            cout << "Base de datos '" << name << "' no encontrada." << endl;
            return;
        }
        if (db->queue->updateAt(index, newVal))
            cout << "Valor en el nodo " << index << " actualizado a " << newVal << "." << endl;
        else
            cout << "Índice fuera de rango." << endl;

    } else if (command == "delete") {
        if (tokens.size() < 3) {
            cout << "Uso: RR delete <nombreBD>" << endl;
            return;
        }
        string name = tokens[2];
        if (dbStore.remove(name))
            cout << "Base de datos '" << name << "' eliminada." << endl;
        else
            cout << "Base de datos '" << name << "' no encontrada." << endl;

    } else if (command == "print") {
        if (tokens.size() < 3) {
            cout << "Uso: RR print <nombreBD>" << endl;
            return;
        }
        string name = tokens[2];
        Database* db = dbStore.find(name);
        if (!db) {
            cout << "Base de datos '" << name << "' no encontrada." << endl;
            return;
        }
        cout << "Contenido de la base de datos '" << name << "': ";
        db->queue->printQueue();

    } else if (command == "save") {
        if (tokens.size() < 3) {
            cout << "Uso: RR save <filename>" << endl;
            return;
        }
        string filename = tokens[2];
        dbStore.guardarEnArchivo(filename);

    } else if (command == "load") {
        if (tokens.size() < 3) {
            cout << "Uso: RR load <filename>" << endl;
            return;
        }
        string filename = tokens[2];
        if (dbStore.cargarDesdeArchivo(filename))
            cout << "Tabla cargada correctamente." << endl;
        else
            cout << "Error al cargar la tabla." << endl;
    }
}
