#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "seats.h"

/* Makes the 2D seat map and sets defaults to NA/0 */
Seat** createSeatMap(int rows)
{
    int i, j;
    Seat** seats = (Seat**)malloc(rows * sizeof(Seat*));
    for(i = 0; i < rows; i++) {
        seats[i] = (Seat*)malloc(NUM_COLS * sizeof(Seat));
        for(j = 0; j < NUM_COLS; j++) {
            seats[i][j].bookingStatus = 0;
            strcpy(seats[i][j].Name, "NA");
            seats[i][j].age = 0;
        }
    }
    return seats;
}

/* Frees all memory used by the seat map */
void freeSeatMap(Seat** seats, int rows)
{
    int i;
    for(i = 0; i < rows; i++)
        free(seats[i]);
    free(seats);
}

/* Turns a seat letter (A-F) into a number (0-5) */
int letterToCol(char c) {
    if (c >= 'A' && c <= 'F') return c - 'A';
    if (c >= 'a' && c <= 'f') return c - 'a';
    return -1;
}

/* Books a seat: Checks validity, availability, then updates struct */
int bookSeat(Seat** seats, int rows, int row, char col, const char* name, int age)
{
    int c = letterToCol(col);
    int r = row - 1;

    if (r < 0 || r >= rows || c < 0 || c >= NUM_COLS) return -1;
    if (seats[r][c].bookingStatus == 1) return 0;

    seats[r][c].bookingStatus = 1;
    strncpy(seats[r][c].Name, name, 49);
    seats[r][c].Name[49] = '\0';
    seats[r][c].age = age;

    return 1;
}

/* Cancels a seat: Resets to NA and 0 */
int cancelSeat(Seat** seats, int rows, int row, char col)
{
    int c = letterToCol(col);
    int r = row - 1;

    if (r < 0 || r >= rows || c < 0 || c >= NUM_COLS) return -1;
    if (seats[r][c].bookingStatus == 0) return 0;

    seats[r][c].bookingStatus = 0;
    strcpy(seats[r][c].Name, "NA");
    seats[r][c].age = 0;

    return 1;
}

/* Sets all seats to Available/NA/0 */
void initializeSeating(Seat** seats, int rows) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            seats[i][j].bookingStatus = 0;
            strcpy(seats[i][j].Name, "NA");
            seats[i][j].age = 0;
        }
    }
}

/* Books random seats based on user input */
void bookRandomSeats(Seat** seats, int rows, int numSeats)
{
    int booked = 0;
    while (booked < numSeats && booked < (rows * NUM_COLS)) {
        int r = rand() % rows;
        int c = rand() % NUM_COLS;
        if (seats[r][c].bookingStatus == 0) {
            seats[r][c].bookingStatus = 1;
            strcpy(seats[r][c].Name, "Prebooked");
            seats[r][c].age = 18;
            booked++;
        }
    }
}

/* Displays the seat map showing status as 0 or 1.
   Example: 1A(0) 1B(1) 
*/
void displaySeating(Seat** seats, int rows) {
    printf("\n   AIRLINE SEATING MAP (0: Available, 1: Booked)\n\n");
    for (int r = 0; r < rows; r++) {
        printf("Row %d: ", r + 1);
        for (int c = 0; c < NUM_COLS; c++) {
            char letter = 'A' + c;
            /* Fulfills criteria: status is printed directly as 0 or 1 */
            printf("%d%c(%d) ", r + 1, letter, seats[r][c].bookingStatus);
        }
        printf("\n");
    }
}
