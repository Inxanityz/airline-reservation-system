#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "seats.h"
#include "fileio.h"

/*
   Just checks if the row number the user gives is okay.
   Program only works with 5 to 10 rows, so this makes sure it's valid.
*/
int isValidRowCount(int rows)
{
    return (rows >= 5 && rows <= 10);
}

/*
   Main part of the whole program.
   It reads the user’s inputs, sets up the seat map, and shows a menu.
   Depending on what the user picks, to book, cancel, save, or load seats.
*/
int main(int argc, char* argv[])
{
    int rows;
    char* filename;
    Seat** seats;  // Declare dynamically allocated Seat array
    char command;
    int running = 1;   /* used to control the menu loop */

    /* Make sure the user typed the right number of arguments */
    if(argc != 3) {
        printf("Usage: ./ars <rows 5-10> <output_file>\n");
        return 1;
    }

    /* Turn the row argument (text) into a number */
    rows = atoi(argv[1]);

    /* Check if the row count is within the allowed range */
    if(!isValidRowCount(rows)) {
        printf("Row count must be between 5 and 10.\n");
        return 1;
    }

    /* Save the filename to use when saving later */
    filename = argv[2];

    /* Setup the random seed so the seats change every time you run it */
    srand(time(NULL));

    /* Make the seat map that the rest of the program uses */
    seats = createSeatMap(rows);  // Use dynamic allocation

    // Initialize the seating arrangement
    initializeSeating(seats, rows);

    /* Ask the user how many seats to pre-book as per Assignment 2 rules */
    int numSeats;
    printf("Enter number of seats to pre-book randomly: ");
    scanf("%d", &numSeats);

    // Book the random seats
    bookRandomSeats(seats, rows, numSeats);

    /* Main loop that shows the menu and waits for commands */
    while(running)
    {
        /* REFRESH: Show the seat layout on screen at the start of every loop */
        displaySeating(seats, rows);

        /* Menu options for the user */
        printf("Airline Reservation System:\n");
        printf("  b - Book a seat\n");
        printf("  c - Cancel a seat\n");
        printf("  s - Save to a file\n");
        printf("  l - Load from a file\n");
        printf("  q - Quit\n");
        printf("Enter choice: ");
        scanf(" %c", &command);

        /* Option to book a seat */
        if(command == 'b') {
            int br;
            char bc;
            char name[50];
            int age;

            /* 4.6 Booking: Single scanf for seat code */
            printf("Enter seat to book (ex: 3C): ");
            scanf("%d %c", &br, &bc);

            printf("Enter your name: ");
            scanf("%s", name);

            printf("Enter your age: ");
            scanf("%d", &age);

            int result = bookSeat(seats, rows, br, bc, name, age);

            if(result == 1)
                printf("Seat booked successfully!\n");
            else if(result == 0)
                printf("Seat already booked.\n");
            else
                printf("Invalid seat number.\n");
        }

        /* Option to cancel a seat */
        else if(command == 'c') {
            int cr;
            char cc;

            /* 4.7 Cancelling: Single scanf for seat code */
            printf("Enter seat to cancel (ex: 3C): ");
            scanf("%d %c", &cr, &cc);

            int result = cancelSeat(seats, rows, cr, cc);

            if(result == 1)
                printf("Seat cancelled.\n");
            else if(result == 0)
                printf("Seat is already available.\n");
            else
                printf("Invalid seat number.\n");
        }

        /* Option to save everything into the file */
        else if(command == 's') {
            if(saveSeats(seats, rows, filename))
                printf("Saved to %s.\n", filename);
            else
                printf("Error saving file.\n");
        }

        /* Option to load seats from the file */
        else if(command == 'l') {
            if(loadSeats(seats, rows, filename))
                printf("Loaded seats from %s.\n", filename);
            else
                printf("Error loading file.\n");
        }

        /* Quit the program */
        else if(command == 'q') {
            running = 0;  /* this stops the while loop */
        }

        /* If the user typed something not in the menu */
        else {
            printf("Invalid input, enter again.\n");
        }
    }

    /* Free the seat map memory before exiting */
    freeSeatMap(seats, rows);
    return 0;
}
