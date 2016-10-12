#include "headers/consts.h"
#include "headers/gpsprint.h"
#include <iostream> 
#include <libgpsmm.h> 
#include <utility> 
#include <ctime> 
#include <iomanip> 

using namespace std;

void printData(gpsmm& gpsData) {
    time_t tim = time(nullptr);    
    cout << "Current time: " << put_time(gmtime(&tim), "%T") << endl;
}
