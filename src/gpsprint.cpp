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
-- REVISIONS: Version 2.0 EY
-- v1   - JA
-- v1.1 - EY
--
-- DESIGNER: EY / JA
--
--
------------------------------------------------------------------------------*/

#include "headers/consts.h"
#include "headers/gpsprint.h"
#include "headers/map.h"
#include <iostream>
#include <libgpsmm.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <ncurses.h>
#include <string.h>
#include <string>


using namespace std;

static WINDOW * gpsWin, * mapWin , * satteliteWin;
static int win_width;
/*--------------------------------------------------------------------------
-- FUNCTION: printData
--
-- DATE: OCT. 12, 2016
--
-- REVISIONS: Version 1.2
--
-- DESIGNER: EY / JA
--
-- PROGRAMMER: 2.0 EY ( Ncurses implmentation)
-- v1.2 JA
-- v1.1 EY
-- v1.0 - JA
--
-- INTERFACE: void printData (struct gps_data_t * gpsData)
-- pointer to a struct containing the gps data received from the dongle
--
-- NOTES:
-- v.2 Ncurses Qui Implmentation with Ascii map plotting
-- v.1  design is simple, jsut to ensure basic functionality works
-- References:
-- https://fossies.org/dox/gpsd-3.16/gps_8h_source.html#l02010
-- https://fossies.org/dox/gpsd-3.16/cgps_8c_source.html
--------------------------------------------------------------------------*/

void printData(struct gps_data_t * gpsData) {
    mvprintw ( 1 , 1, "WELCOME TO DCGPS!");

    gpsWin = mapWin = satteliteWin = nullptr;

    static bool mapMade = false;
    static bool winMade = false;
    int height;
    getmaxyx(stdscr, height, win_width);
    if(!winMade)
    {
      gpsWin       = makeWin(gpsWin,
                            GPS_WIN_LINES,
                            win_width - 2,
                            Y_POS,
                            X_POS);

      mapWin       = makeWin(mapWin,
                              MAP_WIN_LINES,
                              win_width - 2,
                              GPS_WIN_LINES + Y_POS,
                              X_POS);

      satteliteWin = makeWin(satteliteWin,
                                SATTELITE_WIN_LINES,
                                win_width - 2,
                                GPS_WIN_LINES + MAP_WIN_LINES + Y_POS,
                                X_POS);
      winMade = true;
    }

    refresh();
    printGPSWin(gpsWin, gpsData);
    printSattelitesFound(satteliteWin, gpsData);

    if (gpsData->fix.mode > 1)
    {
      if(!mapMade)
      {
        printMapWin(mapWin, gpsData);
        mapMade = true;
      }
      return;
    }


}
 /*--------------------------------------------------------------------------
 -- FUNCTION: endInnerWin
 --
 -- DATE: OCT. 19, 2016
 --
 -- REVISIONS: Version 2.0
 --
 -- DESIGNER: Eva Yu
 --
 -- PROGRAMMER: Eva Yu
 --
 -- INTERFACE: [void] [endInnerWin] (void)
 --
 -- NOTES:
 -- kills all windows that are not needed
 --------------------------------------------------------------------------*/
void endInnerWin()
{
  delwin(gpsWin);
  delwin(satteliteWin);
  delwin(mapWin);
}

 /*--------------------------------------------------------------------------
 -- FUNCTION: makeWin
 --
 -- DATE: OCT. 19, 2016
 --
 -- REVISIONS: Version 2.0
 --
 -- DESIGNER: Eva Yu
 --
 -- PROGRAMMER: Eva Yu
 --
 -- INTERFACE: WINDOW * makeWin (WINDOW * win, int lines, int width, int x , int y)
 --
 -- NOTES:
 -- builds a window and displays border
 --------------------------------------------------------------------------*/
WINDOW * makeWin (WINDOW * win, int lines, int width, int x , int y)
{
  win = newwin(lines, width-1, x, y);
  box(win, 0 , 0);
  wrefresh(win);
  return win;
}

 /*--------------------------------------------------------------------------
 -- FUNCTION: printGPSWin
 --
 -- DATE: OCT. 19, 2016
 --
 -- REVISIONS: Version 2.0
 --
 -- DESIGNER: Eva Yu
 --
 -- PROGRAMMER: Eva Yu
 --
 -- INTERFACE: void printGPSWin(WINDOW * win, gps_data_t * gpsData)
 --
 -- NOTES:
 -- prints the GPS fix data
 --------------------------------------------------------------------------*/
