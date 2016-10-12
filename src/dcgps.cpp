/*------------------------------------------------------------------------------
-- SOURCE FILE: dcgps.cpp.cpp - GPS Program Entrance
--
-- PROGRAM: dcgps.cpp
--
-- FUNCTIONS:
-- int  main 		( void )
-- void exitProgram ( void )
--
-- DATE: Oct. 10, 2016
--
-- REVISIONS: 
-- Version 1.0 Skeleton By JA
-- Version 1.1 Revision of Skeleton By EY
-
-- DESIGNER: JA / EY 
--
-- PROGRAMMER: 
--
-- NOTES:
-- References : https://github.com/jcable/gpsd/blob/master/libgpsmm.h
------------------------------------------------------------------------------*/

#include "headers/consts.h"
#include "headers/dcgps.h"
#include "headers/gps-utils.h"
#include <libgpsmm.h>
#include <iostream>
#include <string>

using namespace std;

/** EY - 2 : added a string const for easier management**/ 
static const string HOST = "localhost";


int main(void) {
	gpsmm gpsData(HOST.c_str(), DEFAULT_GPSD_PORT);     
    
    if (!gpsData.stream(WATCH_ENABLE | WATCH_JSON)) {
        cerr << "No GPSD running." << endl;
        return 1;

    }

    startReading(gpsData);
}

