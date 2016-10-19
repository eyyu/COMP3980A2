#ifndef GPSPRINT_H
#define GPSPRINT_H

#include <libgpsmm.h>
#include <ncurses.h>

void printData(gps_data_t *gpsData);
void printToConsole(gps_data_t *gpsData);

WINDOW *  makeWin (WINDOW * win, int lines, int width, int x , int y);

void printGPSWin(WINDOW * win, gps_data_t * gpsData);
void printSatteliteWin(WINDOW * win);
void printMapWin(WINDOW * win, gps_data_t * gpsData);
void printSattelitesFound(WINDOW * win, gps_data_t * gpsData);
void endInnerWin();
#endif
