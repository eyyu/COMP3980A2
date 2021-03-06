/*------------------------------------------------------------------------------
-- SOURCE FILE: gpsprint.cpp - print and display functions for gps program
--
-- PROGRAM: gpsprint
--
-- FUNCTIONS:
-- void printData (gpsmm&)
--
--
-- DATE: Oct. 12, 2016
--
-- REVISIONS: 
-- v1   - JA
-- v1.1 - EY
--
-- DESIGNER: EY / JA
--
--
------------------------------------------------------------------------------*/

#include "headers/consts.h"
#include "headers/gpsprint.h"
#include <iostream> 
#include <libgpsmm.h> 
#include <utility> 
#include <ctime> 
#include <iomanip> 

using namespace std;

/*--------------------------------------------------------------------------
-- FUNCTION: printData
--
-- DATE: OCT. 12, 2016
--
-- REVISIONS: Version 1.2
--
-- DESIGNER: EY / JA
--
-- PROGRAMMER: v1.2 JA
-- v1.1 EY 
-- v1.0 - JA
--
-- INTERFACE: void printData (struct gps_data_t * gpsData)
-- pointer to a struct containing the gps data received from the dongle
--
-- NOTES:
-- v.1  design is simple, jsut to ensure basic functionality works 
-- References: 
-- https://fossies.org/dox/gpsd-3.16/gps_8h_source.html#l02010
-- https://fossies.org/dox/gpsd-3.16/cgps_8c_source.html
--
-- ISSUE:
-- raspberry pi runs an older version of the api, and "skyview" variable is not found 
-- proposed solution reference for cross - version compatibility: http://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class  
--------------------------------------------------------------------------*/

void printData(struct gps_data_t * gpsData) {
    if (gpsData->satellites_visible < 0)
    {
      return; 
    }

    if (gpsData->status == STATUS_NO_FIX /*0*/ )
    {
        cout << "n/a" << endl;  
        return; 
    }
    if (gpsData->fix.mode > 1){ /* 2D or 3D */
        double latitude = gpsData->fix.latitude;
        double longitude = gpsData->fix.longitude;
        time_t timestamp = static_cast<time_t>(gpsData->skyview_time);
        cout   << put_time(gmtime(&timestamp), "%T") << ":" 
                << " Longitude: " << longitude << (longitude < 0 ? " N" : " S") 
                << " Latitude: "  << latitude  << (latitude < 0 ? " E" : " W")
                << endl;

        if(gpsData->fix.mode > 2) { /* 3D only */
            cout << "Altitude: " << gpsData->fix.altitude
                 << "\tClimb: "  << gpsData->fix.climb
                 << endl;
        }
    }

    for(int i = 0; i < gpsData->satellites_visible; ++i)
    {
        double  ssdB;     // DEBUG : storing vals if necessary -- to be simplified later
        short   PRN;    // DEBUG : storing vals if necessary -- to be simplified later
        short   elevation;  // DEBUG : storing vals if necessary -- to be simplified later
        short   azimuth;  // DEBUG : storing vals if necessary -- to be simplified late
        bool  isUsed;   // DEBUG : storing vals if necessary -- to be simplified later
        
        ssdB       = gpsData->ss[i];
        PRN        = gpsData->PRN[i];
        elevation  = gpsData->elevation[i];
        azimuth    = gpsData->azimuth[i];
        isUsed     = gpsData->used[i];

        cout << "PRN:"              << PRN
             << "\tElevatation: "   << elevation
             << "\tAzimuth: "       << azimuth
             << "\tSNR: "           << ssdB
             << "\tUsed: "          << (isUsed? 'Y' : 'N')
               << endl;  
    }
    cout << endl;
}
