# Expression Converter (Infix, Prefix, Postfix) in C++

## Overview

This C++ console application converts mathematical expressions between infix, prefix, and postfix notations. The program reads expressions from a file and writes the converted result into corresponding output files.

## Features

- **Infix to Postfix conversion**
- **Infix to Prefix conversion**
- **Postfix to Infix conversion**
- **Prefix to Infix conversion**
- Reads input expressions from text files (`infix.txt`, `postfix.txt`, or `prefix.txt`)
- Writes converted output to corresponding files (`postfix.txt`, `prefix.txt`, `infix.txt`, or `infix2.txt`)
- Implements a **stack using a Linked List**

## Supported Operators

- `+` (Addition)
- `-` (Subtraction)
- `*` (Multiplication)
- `/` (Division)
- `%` (Modulo)

## Usage

### How to Compile

```bash
g++ -o expression_converter main.cpp

### How to run
./expression_converter infix.txt
./expression_converter postfix.txt
./expression_converter prefix.txt