This file was generated with the help of AI

# Course Management System (BST + AVL)

## 📚 Overview
This project implements a **Course Management System** using:
- **Binary Search Tree (BST)**
- **AVL Tree** (self-balancing BST)

Each course has an ID and details. You can:
- Add new courses
- Delete existing courses
- Search for courses
- Display all courses (in ascending order)
- Display balance factors (in AVL)
- Display minimum/maximum course IDs
- Display total number of courses
- Display height of the tree

---

## 🛠 Project Structure

| File | Purpose |
|:-----|:--------|
| `Course.h` | Defines the `Course` class. |
| `BST.h / BST.cpp` | Defines the `BST` class for standard binary search tree operations. |
| `AVL.h / AVL.cpp` | Defines the `AVL` class (inherits BST) with balancing after insertion and deletion. |
| `main.cpp` | Provides a menu-driven interface for user interaction. |
| `build/` | Compiled files (executable `app`) are placed here. |

---

## ⚙️ How to Compile and Run

Make sure you have a C++ compiler installed (`g++` recommended).

### 1. Clone the project or download the files.

### 2. Use the provided Makefile:
```bash
make
```

### 3. Run the application:
```bash
./build/app
```

### 4. Clean the build files:
```bash
make clean
```

---

## 🧠 Important Notes

- **AVL Tree** prints:
  - The **balance factor** of each node after every insertion and deletion.
  - The **in-order traversal** of the tree after every insertion and deletion.
- **Balance Factor** = Height of Left Subtree - Height of Right Subtree.
- **AVL Rotations** (single/double) are automatically handled to maintain balance.

---

## 📋 Example Operations

- Add a new course.
- Delete a course by ID.
- Search for a course by ID.
- List all courses in ascending order.
- Show minimum and maximum course IDs.
- Show total number of courses.
- Show tree height.

---

## 📢 Author
This project was developed as a programming exercise for understanding 
**Data Structures** concepts like **BST** and **AVL Trees**.

