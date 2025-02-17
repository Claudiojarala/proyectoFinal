#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "CircularQueue.h"

using namespace std;

struct Database {
    string name;
    string dataType;
    int capacity;
    CircularQueue* queue;  // Puntero a la cola circular de datos

    Database(const string &n, const string &dt, int cap);
    ~Database();
    double stringToDouble(const string& str) const;
    string doubleToString(double value) const;
    bool insertValue(const string& value);
    string getValue(int index) const;
    void serialize(ostream &os) const;
    static Database* deserialize(istream &is);
};

#endif // DATABASE_H
