/*------------------------------------------------------------------------------
-- SOURCE FILE: dcgps.cpp.cpp - GPS Program Entrance
--
-- PROGRAM: dcgps.cpp
--
-- FUNCTIONS:
-- int  main 		( void )
--
-- DATE: Oct. 10, 2016
--
-- REVISIONS: 
-- Version 1.0 Skeleton By JA
-- Version 1.1 Revision of Skeleton By EY
-- Version 1.2 JA added help flag detection
--
-- DESIGNER: JA / EY 
--
-- PROGRAMMER: JA
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
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

static const string HOST = "localhost";
/*--------------------------------------------------------------------------
-- FUNCTION: main - program entrance
--
-- DATE: OCT. 12, 2016
--
-- REVISIONS: Set Version 2.0
--
-- DESIGNER: JA / EY
--
-- PROGRAMMER: JA
-- 
-- INTERFACE: int main(int argc, char **argv)
--
-- RETURNS: 
-- int signifying state at exit 
--------------------------------------------------------------------------*/
int main(int argc, char **argv) {
    if (argc > 1) {
       if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            cout << HELP_GUIDE << endl;
       } else {
            cout << "Did you mean \"-h\" or \"--help\"?" <<endl;
       }
       return 0;
    }

	gpsmm gpsData(HOST.c_str(), DEFAULT_GPSD_PORT);     
    
    if (!gpsData.stream(WATCH_ENABLE | WATCH_JSON)) {
        cerr << "No GPSD running." << endl;
        return 1;
    }

    startReading(gpsData);
}

