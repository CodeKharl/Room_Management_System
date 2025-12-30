Room Management System (C)

A simple command-line program written in C for managing rooms and their members.
The application supports creating, updating, viewing, and deleting rooms, as well as managing members associated with each room.

This project is intended for learning and basic system design practice.

Features

Add, remove, update, and view rooms

Manage room members (add, remove, update, view)

Modular project structure using source and header files

Bash-based build system

Project Structure
.
├── bin/
│   └── build            # Bash script to build the executable
├── src/
│   └── *.c              # Source files
├── include/
│   └── *.h              # Header files
├── scripts/
│   └── *.sh             # Optional helper scripts
├── README.md


Header files are located in the include/ directory

Source files are located in the src/ directory

Requirements

GCC or any compatible C compiler

Bash shell

Linux / Unix-like operating system

Building the Program

This project does not include a Makefile.
Instead, it uses a Bash build script.

Make sure the build script is executable:

chmod +x ./bin/build


Build the project using:

./bin/build


The script compiles all source files and generates the executable.

Running the Program

After building, run the executable:

./room-manage

Notes

No external libraries are required

Users are free to create their own Makefile if desired

Designed to be simple, modular, and easy to extend
