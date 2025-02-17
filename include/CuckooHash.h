#ifndef CUCKOOHASH_H
#define CUCKOOHASH_H

#include <vector>
#include "Database.h"

using namespace std;

class CuckooHash {
private:
    vector<Database*> table1;
    vector<Database*> table2;
    int capacity;
    int totalElements;
    const int maxLoop = 32;

    int hash1(const string &key) const;
    int hash2(const string &key) const;
    void rehash();

public:
    CuckooHash(int cap = 11);
    ~CuckooHash();

    bool insert(Database* db);
    Database* find(const string &name);
    bool remove(const string &name);
    void guardarEnArchivo(const string &filename) const;
    bool cargarDesdeArchivo(const string &filename);
};

#endif // CUCKOOHASH_H
