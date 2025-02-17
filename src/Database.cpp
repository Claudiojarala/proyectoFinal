#include "Database.h"
#include <iostream>
#include <fstream>

Database::Database(const std::string &n, const std::string &dt, int cap)
    : name(n), dataType(dt), capacity(cap) {
    queue = new CircularQueue(cap);
}

Database::~Database() {
    delete queue;
}

double Database::stringToDouble(const std::string& str) const {
    double value = 0.0;
    for (char c : str) {
        value = value * 256 + static_cast<double>(c);
    }
    return value;
}

std::string Database::doubleToString(double value) const {
    std::string result;
    while (value > 0) {
        char c = static_cast<char>(fmod(value, 256));
        result = c + result;
        value = floor(value / 256);
    }
    return result;
}

bool Database::insertValue(const std::string& value) {
    if (dataType == "string") {
        return queue->enqueue(stringToDouble(value));
    } else {
        return queue->enqueue(stod(value));
    }
}

std::string Database::getValue(int index) const {
    double value;
    if (!queue->getValueAt(index, value)) {
        return "";
    }
    if (dataType == "string") {
        return doubleToString(value);
    }
    return std::to_string(value);
}

void Database::serialize(std::ostream &os) const {
    size_t nameLen = name.size();
    os.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    os.write(name.data(), nameLen);
    size_t dataTypeLen = dataType.size();
    os.write(reinterpret_cast<const char*>(&dataTypeLen), sizeof(dataTypeLen));
    os.write(dataType.data(), dataTypeLen);
    os.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    queue->serialize(os);
}

Database* Database::deserialize(std::istream &is) {
    size_t nameLen;
    is.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    std::string name;
    name.resize(nameLen);
    is.read(&name[0], nameLen);
    size_t dataTypeLen;
    is.read(reinterpret_cast<char*>(&dataTypeLen), sizeof(dataTypeLen));
    std::string dataType;
    dataType.resize(dataTypeLen);
    is.read(&dataType[0], dataTypeLen);
    int cap;
    is.read(reinterpret_cast<char*>(&cap), sizeof(cap));
    Database* db = new Database(name, dataType, cap);
    delete db->queue;
    db->queue = CircularQueue::deserialize(is);
    return db;
}
