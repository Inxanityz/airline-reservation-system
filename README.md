# Airline Reservation System

A command-line seat booking system written in C, split across multiple source files.

## Features
- Book and cancel seats on a row-by-column grid (A-F)
- Random seat pre-booking for simulation
- Visual seat map display
- Persistent seat data via file I/O (save/load)
- Dynamic memory allocation for seat grid

## Architecture
- `main.c` — program entry point and menu logic
- `seats.c` / `seats.h` — seat booking, cancellation, and display
- `fileio.c` / `fileio.h` — file read/write operations
- `Makefile` — compilation rules

## Tech
- C (compiled with gcc)
- Make

## Build and Run
make
./ars
