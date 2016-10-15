#ifndef GPSPRINT_H
#define GPSPRINT_H

#include <libgpsmm.h> 

void printData(gps_data_t *gpsData);
void printToConsole(gps_data_t *gpsData);
void printSatelliteDataHelper(short PRN,
                          short elevation,
                          short azimuth, 
                          double ssdB, 
                          bool isUsed);

#endif
