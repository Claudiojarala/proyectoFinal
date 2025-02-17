#ifndef CUCKOO_HASH_H
#define CUCKOO_HASH_H

#include <vector>
#include "Database.h"

class CuckooHash {
private:
    std::vector<Database*> table1;
    std::vector<Database*> table2;
    int capacity;
    int totalElements;
    const int maxLoop = 32;

    int hash1(const std::string &key) const;
    int hash2(const std::string &key) const;
    void rehash();

public:
    CuckooHash(int cap = 11);
    ~CuckooHash();
    bool insert(Database* db);
    Database* find(const std::string &name);
    bool remove(const std::string &name);
    void guardarEnArchivo(const std::string &filename) const;
    bool cargarDesdeArchivo(const std::string &filename);
};

#endif // CUCKOO_HASH_H
