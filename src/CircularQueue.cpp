#include "CircularQueue.h"
#include <iostream>
#include <fstream>
#include <cmath>

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

bool CircularQueue::getValueAt(int index, double &value) {
    if (index < 0 || index >= count)
        return false;
    int idx = (front + index) % capacity;
    value = arr[idx];
    return true;
}

bool CircularQueue::updateAt(int index, double newVal) {
    if (index < 0 || index >= count)
        return false;
    int idx = (front + index) % capacity;
    arr[idx] = newVal;
    return true;
}

void CircularQueue::serialize(ostream &os) const {
    os.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (int i = 0; i < count; ++i) {
        int idx = (front + i) % capacity;
        double value = arr[idx];
        os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
}

CircularQueue* CircularQueue::deserialize(istream &is) {
    int cap, cnt;
    is.read(reinterpret_cast<char*>(&cap), sizeof(cap));
    is.read(reinterpret_cast<char*>(&cnt), sizeof(cnt));
    CircularQueue* cq = new CircularQueue(cap);
    for (int i = 0; i < cnt; ++i) {
        double value;
        is.read(reinterpret_cast<char*>(&value), sizeof(value));
        cq->enqueue(value);
    }
    return cq;
}
