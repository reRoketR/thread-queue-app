#ifndef THREAD1_H
#define THREAD1_H
#include <QThread>

// Thread1 is responsible for generating a sequence of numbers in its own thread.
// It generates numbers in increments and emits a signal each time a new number is generated.
class Thread1 : public QThread {
    Q_OBJECT
public:
    bool running = false;  // This flag controls whether the thread is running.
    int number = 0;        // The current number to be generated.

    // The main execution method of the thread, called when the thread is started.
    // It continuously generates numbers and emits them until the thread is stopped.
    void run() override {
        while (running) {
            QThread::msleep(500);       // Pause for 500 ms to make visible delay
            emit numberGenerated(number++);  // Emit a signal with the generated number and increment it.
        }
    }

signals:
    // This signal is emitted whenever a new number is generated.
    void numberGenerated(int num);
};

#endif // THREAD1_H
