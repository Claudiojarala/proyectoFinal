#include "CircularQueue.h"
#include <iostream>
#include <fstream>

using namespace std;

CircularQueue::CircularQueue(int cap) : capacity(cap), front(0), rear(-1), count(0) {
    arr = new double[capacity];
}

CircularQueue::~CircularQueue() {
    delete[] arr;
}

bool CircularQueue::isFull() const {
    return count == capacity;
}

bool CircularQueue::isEmpty() const {
    return count == 0;
}

bool CircularQueue::enqueue(double value) {
    if (isFull())
        return false;
    rear = (rear + 1) % capacity;
    arr[rear] = value;
    count++;
    return true;
}

bool CircularQueue::dequeue(double &value) {
    if (isEmpty())
        return false;
    value = arr[front];
    front = (front + 1) % capacity;
    count--;
    return true;
}

void CircularQueue::printQueue() {
    if (isEmpty()) {
        cout << "La cola está vacía." << endl;
        return;
    }
    int idx = front;
    for (int i = 0; i < count; i++) {
        cout << arr[idx] << " ";
        idx = (idx + 1) % capacity;
    }
    cout << endl;
}

// Implementar los demás métodos...
