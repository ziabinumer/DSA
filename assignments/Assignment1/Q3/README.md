# Process Priority Queue

## Overview
This C++ program implements a priority queue for process scheduling based on priority levels and timestamps. The queue is implemented as a doubly-linked list where processes are ordered first by their priority level (higher priority first) and then by timestamp (earlier timestamp first).

## Features
- Priority-based process scheduling
- Time-based tie-breaking for processes with same priority
- File-based input of process data
- Double-linked list implementation for efficient insertions

## Data Structures
The program uses several key data structures:

### Time Structure
- Stores hour, minute, and second
- Includes a comparison method to determine which time comes first

### ProcessData Structure
- Stores process information:
  - Priority level (integer)
  - Process name (string)
  - Timestamp (Time structure)

### Node Structure
- Container for ProcessData
- Includes pointers to next and previous nodes in the linked list

### Queue Class
- Manages the priority queue operations
- Implements:
  - Enqueue - Insert a process in priority order
  - Dequeue - Remove the highest priority process
  - isEmpty - Check if queue is empty
  - getFirst - Return the name of the highest priority process
  - printQueue - Display all processes in the queue

## File Format
The program reads process data from a file named `process.txt`. Each line in the file should follow this format:
```
process_name priority_level HH:MM:SS
```

Example:
```
Process1 10 14:30:00
Process2 5 12:15:30
Process3 10 12:00:00
```

## Usage
1. Prepare the `process.txt` file with your process data
2. Compile the program with a C++ compiler:
   ```
   g++ -o process_queue main.cpp
   ```
3. Run the executable:
   ```
   ./process_queue
   ```

## Algorithm Details
- When inserting a new process (Enqueue operation):
  1. If the queue is empty or the new process has higher priority than the front, insert at the front
  2. Otherwise, traverse the queue to find the correct position based on priority
  3. For processes with equal priority, position is determined by timestamp (earlier time comes first)

## Memory Management
The program includes proper memory cleanup in the Queue destructor to prevent memory leaks when the program terminates.