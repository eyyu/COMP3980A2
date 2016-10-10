#include "headers/dcgps.h"
#include <libgpsmm.h>
#include <iostream>

using namespace std;

int main(void) {
    gpsmm gpsData("localhost", DEFAULT_GPSD_PORT); 
    
    if (!gpsData.stream(WATCH_ENABLE | WATCH_JSON)) {
        std::cerr << "No GPSD running." << std::endl;
        return 1;
    }
}
