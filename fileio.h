#ifndef FILEIO_H
#define FILEIO_H
#include "seats.h"

/* Saves all seats into a file */
int saveSeats(Seat** seats, int rows, const char* filename);

/* Loads seats from a file */
int loadSeats(Seat** seats, int rows, const char* filename);

#endif

