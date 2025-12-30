# Room Management System

A simple C program for managing rooms and room members.

## Overview

room-manage is a command-line application written in C.  
It provides basic room management and member management functionality.

## Project Structure

```
.
├── bin/
│   └── build
├── src/
│   └── *.c
├── include/
│   └── *.h
├── scripts/
│   └── *.sh
├── README.md
```

## Build

This project does not include a Makefile.

Build the executable using the provided bash script:

```
chmod +x bin/build
./bin/build
```

The build process outputs the executable:

```
room-manage
```

## Run

```
./room-manage
```

## Notes

- Header files are located in `include/`
- Source files are located in `src/`
- You may create your own Makefile if needed
