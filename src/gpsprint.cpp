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
-- PROGRAMMER: v1.1 EY 
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
--------------------------------------------------------------------------*/
void printData(struct gps_data_t * gpsData) {
    //JA - Use enum class instead of const char array - Provides more meaning than arbitrary N and Y
    const char USED[2] {'N', 'Y'};
    time_t tim = time(nullptr);

    //JA - If you need to store values for repeated use, define them with the smallest necessary scope
    double 	latitude; // DEBUG : storing vals if necessary -- to be simplified later
    double 	longitude;  // DEBUG : storing vals if necessary -- to be simplified later
    double 	timestamp;  // DEBUG : storing vals if necessary -- to be simplified later
	
	double  ssdB; 		// DEBUG : storing vals if necessary -- to be simplified later
	short 	PRN; 		// DEBUG : storing vals if necessary -- to be simplified later
	short 	elevation; 	// DEBUG : storing vals if necessary -- to be simplified later
	short 	azimuth; 	// DEBUG : storing vals if necessary -- to be simplified late
	bool 	isUsed; 	// DEBUG : storing vals if necessary -- to be simplified later
    
    //EY - 1 : May I ask, What is this one for?
    //JA This is to print out the current time is UTC. Don't know if we should use this vs the gps fix time, so I put this one here
    cout << "Current time: " << put_time(gmtime(&tim), "%T") << endl;
    
    if (gpsData->satellites_visible < 0)
    {
    	cerr << "No satellites visible." << endl; 
    	return; //EY - 2: Erm.. is that all? JA - Probably yes. Either return or print nothing like Aman showed in the example
    }

    if(gpsData->status == STATUS_NO_FIX /*0*/ )
    {
    	cout << "NO FIX." << endl;	
    	return; //EY - 3: should I retry here? JA - Nope, Aman showed a screen of what a failure to get a fix looked like. We should porobably do that
    }
    else 
    {
	    timestamp = gpsData->skyview_time;

    	if (gpsData->fix.mode >1){ /* 2D or 3D */
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
            ssdB       = gpsData->skyview[i].ss;
            PRN        = gpsData->skyview[i].PRN;
            elevation  = gpsData->skyview[i].elevation;
            azimuth    = gpsData->skyview[i].azimuth;
            isUsed     = gpsData->skyview[i].used;
        
            cout << "PRN:"              << PRN
                 << "\tElevatation: "   << elevation
                 << "\tAzimuth: "       << azimuth
                 << "\tSNR: "           << ssdB
                 << "\tUsed: "          << USED[isUsed]
                 << endl << endl;  
        }
    }
}
