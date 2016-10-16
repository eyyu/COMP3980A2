#include "headers/consts.h"
#include "headers/gps-utils.h"
#include "headers/gpsprint.h"
#include <iostream> 
#include <libgpsmm.h> 
#include <thread> 
#include <utility> 

using namespace std;

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
        } else {
            //Success
           printData(newData);
        }
    }
}
