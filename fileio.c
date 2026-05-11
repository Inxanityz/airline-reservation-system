#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seats.h"

/*
   Saving in a File.
   Saves the complete booking information in the file provided via command line.
   Format: SeatCode Status Name Age (e.g., 1A 0 NA 0)
*/
int saveSeats(Seat** seats, int rows, const char* filename)
{
    FILE* f = fopen(filename, "w");
    int r, c;
    
    if(f == NULL) return 0;

    /* Loop through every single seat */
    for(r = 0; r < rows; r++) {
        for(c = 0; c < NUM_COLS; c++) {
            /* Format: <Row><Col> <Status> <Name> <Age>
               Example: 1A 0 NA 0 
            */
            fprintf(f, "%d%c %d %s %d\n", 
                    r + 1,           /* Row number */
                    'A' + c,         /* Column letter */
                    seats[r][c].bookingStatus, 
                    seats[r][c].Name, 
                    seats[r][c].age);
        }
    }

    fclose(f);
    return 1;  /* Successfully saved */
}

/*
   Loads booking info from the file to check if it is stored correctly.
   Matches the format used in saveSeats.
*/
int loadSeats(Seat** seats, int rows, const char* filename)
{
    FILE* f = fopen(filename, "r");
    int r, status, age;
    char col, name[50];

    if(f == NULL) return 0;

    /* Read every line from the file */
    while(fscanf(f, "%d%c %d %49s %d", &r, &col, &status, name, &age) == 5)
    {
        int c = letterToCol(col);
        /* Validate that the seat belongs in our current map size */
        if(r >= 1 && r <= rows && c >= 0 && c < NUM_COLS)
        {
            seats[r - 1][c].bookingStatus = status;
            strcpy(seats[r - 1][c].Name, name);
            seats[r - 1][c].age = age;
        }
    }

    fclose(f);
    return 1;
}