void printGPSWin(WINDOW * win, gps_data_t * gpsData)
{
  time_t timestamp = static_cast<time_t>(gpsData->skyview_time);
  if(gpsData->status == 0)
  {
    mvwprintw ( win, 1 , 1,         "Timestamp:\t NO FIX");
    mvwprintw ( win, 3 , 1,         "Longitude:\t%f", 0.0);
    mvwprintw ( win, 3 , win_width / 2, "Latitude:\t%f" , 0.0);
    mvwprintw ( win, 5 , 1,         "Altitude:\t%f" , 0.0);
    mvwprintw ( win, 5 , win_width / 2, "Climb:\t%f"    , 0.0);
    wrefresh(win);
  }
  else
  {
    mvwprintw ( win, 1 , 1,         "Timestamp:\t%s",
                                      put_time(gmtime(&timestamp), "%T"));
    mvwprintw ( win, 3 , 1,         "Longitude:\t%f %c",gpsData->fix.longitude,
                                    (gpsData->fix.longitude > 0 ? 'E': 'W'));
    mvwprintw ( win, 3 , win_width / 2, "Latitude:\t%f%c" , gpsData->fix.latitude,
                                    (gpsData->fix.latitude  > 0 ? 'N': 'S'));

    if(gpsData->fix.mode > 2) {
        mvwprintw ( win, 5 , 1,         "Altitude:\t%f" , gpsData->fix.altitude);
        mvwprintw ( win, 5 , win_width / 2, "Climb:\t%f" , gpsData->fix.climb);
    }

  }
  wrefresh(win);
}

 /*--------------------------------------------------------------------------
 -- FUNCTION: printSatteliteWin
 --
 -- DATE: OCT. 19, 2016
 --
 -- REVISIONS: Version 2.0
 --
 -- DESIGNER: Eva Yu
 --
 -- PROGRAMMER: Eva Yu
 --
 -- INTERFACE: void printSatteliteWin(WINDOW * win, gps_data_t * gpsData)
 --
 -- NOTES:
 -- prints the GPS sattellites labels
 --------------------------------------------------------------------------*/

void printSatteliteWin(WINDOW * win)
{
  refresh();
  mvwprintw ( win, 1 , 1,             "PRN:");
  mvwprintw ( win, 1 , win_width / 5,     "Elevation:");
  mvwprintw ( win, 1 , win_width / 5 * 2, "Azimuth:");
  mvwprintw ( win, 1 , win_width / 5 * 3, "SNR:" );
  mvwprintw ( win, 1 , win_width / 5 * 4, "Used:");
  wrefresh  ( win );
}

 /*--------------------------------------------------------------------------
 -- FUNCTION: printSattelitesFound
 --
 -- DATE: OCT. 19, 2016
 --
 -- REVISIONS: Version 2.0
 --
 -- DESIGNER: Eva Yu
 --
 -- PROGRAMMER: Eva Yu
 --
 -- INTERFACE: void printSattelitesFound(WINDOW * win, gps_data_t * gpsData)
 --
 -- NOTES:
 -- prints the GPS sattellites data ( skyview is gpsd version dependent)
 --------------------------------------------------------------------------*/
void printSattelitesFound(WINDOW * win, gps_data_t * gpsData)
{
  refresh();
  printSatteliteWin(win);
  int line = 3;
//  for(int i = 0; i < gpsData->satellites_visible; ++i, ++line)
  for (int i = 0; i < gpsData->satellites_visible; ++i, ++line)
  {
    // mvwprintw ( win, line, 1,              "%d", gpsData->skyview[i].PRN );
    // mvwprintw ( win, line, win_width / 5,      "%d", gpsData->skyview[i].elevation );
    // mvwprintw ( win, line, win_width / 5 * 2,  "%d", gpsData->skyview[i].azimuth );
    // mvwprintw ( win, line, win_width / 5 * 3,  "%f", gpsData->skyview[i].ss );
    // mvwprintw ( win, line, win_width / 5 * 4,  (gpsData->skyview[i].used ? "Y" : "N") );

    mvwprintw ( win, line, 1,              "%f", gpsData->PRN[i] );
    mvwprintw ( win, line, win_width / 5,      "%d", gpsData->elevation[i] );
    mvwprintw ( win, line, win_width / 5 * 2,  "%d", gpsData->azimuth[i] );
    mvwprintw ( win, line, win_width / 5 * 3,  "%d", gpsData->ss[i] );
    mvwprintw ( win, line, win_width / 5 * 4,  (gpsData->used[i]? "Y" : "N") );
  }
  wrefresh(win);
}

void printMapWin(WINDOW * win, gps_data_t * gpsData)
{
  double longitude, latitude;
  longitude = gpsData->fix.longitude;
  latitude  = gpsData->fix.latitude;

  const char * marker = "\033[38;5;196mX\033[0m"; // the linux ascii colored string
  string mapStr = getMap(longitude,latitude); // get string representing map

  char mapStrPtr [mapStr.length() + 1]; // reserve char array for string
  strcpy(mapStrPtr, mapStr.c_str());    // copy the string

  char * mapline = strtok(mapStrPtr, " ");
  int y = 0, x = 1;

  while (mapline != NULL ) {
    char * xPtr;

    //Check to see if line has the marker string to get rid of it
    if( ( xPtr = strstr(mapline, marker) ) != nullptr) {

        init_pair(3, COLOR_RED,   COLOR_BLACK);
        char  substr [256];
        int colOfX = (xPtr - mapline) / sizeof(char);
        strncpy(substr, mapline, colOfX - 1);


        /*first half of string BEFORE MARKER*/
        mvwprintw( win, ++y , x, substr );

        /*READ x at marker*/
        wattron(win, COLOR_PAIR(3));
        mvwaddstr( win, y , colOfX, "X" );
        wattroff(win, COLOR_PAIR(3));

        /* second half of string after marker*/
        strncpy(substr, 
            xPtr + strlen(marker),
            strlen(mapline) - strlen(marker) - colOfX + 1 );
        
        mvwprintw( win, y , colOfX+1 , substr );
    }
    else
    {
      mvwaddstr( win, ++y , x, mapline );
    }

      mapline = strtok(NULL, "\n");
  }


  wrefresh(win);
}
