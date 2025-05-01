This file was generated with the help of AI

# File System Hierarchy Simulator

A simple C++ terminal-based simulation of a file system that allows users to create folders and files, list contents, search, reset, and more—mimicking basic shell commands.

---

## 🛠 Features

- Create directories and files using `mkdir` and `touch`
- Display directory structure with `ls`
- Count all files and folders with `count`
- Search for files or folders by name
- Reset the entire virtual file system
- Clear screen (Linux/macOS only)

---

## 📂 Command List

| Command           | Description                              |
|------------------|------------------------------------------|
| `mkdir [path]`    | Create a new directory                   |
| `touch [path]`    | Create a new file                        |
| `ls [path]`       | List contents of a path (default: root)  |
| `search [name]`   | Search for a file or folder              |
| `count`           | Count all files and folders              |
| `reset`           | Delete all nodes and reset the FS        |
| `clear`           | Clear the terminal screen                |
| `quit`            | Exit the program                         |

---

## 📌 Notes

- The root directory must be created first: `mkdir root`
- Files must include an extension (e.g. `.txt`, `.cpp`)
- Folder names must **not** contain a dot (`.`)
- Paths must always begin with `root/`
- Duplicate file/folder names in the same directory are not allowed

---

## 🔧 Compilation & Running

Make sure you have a C++ compiler (like `g++`) installed.

```bash
g++ -o filesystem filesystem.cpp
./filesystem

```
## Sample Usage
```bash
$ mkdir root
$ mkdir root/projects
$ touch root/projects/main.cpp
$ ls
📁 root
  📁 projects
    📄 main.cpp
$ search main.cpp
Success: 1 matching results found
root/projects/main.cpp
$ count
Success: 3 files/folders found
$ reset
Success: Filesystem is reset
```
## Requirements
C++11 or above

Linux/macOS terminal for clear command to work (optional)

