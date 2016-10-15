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
-- REVISIONS: Version 1.1
--
-- DESIGNER: EY / JA
--
-- PROGRAMMER: v1.2 JA
-- v1.1 EY 
-- v1.0 - JA
--
-- INTERFACE: void printData (gpsmm&)
-- gpsData reference to a gpsmm object / instance
--
-- NOTES:
-- v.1  design is simple, jsut to ensure basic functionality works 
-- References: 
-- https://fossies.org/dox/gpsd-3.16/gps_8h_source.html#l02010
-- https://fossies.org/dox/gpsd-3.16/cgps_8c_source.html
--
-- ISSUE:
- r pi runs an older version of the api , and "skyview " variable is not found 
- proposed solution reference for cross - version compatibility: http://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class  
--------------------------------------------------------------------------*/

void printData(struct gps_data_t * gpsData) {
    //JA This is to print out the current time is UTC. Don't know if we should use this vs the gps fix time, so I put this one here
    //EY - 1: Ah... I believe tihs is actually using the satellite time (we will probably need to parse it  from epoch time) 
    //EY: NOTE ! put_time is not a decalred function in pi.... not sure why :S
    
    /*time_t tim = time(nullptr);
    cout << "Current time: " << put_time(gmtime(&tim), "%T") << endl;
    */
    
    if (gpsData->satellites_visible < 0)
    {
      return; 
    }

    if(gpsData->status == STATUS_NO_FIX /*0*/ )
    {
      cout << "n/a" << endl;  
      return; 
    }
    
    else 
    
    {
      timestamp = gpsData->skyview_time;

      if (gpsData->fix.mode > 1){ /* 2D or 3D */
      double  latitude;   // DEBUG : storing vals if necessary -- to be simplified later
      double  longitude;  // DEBUG : storing vals if necessary -- to be simplified later
      double  timestamp;  // DEBUG : storing vals if necessary -- to be simplified later
       
            latitude = gpsData->fix.latitude;
            longitude = gpsData->fix.longitude;
    
            cout   << timestamp << ":" 
                    << " Longitude: " << longitude << (longitude > 0 ? " N" : " S") 
                    << " Latitude: "  << latitude  << (latitude > 0 ? " E" : " W")
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
}
