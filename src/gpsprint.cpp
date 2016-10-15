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


/*
#define DEFINE_MEMBER_CHECKER() \
    template < typename T, typename = void > \
    struct hasSkyview \
    : std::false_type { }; \
    template < typename T > \
    struct hasSkyview < T, decltype(std::declval<T>().skyview, void() )> \
        : std::true_type  { }; \

#define HAS_MEMBER() hasSkyview<gps_data_t>::value;

DEFINE_MEMBER_CHECKER(skyview)
*/

#define ENABLE_SKYVIEW
#ifdef ENABLE_SKYVIEW

#define ELEVATION   gpsData->skyview[i].ss;
#define SS_DB       gpsData->skyview[i].PRN;
#define PRN         gpsData->skyview[i].elevation;
#define AZIMUTH     gpsData->skyview[i].azimuth;
#define USED        gpsData->skyview[i].used;

#else

#define ELEVATION   gpsData->ss[i];
#define SS_DB       gpsData->PRN[i];
#define PRN         gpsData->elevation[i];
#define AZIMUTH     gpsData->azimuth[i];
#define USED        gpsData->used[i];

#endif

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
- additonal issues : compiler issue for undeclared data -- proposed solution -- preprocessor directives
--------------------------------------------------------------------------*/
void printData(struct gps_data_t * gpsData) {

    time_t tim = time(nullptr);



    //EY - 1 : May I ask, What is this one for?
    //JA This is to print out the current time is UTC. Don't know if we should use this vs the gps fix time, so I put this one here
    //EY - 1: Ah... I believe tihs is actually using the satellite time (we will probably need to parse it  from epoch time)
    cout << "Current time: " << put_time(gmtime(&tim), "%T") << endl;

    if (gpsData->satellites_visible < 0)
    {
      // cerr << "No satellites were visible." << endl;
      return;
    }

    if(gpsData->status == STATUS_NO_FIX /*0*/ )
    {
      cout << "NO FIX." << endl;
      return; //EY - 3: should I retry here? JA - Nope, Aman showed a screen of what a failure to get a fix looked like. We should porobably do that
    }

    else

    {
      double  timestamp;  // DEBUG : storing vals if necessary -- to be simplified later
      timestamp = gpsData->skyview_time;

      if (gpsData->fix.mode > 1){ /* 2D or 3D */
        double  latitude;   // DEBUG : storing vals if necessary -- to be simplified later
        double  longitude;  // DEBUG : storing vals if necessary -- to be simplified later

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
        printSatelliteHelper( PRN , ELEVATION , AZIMUTH , SS_DB , USED );
      }
    }
}

void printSatelliteDataHelper(short PRN,
                          short elevation,
                          short azimuth,
                          double ssdB,
                          bool isUsed)
{
    cout << "PRN:"              << PRN
         << "\tElevatation: "   << elevation
         << "\tAzimuth: "       << azimuth
         << "\tSNR: "           << ssdB
         << "\tUsed: "          << (isUsed? 'Y' : 'N');
         << endl << endl;
}
