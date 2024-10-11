#ifndef THREAD2_H
#define THREAD2_H
#include <QThread>
#include <QMutexLocker>
#include <QQueue>
#include <QList>

// Thread2 is responsible for managing a queue of numbers in a thread-safe manner
// It allows adding numbers to the queue and retrieving the current state of the queue
class Thread2 : public QThread {
    Q_OBJECT
public:
    QQueue<int> queue;    // A FIFO queue that stores the numbers
    QMutex mutex;         // Mutex to ensure thread-safe access to the queue

    // Adds a number to the queue. If the queue has 20 or more elements, it removes the oldest one
    void addNumber(int num) {
        QMutexLocker locker(&mutex);  // Automatically locks the mutex for thread safety
        if (queue.size() >= 20) {     // Check if the queue size has reached the limit of 20
            queue.dequeue();          // Remove the oldest number if the queue is full
        }
        queue.enqueue(num);           // Add the new number to the queue
    }

    // Returns the current list of numbers in the queue
    QList<int> getNumbers() {
        QMutexLocker locker(&mutex);  // Automatically locks the mutex for thread-safe access
        return queue.toList();        // Convert the queue to a QList and return it
    }
};

#endif // THREAD2_H
