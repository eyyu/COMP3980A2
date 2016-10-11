#include "headers/gps-utils.h"
#include <iostream> 
#include <libgpsmm.h> 
#include <thread> 
#include <utility> 

using namespace std;

void startReading(gpsmm& gpsData) 
{
    thread readThread(readLoop, gpsData);
}

/*
 * Left incomplete atm because I'm not sure how to check if read fails with gpsmm
 * Documentation suggests that it returns null on failure, but it might also return void
 * No obvious last error method to call either
 */
void readLoop(gpsmm gpsData) 
{
    for (;;) 
    {
        if (!gpsData.read()) 
        {

        }
    }
}
