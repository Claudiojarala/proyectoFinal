#include "Database.h"
#include <iostream>
#include <fstream>

using namespace std;

Database::Database(const string &n, const string &dt, int cap)
    : name(n), dataType(dt), capacity(cap) {
    queue = new CircularQueue(cap);
}

Database::~Database() {
    delete queue;
}

void Database::serialize(ostream &os) const {
    size_t nameLen = name.size();
    os.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    os.write(name.data(), nameLen);
    size_t dataTypeLen = dataType.size();
    os.write(reinterpret_cast<const char*>(&dataTypeLen), sizeof(dataTypeLen));
    os.write(dataType.data(), dataTypeLen);
    os.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    queue->serialize(os);
}

Database* Database::deserialize(istream &is) {
    size_t nameLen;
    is.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    string name;
    name.resize(nameLen);
    is.read(&name[0], nameLen);
    size_t dataTypeLen;
    is.read(reinterpret_cast<char*>(&dataTypeLen), sizeof(dataTypeLen));
    string dataType;
    dataType.resize(dataTypeLen);
    is.read(&dataType[0], dataTypeLen);
    int cap;
    is.read(reinterpret_cast<char*>(&cap), sizeof(cap));
    Database* db = new Database(name, dataType, cap);
    delete db->queue;
    db->queue = CircularQueue::deserialize(is);
    return db;
}
