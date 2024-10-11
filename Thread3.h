#ifndef THREAD3_H
#define THREAD3_H
#include "Thread2.h"

// Thread3 is responsible for consuming numbers from the queue managed by Thread2
// It runs in its own thread and periodically dequeues numbers from the queue
class Thread3 : public QThread {
    Q_OBJECT
public:
    bool running = false;  // This flag controls whether the thread should be running
    Thread2* queueManager; // Pointer to the queue manager (Thread2), which manages the queue

    // Constructor that initializes the queue manager reference
    Thread3(Thread2* manager) : queueManager(manager) {
    }

    // The main execution method of the thread, called when the thread is started
    void run() override {
        while(running) {
            QThread::msleep(500);  // Pause for 500 ms between each queue check

            if (!queueManager->queue.isEmpty()) {
                queueManager->mutex.lock();  // Lock the mutex to ensure thread-safe access to the queue
                int num = queueManager->queue.dequeue();  // Dequeue the oldest number
                queueManager->mutex.unlock();  // Unlock the mutex after modifying the queue

                emit numberConsumed(num);  // Emit a signal that a number has been consumed
            }
        }
    }

signals:
    // This signal is emitted whenever a number is consumed from the queue
    void numberConsumed(int num);
};


#endif // THREAD3_H
