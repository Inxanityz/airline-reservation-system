#ifndef SEATS_H
#define SEATS_H

/* Total columns across the plane (A through F) */
#define NUM_COLS 6

/* The data stored for every single seat */
typedef struct {
    int bookingStatus;  /* 0 means empty, 1 means taken */
    char Name[50];      /* Name of the passenger */
    int age;            /* Age of the passenger */
} Seat;

/* Creates the seating chart in memory */
Seat** createSeatMap(int rows);

/* Cleans up and frees the memory for the chart */
void freeSeatMap(Seat** seats, int rows);

/* Changes letters like 'A' or 'B' into numbers like 0 or 1 */
int letterToCol(char c);

/* Saves a booking into a specific seat */
int bookSeat(Seat** seats, int rows, int row, char col, const char* name, int age);

/* Removes a booking and makes the seat empty again */
int cancelSeat(Seat** seats, int rows, int row, char col);

/* Sets every seat in the chart to "NA" and status 0 */
void initializeSeating(Seat** seats, int rows);

/* Randomly fills some seats with "Prebooked" passengers */
void bookRandomSeats(Seat** seats, int rows, int numSeats);

/* Prints the seating chart onto the terminal screen */
void displaySeating(Seat** seats, int rows);

#endif
