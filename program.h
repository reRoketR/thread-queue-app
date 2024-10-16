#ifndef PROGRAM_H
#define PROGRAM_H
#include <QWidget>
#include "Thread1.h"
#include "Thread2.h"
#include "Thread3.h"
#include <QListWidget>
#include <QLabel>
#include <QVector>
#include <QPushButton>

// The Program class represents the main window of the application and manages the interaction
// between the UI and the threads (Thread1, Thread2, Thread3).
class Program : public QWidget {
    Q_OBJECT

    // ListWidgets to display the numbers for each thread.
    QListWidget* listBox1;  // Shows numbers generated by Thread1.
    QListWidget* listBox2;  // Shows the queue managed by Thread2.
    QListWidget* listBox3;  // Shows numbers consumed by Thread3.

    // Thread objects.
    Thread1* thread1;  // Generates numbers.
    Thread2* thread2;  // Manages the queue (FIFO).
    Thread3* thread3;  // Consumes numbers from the queue.

    // Labels to display the status of each thread.
    QLabel* thread1Label;  // Label for Thread1 status.
    QLabel* thread2Label;  // Label for Thread2 status.
    QLabel* thread3Label;  // Label for Thread3 status.

    // Button to toggle current state of thread
    QPushButton* startStopButton1;  // Button for toggling Thread1
    QPushButton* startStopButton3;  // Button for toggling Thread3

    // Buffers to store numbers temporarily.
    QVector<int> generatedNumsBuffer;  // Buffer for numbers generated by Thread1.
    QVector<int> consumedNumsBuffer;   // Buffer for numbers consumed by Thread3.

    QMutex mutex;

public:
    // Constructor that sets up the UI, threads, and connections.
    Program();

private:
    // Updates the listBox1 with the numbers generated by Thread1.
    void updateListBox1();

    // Updates the listBox2 with the current queue state from Thread2.
    void updateListBox2();

    // Updates the listBox3 with the numbers consumed by Thread3.
    void updateListBox3();

    // Updates the thread status labels (running/stopped)
    void updateThreadLabels();

    // Initializes and configures the basic UI components
    void setupUIComponents();

    // Defines how widgets are laid out and configures their size policies.
    void setupLayout();

    // Initializes the threads
    void setupThreads();

    // Sets up signal-slot connections for buttons and thread-to-UI communication.
    void setupConnections();

    // Configures the timer to update the UI periodically.
    void setupTimer();

private slots:
    // Adds a number generated by Thread1 to the generatedNumsBuffer and passes it to Thread2 (queue)
    void addNum(int num);

    // Adds a number consumed by Thread3 to the consumedNumsBuffer
    void consumeNum(int num);

    // Starts or stops Thread1 based on its current state
    void toggleThread1();

    // Starts or stops Thread3 based on its current state
    void toggleThread3();

    // Updates the UI by calling the list update methods
    void updateUI();

};


#endif // PROGRAM_H
