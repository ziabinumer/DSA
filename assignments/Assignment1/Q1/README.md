# User Profile Management System (C++)

## Overview

This is a simple C++ console-based application that provides a basic user profile management system with login and registration functionality. Users can create accounts, log in, and manage their personal profiles. The system stores credentials in a text file (`credentials.txt`) and creates individual profile files for each user.

## Features

- User **Registration** (with username and numeric password)
- User **Login**
- **Profile Creation** (Reg No, Name, Father Name, Birth Date, Age, Class Name)
- **View Profile**
- **Overwrite Profile**
- Simple text-based **menu navigation**
- **Data validation** (for numeric password and input sanitization)
- **Cross-platform screen clearing** for both Windows and Linux/macOS

## How It Works

### Main Menu
- **1. Login** - Existing users can log in using their credentials.
- **2. Signup** - New users can register with a unique username and a numeric password between `10000` and `65000`.
- **3. Exit** - Exit the program.

### After Login
- **1. Show Profile** - Displays the saved profile data.
- **2. Overwrite Profile** - Allows the user to re-enter and overwrite existing profile information.
- **3. Exit to main menu** - Returns to the main menu.

### Data Storage
- Credentials are saved in `credentials.txt` in the format:  
- Each user has a separate profile file named `<username>.txt` containing their personal details.

## Files

- `main.cpp` - The main source code file containing the program logic.
- `credentials.txt` - Text file to store usernames and passwords.
- `<username>.txt` - Generated profile file for each registered user.

## Requirements

- C++11 or later
- Standard C++ libraries (`iostream`, `fstream`, `sstream`, `vector`, etc.)

## How to Run

1. Compile the code:
  ```bash
  g++ -o user_management main.cpp
  ```

2. Run the compiled program:
  ```bash
  ./user_management
  ```

### For Windows:
```bash
g++ -o user_management.exe main.cpp
user_management.exe

Notes
Passwords must be numeric and between 10000 and 65000.
Profile details are stored in plaintext files for simplicity (Not secure for production usage).
This is a basic demonstration and can be extended with better encryption, file handling, and error management.