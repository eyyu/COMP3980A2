// #include <ncurses.h>
// #include <string.h>
// #include <string>
// #include "headers/map.h"
// #include <libgpsmm.h>
//
// using namespace std;
// //DUMMY DATA
// string timestampTest   = "09/11/2016 14:16:00:00";
// double altitude    = 1234567;
// double longitude   = -34.32755;
// double latitude    = -14.24658;
// short  elevation[] = { 123, 456, 765};
// short  azimuth[]   = { 45, 56, 78};
// double SNR[]       = { 47.1, 16.8, 34.5};
// short  PNR[]       = { 10, 4, 27};
// bool   USED[]      = { true, true, true};
//
// // USED DATA
// int width;
// int height;
// int X_POS = 1;
// int Y_POS = 2;
//
// int gpsWin_nlines = 8;
// int gpsWin_display_nlines = 6;
// int gpsWin_timestamp_nlines = 1;
// int gpsWin_longLat_nlines   = 3;
// int gpsWin_altClimb_nlines  = 5;
//
// int mapWin_lines = 17;
//
// int satteliteWin_lines        = 15;
// int satteliteWin_PRN_x        = 1;
// int satteliteWin_altitude_x   = 5;
// int satteliteWin_SN_x         = 15;
// int satteliteWin_elevation_x  = 25;
// int satteliteWin_used_x       = 35;



// WINDOW *  makeWin (WINDOW * win, int lines, int width, int x , int y);
// void printGPSWin(WINDOW * win);
// void printSatteliteWin(WINDOW * win);
// void printMapWin(WINDOW * win);
// void printSattelitesFound(WINDOW * win, gps_data_t * gpsData);
// int main (void)
// {
//   WINDOW * gpsWin, * mapWin , * satteliteWin;
//   gpsWin = mapWin = satteliteWin = nullptr;
//
//   initscr();  // creates a standard screen
//   cbreak();
//   clear();
//   noecho();
//
//   start_color();
//
//   /*FOR NO FIX */
//   init_pair(1, COLOR_GREEN, COLOR_BLACK);
//   init_pair(2, COLOR_WHITE, COLOR_BLUE);
//   init_pair(3, COLOR_RED,   COLOR_BLACK);
//
//   getmaxyx(stdscr, height, width);
//
//   refresh();
//
//   gpsWin       = makeWin(gpsWin,
//                         gpsWin_nlines,
//                         width - 2,
//                         Y_POS,
//                         X_POS);
//
//   mapWin       = makeWin(mapWin,
//                           mapWin_lines,
//                           width - 2,
//                           gpsWin_nlines + Y_POS,
//                           X_POS);
//
//   satteliteWin = makeWin(satteliteWin,
//                             gpsWin_nlines,
//                             width - 2,
//                             gpsWin_nlines + mapWin_lines + Y_POS, X_POS);
//
//   printGPSWin(gpsWin);
//   printMapWin(mapWin);
//   printSattelitesFound(satteliteWin, nullptr);
//
//   refresh();
//
//   getch();    //ensures it does not close
//   delwin(gpsWin);
//   delwin(satteliteWin);
//   delwin(mapWin);
//   endwin(); // close window
//
// }

// WINDOW * makeWin (WINDOW * win, int lines, int width, int x , int y)
// {
//   win = newwin(lines, width-1, x, y);
//   box(win, 0 , 0);
//   wrefresh(win);
//   return win;
// }
//
// void printGPSWin(WINDOW * win)
// {
//   refresh();
//   string times = "Timestamp:\t" + timestampTest;
//   mvwaddstr ( win, 1 , 1,         times.c_str());
//   mvwprintw ( win, 3 , 1,         "Longitude:\t%f", longitude);
//   mvwprintw ( win, 3 , width / 2, "Latitude:\t%f" , latitude);
//   mvwprintw ( win, 5 , 1,         "Altitude:\t%f" , altitude);
//   wrefresh(win);
// }
//
// void printSatteliteWin(WINDOW * win)
// {
//   refresh();
//   mvwprintw ( win, 1 , 1,             "PRN");
//   mvwprintw ( win, 1 , width / 5,     "Elevation");
//   mvwprintw ( win, 1 , width / 5 * 2, "Azimuth");
//   mvwprintw ( win, 1 , width / 5 * 3, "SNR:" );
//   mvwprintw ( win, 1 , width / 5 * 4, "Used:");
//   wrefresh  ( win );
// }
//
// void printSattelitesFound(WINDOW * win, gps_data_t * gpsData)
// {
//   refresh();
//   printSatteliteWin(win);
//   int line = 3;
// //  for(int i = 0; i < gpsData->satellites_visible; ++i, ++line)
//   for (int i = 0; i < 3; ++i, ++line)
//   {
//     mvwprintw ( win, line, 1,              "%d", PNR[i] );
//     mvwprintw ( win, line, width / 5,      "%d", elevation[i] );
//     mvwprintw ( win, line, width / 5 * 2,  "%d", azimuth[i] );
//     mvwprintw ( win, line, width / 5 * 3,  "%f", SNR[i] );
//     mvwprintw ( win, line, width / 5 * 4,  (USED[i]? "Y" : "N") );
//
//     // mvwprintw ( win, line, 1,              "%f", gpsData->PRN[i] );
//     // mvwprintw ( win, line, width / 5,      "%d", gpsData->elevation[i] );
//     // mvwprintw ( win, line, width / 5 * 2,  "%d", gpsData->azimuth[i] );
//     // mvwprintw ( win, line, width / 5 * 3,  "%d", gpsData->ss[i] );
//     // mvwprintw ( win, line, width / 5 * 4,  (gpsData->used[i]? "Y" : "N") );
//   }
//   wrefresh(win);
// }
//
// void printMapWin(WINDOW * win)
// {
//   const char * marker = "\033[38;5;196mX\033[0m";
//   string mapStr = getMap(longitude,latitude); // get string representing map
//
//   char mapStrPtr [mapStr.length() + 1]; // reserve char array for string
//   strcpy(mapStrPtr, mapStr.c_str());    // copy the string
//
//   char * mapline = strtok(mapStrPtr, " ");
//   int y = 0, x = 1;
//
//   while (mapline != NULL ) {
//     char * xPtr;
//     if( ( xPtr = strstr(mapline, marker) ) != nullptr) {
//
//         init_pair(3, COLOR_RED,   COLOR_BLACK);
//         char  substr [256];
//         int colOfX = (xPtr - mapline) / sizeof(char);
//         strncpy(substr, mapline, colOfX - 1);
//
//
//         /*first half of string BEFORE MARKER*/
//         mvwprintw( win, ++y , x, substr );
//
//         /*READ x at marker*/
//         wattron(win, COLOR_PAIR(3));
//         mvwaddstr( win, y , colOfX, "X" );
//         wattroff(win, COLOR_PAIR(3));
//
//         /* second half of string after marker*/
//         strncpy(substr, xPtr + strlen(marker), strlen(mapline) - strlen(marker) - colOfX + 1 );
//         mvwprintw( win, y , colOfX+1 , substr );
//     }
//     else
//     {
//       mvwaddstr( win, ++y , x, mapline );
//     }
//
//       mapline = strtok(NULL, "\n");
//   }
//
//
//   wrefresh(win);
// }
