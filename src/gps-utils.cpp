/*------------------------------------------------------------------------------
-- SOURCE FILE: gps-utils.c - holds the read + utility functions for gps program
--
-- PROGRAM: gps-utils.cpp
--
-- FUNCTIONS:
-- void startReading (gpsmm& gpsData)
--
-- DATE: Oct. 16, 2016
--
-- REVISIONS: Version 2.0 for ncurses changes
-- version 1.5: Removed thread
--
--
-- DESIGNER: EY / JA
--
-- PROGRAMMER: JA
--
------------------------------------------------------------------------------*/
#include "headers/consts.h"
#include "headers/gps-utils.h"
#include "headers/gpsprint.h"
#include <iostream>
#include <libgpsmm.h>
#include <thread>
#include <utility>

using namespace std;
/*--------------------------------------------------------------------------
-- FUNCTION: startReading
--
-- DATE: OCT. 15, 2016
--
-- REVISIONS: Version 1.5
--
-- DESIGNER: JA
--
-- PROGRAMMER: JA
--
-- INTERFACE: void startReading (gpsmm& gpsData)
-- gpsData  the gps data struct that contains the information read
--
--
-- NOTES:
-- No thread required, adding a thread prevents a proper reading
--------------------------------------------------------------------------*/
void startReading(gpsmm& gpsData)
{
    struct gps_data_t *newData;
    for (;;)
    {

        if (!gpsData.waiting(50000000)) {
            continue;
        }
        if ((newData = gpsData.read()) == nullptr)
        {
            //Failure
            cerr << "Timeout on reading."
            return;
        } else {
            //Success
           printData(newData);
        }

        printData(newData);
    }
}
