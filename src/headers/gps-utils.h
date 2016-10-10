#ifndef GPS_UTILS_H
#define GPS_UTILS_H

#include <libgpsmm.h>
void startReading(gpsmm& gpsData);
void readLoop(gpsmm gpsData);

#endif
