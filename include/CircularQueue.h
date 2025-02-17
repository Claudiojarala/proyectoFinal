#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>
#include <ostream>
#include <istream>

class CircularQueue {
private:
    double* arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    CircularQueue(int cap);
    ~CircularQueue();
    bool isFull() const;
    bool isEmpty() const;
    bool enqueue(double value);
    bool dequeue(double &value);
    void printQueue();
    bool getValueAt(int index, double &value);
    bool updateAt(int index, double newVal);
    void serialize(std::ostream &os) const;
    static CircularQueue* deserialize(std::istream &is);
};

#endif // CIRCULARQUEUE_H
