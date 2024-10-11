#include "program.h"
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
Program::Program() {
    // creating objects for UI listboxes
    listBox1 = new QListWidget(this);
    listBox2 = new QListWidget(this);
    listBox3 = new QListWidget(this);

    // creating objects for UI labels
    thread1Label = new QLabel("Thread 1 (Stopped)", this);
    thread2Label = new QLabel("Thread 2", this);
    thread3Label = new QLabel("Thread 3 (Stopped)", this);

    // setting alignment for labels
    thread1Label->setAlignment(Qt::AlignCenter);
    thread2Label->setAlignment(Qt::AlignCenter);
    thread3Label->setAlignment(Qt::AlignCenter);

    // creating objects for UI buttons
    QPushButton* startStopButton1 = new QPushButton("Start/Stop Thread 1", this);
    QPushButton* startStopButton3 = new QPushButton("Start/Stop Thread 3", this);

    // setting 'clicked' signals to invoke thread toggling
    connect(startStopButton1, &QPushButton::clicked, this, &Program::toggleThread1);
    connect(startStopButton3, &QPushButton::clicked, this, &Program::toggleThread3);
    
    // Creating threads
    thread1 = new Thread1();  // Thread to generate numbers
    thread2 = new Thread2();  // Thread managing the queue (FIFO)
    thread3 = new Thread3(thread2);  // Thread to consume numbers from the queue

    // Setting up signals to connect thread events to UI updates
    connect(thread1, &Thread1::numberGenerated, this, &Program::addNum);  // Connect number generation signal to addNum slot
    connect(thread3, &Thread3::numberConsumed, this, &Program::consumeNum);  // Connect number consumption signal to consumeNum slot

    // Creating a timer to update the UI every 333ms (3 times per second)
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Program::updateUI);  // Connect timer to UI update slot
    timer->start(333);  // Set timer to trigger every 333ms

    // Creating a grid layout for the UI components
    QGridLayout* gridLayout = new QGridLayout(this);

    // Set minimum sizes for list boxes and buttons
    listBox1->setMinimumSize(150, 200);
    listBox2->setMinimumSize(150, 200);
    listBox3->setMinimumSize(150, 200);
    startStopButton1->setMinimumSize(100, 40);
    startStopButton3->setMinimumSize(100, 40);

    // Set scalable size policies for widgets (expandable with window resize)
    thread1Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    thread2Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    thread3Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listBox1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listBox2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listBox3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    startStopButton1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    startStopButton3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Setting column stretches to ensure equal width for each column
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setColumnStretch(2, 1);

    // Setting row stretches to balance layout
    gridLayout->setRowStretch(0, 0);
    gridLayout->setRowStretch(1, 1);
    gridLayout->setRowStretch(2, 0);

    // Adding widgets to the grid layout
    gridLayout->addWidget(thread1Label, 0, 0);
    gridLayout->addWidget(thread2Label, 0, 1);
    gridLayout->addWidget(thread3Label, 0, 2);


    // Add list boxes to the grid layout (one in each column)
    gridLayout->addWidget(listBox1, 1, 0);
    gridLayout->addWidget(listBox2, 1, 1);
    gridLayout->addWidget(listBox3, 1, 2);

    // Add buttons for toggling threads under listBox1 and listBox3
    gridLayout->addWidget(startStopButton1, 2, 0);
    gridLayout->addWidget(startStopButton3, 2, 2);

}

void Program::updateListBox1() {
    // Loop through the generatedNumsBuffer and add new numbers to the list box
    while (!generatedNumsBuffer.isEmpty()) {
        // Taking the first number from the buffer and add it to the list box
        int num = generatedNumsBuffer.takeFirst();
        listBox1->addItem(QString::number(num));
    }
    listBox1->scrollToBottom();
}

void Program::updateListBox2(){
    listBox2->clear();
    for (int num : thread2->getNumbers()) {
        listBox2->addItem(QString::number(num));
    }
}
void Program::updateListBox3() {
    // Loop through the generatedNumsBuffer and add new numbers to the list box
    while (!consumedNumsBuffer.isEmpty()) {
        // Take the first number from the buffer and add it to the list box
        int num = consumedNumsBuffer.takeFirst();
        listBox3->addItem(QString::number(num));
    }
    listBox3->scrollToBottom();
}


// Updates the UI components (ListBoxes) every time the timer triggers
// It refreshes the display for all three threads' list boxes
void Program::updateUI()
{
    updateListBox1();
    updateListBox2();
    updateListBox3();
}

// This method handles the addition of a number generated by Thread1
// It adds the number to a temporary buffer (generatedNumsBuffer) and
// sends the number to the queue manager (thread2)
void Program::addNum(int num)
{
    generatedNumsBuffer.push_back(num);
    thread2->addNumber(num);
}

// This method handles the consumption of a number by Thread3
// It adds the consumed number to the buffer (consumedNumsBuffer)
void Program::consumeNum(int num)
{
    consumedNumsBuffer.push_back(num);
}

// Toggles the start/stop state of Thread1 when the button is clicked
// If the thread is running, it will stop and quit. If it is not running, the thread will start
void Program::toggleThread1(){
    if (thread1->running) {
        thread1->running = false;
        thread1->quit();
    } else {
        thread1->running = true;
        thread1->start();
    }
    updateThreadLabels();  // Update the label to reflect the thread state
}

// Toggles the start/stop state of Thread3 when the button is clicked
// Works similarly to `toggleThread1`, either stopping or starting Thread3
void Program::toggleThread3(){
    if (thread3->running) {
        thread3->running = false;
        thread3->quit();
    } else {
        thread3->running = true;
        thread3->start();
    }
    updateThreadLabels();  // Update the label to reflect the thread state
}

// Updates the labels on the UI to show the running/stopped state of Thread1 and Thread3
// This gives visual feedback to the user about the current state of the threads
void Program::updateThreadLabels()
{
    if(thread1->running)
        thread1Label->setText("Thread 1 (Running)");
    else
        thread1Label->setText("Thread 1 (Stopped)");

    if(thread3->running)
        thread3Label->setText("Thread 3 (Running)");
    else
        thread3Label->setText("Thread 3 (Stopped)");
}
