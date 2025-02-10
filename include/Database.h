#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "CircularQueue.h"

using namespace std;

struct Database {
    string name;
    string dataType;
    int capacity;
    CircularQueue* queue;

    Database(const string &n, const string &dt, int cap);
    ~Database();
    void serialize(ostream &os) const;
    static Database* deserialize(istream &is);
};

#endif // DATABASE_H
