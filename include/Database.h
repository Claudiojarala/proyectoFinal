#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "CircularQueue.h"

struct Database {
    std::string name;
    std::string dataType;
    int capacity;
    CircularQueue* queue;

    Database(const std::string &n, const std::string &dt, int cap);
    ~Database();
    double stringToDouble(const std::string& str) const;
    std::string doubleToString(double value) const;
    bool insertValue(const std::string& value);
    std::string getValue(int index) const;
    void serialize(std::ostream &os) const;
    static Database* deserialize(std::istream &is);
};

#endif // DATABASE_H
