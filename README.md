# ThreadQueueApp

## Project Overview
This project is a multi-threaded C++ Qt window application that demonstrates thread communication and synchronization. The application consists of three threads:

1. A number generator that produces incrementing integers.
2. A queue manager operating as a FIFO buffer that holds up to 20 numbers, replacing the oldest number when the buffer is full.
3. A number consumer that retrieves numbers from the queue for further processing.
The user can control the start and stop functionality of the number generation and consumption threads via a graphical interface. The application visually displays the numbers handled by each thread, with frequent updates to ensure real-time reflection of the threads' states.

##Features
- Threaded Number Generation: A thread continuously generates numbers, which can be started and stopped through the GUI.
- FIFO Queue Management: A thread manages a queue with a maximum of 20 numbers, replacing the oldest when full.
- Threaded Number Consumption: Another thread retrieves and processes numbers from the queue, with the ability to start and stop via the GUI.
- GUI Control: The application includes buttons for starting and stopping the number generation and consumption threads.
- Real-Time Display: Three list boxes display the numbers associated with each thread, with updates at several times per second to reflect the latest state of each thread.

## Requirements
- C++
- Qt Creator
