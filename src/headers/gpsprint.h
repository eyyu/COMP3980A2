#ifndef GPSPRINT_H
#define GPSPRINT_H

#include <libgpsmm.h> 
#include <type_traits>

void printData(gps_data_t *gpsData);
void printToConsole(gps_data_t *gpsData);
void printSatelliteDataHelper(short PRN,
                         		short elevation,
                          		short azimuth, 
                          		double ssdB, 
                          		bool isUsed)

// template < typename T, typename = void > 
// struct hasSkyview 
// 	: std::false_type { };


// template < typename T >
// struct hasSkyview < T, decltype(std::declval<T>().skyview, void() )> 
// 	: std::true_type  { };

#endif



