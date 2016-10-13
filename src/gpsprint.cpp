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
void printData(gpsmm& gpsData) {
    
    const char [] USED = {'N', 'Y'};
    time_t tim = time(nullptr);  

    double 	latititude; // DEBUG : storing vals if necessary -- to be simplified later
    double 	longitude;  // DEBUG : storing vals if necessary -- to be simplified later
    double 	altitude;   // DEBUG : storing vals if necessary -- to be simplified later
    double 	climb;   	// DEBUG : storing vals if necessary -- to be simplified late
    double 	timestamp;  // DEBUG : storing vals if necessary -- to be simplified later
	
	double  ssdB; 		// DEBUG : storing vals if necessary -- to be simplified later
	short 	PRN; 		// DEBUG : storing vals if necessary -- to be simplified later
	short 	elevation; 	// DEBUG : storing vals if necessary -- to be simplified later
	short 	azimuth; 	// DEBUG : storing vals if necessary -- to be simplified late
	bool 	isUsed; 		// DEBUG : storing vals if necessary -- to be simplified later
    
    //EY - 1 : May I ask, What is this one for?
    cout << "Current time: " << put_time(gmtime(&tim), "%T") << endl;
    
    if (gpsData.data()->satellites_visible > 0)
    {
    	cerr << "No satellites visible." << endl; 
    	return; //EY - 2: Erm.. is that all?
    }


    if(gpsData.data()->status == STATUS_NO_FIX /*0*/ )
    {
    	cout << "NO FIX." << endl;	
    	return; //EY - 3: should I retry here? 
    }
    else 
    {
	    timestamp = gpsData.data()->skyview_time;

    	if(gpsData.data()->fix.mode >1){ /* 2D or 3D */
		    latitiude = gpsData.data()->fix.latitude;
            longitude = gpsData.data()->fix.longitude;
    
             cout   << timestamp << ":" 
                    << " Longitude: " << longitude << ( longitude > 0 ? " N" : " S"); 
                    << " Latitude: "  << latitude  << ( latitude  > 0 ? " E" : " W");
                    << endl;

            if(gpsData.data()->fix.mode > 2){ /* 3D only */
                altitude  = gpsData.data()->fix.altitude;
                climb = gpsData.data()->fix.climb;
                
                cout << "Altitude: " << altitude
                     << "\tClimb: "  << climb
                     << endl;
            
            }
        }

        for(int i = 0; i < gpsData.data()->satellites_visible; ++i )
         {
            ssdB       = gpsData.data()->skyview[i].ss;
            PRN        = gpsData.data()->skyview[i].PRN;
            elevation  = gpsData.data()->skyview[i].elevation;
            azimuth    = gpsData.data()->skyview[i].azimuth;
            isUsed     = gpsData.data()->skyview[i].used;
        
            cout << "PRN:"              << PRN
                 << "\tElevatation: "   << elevation
                 << "\tAzimuth: "       << azimuth
                 << "\tSNR: "           << SNR
                 << "\tUsed: "          << USED[isUsed];
                 << "\n" << endl;  
         }

    }
 
}