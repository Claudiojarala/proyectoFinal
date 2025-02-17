#include "CuckooHash.h"
#include <iostream>
#include <fstream>

CuckooHash::CuckooHash(int cap) : capacity(cap), totalElements(0) {
    table1.resize(capacity, nullptr);
    table2.resize(capacity, nullptr);
}

CuckooHash::~CuckooHash() {
    for (auto db : table1) {
        if (db)
            delete db;
    }
    for (auto db : table2) {
        if (db)
            delete db;
    }
}

int CuckooHash::hash1(const std::string &key) const {
    std::hash<std::string> hash_fn;
    return hash_fn(key) % capacity;
}

int CuckooHash::hash2(const std::string &key) const {
    std::hash<std::string> hash_fn;
    return (hash_fn(key) * 7) % capacity;
}

void CuckooHash::rehash() {
    int oldCapacity = capacity;
    capacity *= 2;
    std::vector<Database*> oldTable1 = table1;
    std::vector<Database*> oldTable2 = table2;

    table1.clear();
    table2.clear();
    table1.resize(capacity, nullptr);
    table2.resize(capacity, nullptr);
    totalElements = 0;

    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable1[i] != nullptr)
            insert(oldTable1[i]);
        if (oldTable2[i] != nullptr)
            insert(oldTable2[i]);
    }
}

bool CuckooHash::insert(Database* db) {
    std::string key = db->name;
    int loopCount = 0;
    Database* item = db;
    bool inTable1 = true;
    while (loopCount < maxLoop) {
        if (inTable1) {
            int pos = hash1(item->name);
            if (table1[pos] == nullptr) {
                table1[pos] = item;
                totalElements++;
                return true;
            } else {
                std::swap(item, table1[pos]);
                inTable1 = false;
            }
        } else {
            int pos = hash2(item->name);
            if (table2[pos] == nullptr) {
                table2[pos] = item;
                totalElements++;
                return true;
            } else {
                std::swap(item, table2[pos]);
                inTable1 = true;
            }
        }
        loopCount++;
    }
    rehash();
    return insert(item);
}

Database* CuckooHash::find(const std::string &name) {
    int pos1 = hash1(name);
    if (pos1 < (int)table1.size() && table1[pos1] && table1[pos1]->name == name)
        return table1[pos1];
    int pos2 = hash2(name);
    if (pos2 < (int)table2.size() && table2[pos2] && table2[pos2]->name == name)
        return table2[pos2];
    return nullptr;
}

bool CuckooHash::remove(const std::string &name) {
    int pos1 = hash1(name);
    if (pos1 < (int)table1.size() && table1[pos1] && table1[pos1]->name == name) {
        delete table1[pos1];
        table1[pos1] = nullptr;
        totalElements--;
        return true;
    }
    int pos2 = hash2(name);
    if (pos2 < (int)table2.size() && table2[pos2] && table2[pos2]->name == name) {
        delete table2[pos2];
        table2[pos2] = nullptr;
        totalElements--;
        return true;
    }
    return false;
}

void CuckooHash::guardarEnArchivo(const std::string &filename) const {
    std::ofstream outfile(filename, std::ios::binary | std::ios::trunc);
    if (!outfile.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << " para guardar." << std::endl;
        return;
    }
    outfile.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    outfile.write(reinterpret_cast<const char*>(&totalElements), sizeof(totalElements));
    for (int i = 0; i < capacity; ++i) {
        bool exists = (table1[i] != nullptr);
        outfile.write(reinterpret_cast<const char*>(&exists), sizeof(exists));
        if (exists) {
            table1[i]->serialize(outfile);
        }
    }
    for (int i = 0; i < capacity; ++i) {
        bool exists = (table2[i] != nullptr);
        outfile.write(reinterpret_cast<const char*>(&exists), sizeof(exists));
        if (exists) {
            table2[i]->serialize(outfile);
        }
    }
    outfile.close();
    std::cout << "Tabla guardada en archivo: " << filename << std::endl;
}

bool CuckooHash::cargarDesdeArchivo(const std::string &filename) {
    std::ifstream infile(filename, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << " para cargar." << std::endl;
        return false;
    }

    infile.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));
    infile.read(reinterpret_cast<char*>(&totalElements), sizeof(totalElements));
    table1.resize(capacity, nullptr);
    table2.resize(capacity, nullptr);
    for (int i = 0; i < capacity; ++i) {
        bool exists;
        infile.read(reinterpret_cast<char*>(&exists), sizeof(exists));
        if (exists) {
            Database* db = Database::deserialize(infile);
            table1[i] = db;
        }
    }
    for (int i = 0; i < capacity; ++i) {
        bool exists;
        infile.read(reinterpret_cast<char*>(&exists), sizeof(exists));
        if (exists) {
            Database* db = Database::deserialize(infile);
            table2[i] = db;
        }
    }
    infile.close();
    std::cout << "Tabla cargada desde archivo: " << filename << std::endl;
    return true;
}
