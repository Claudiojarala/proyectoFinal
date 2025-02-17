#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>
#include <string>

using namespace std;

class CircularQueue {
private:
    double* arr;      // Arreglo dinámico para almacenar los valores
    int capacity;     // Capacidad máxima de la cola
    int front;        // Índice del primer elemento
    int rear;         // Índice del último elemento
    int count;        // Número de elementos actualmente en la cola

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
    void serialize(ostream &os) const;
    static CircularQueue* deserialize(istream &is);
};

#endif // CIRCULARQUEUE_H
