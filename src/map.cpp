/*------------------------------------------------------------------------------
-- SOURCE FILE: gpsprint.cpp - print and display functions for gps program
--
-- PROGRAM: gpsprint
--
-- FUNCTIONS:
-- string getMap (const double latitude, const double longitude)
--
--
-- DATE: Oct. 17, 2016
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
#include "headers/map.h"
#include <iostream>
#include <libgpsmm.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <cstdarg>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

/*--------------------------------------------------------------------------
-- FUNCTION: getMap
--
-- DATE: OCT. 18, 2016
--
-- REVISIONS: Set Version 2.0
--
-- DESIGNER: John A
--
-- PROGRAMMER: John A
--
-- INTERFACE: string getMap(const double latitude, const double longitude)
--
-- RETURNS: 
-- a string calue representing the entire ascii map
--
-- NOTES:
-- using the asciiworld as a lib : https://github.com/vain/asciiworld 
--------------------------------------------------------------------------*/
string getMap(const double latitude, const double longitude) {
    FILE *in;
    char buff[512];
    stringstream output;

    fstream coordFile("coords.txt", ios_base::in | ios_base::out | ios_base::trunc);
    coordFile << "points" << endl  << latitude << " " << longitude << endl;
    coordFile.close();

    if(!(in = popen("./asciiworld.exe -h 14 -l coords.txt", "r"))){
        return "";
    }

    while(fgets(buff, sizeof(buff), in)!=NULL){
        output << buff;
    }
    pclose(in);


    //execl("../asciiworld", "-w", "coords.txt", ">", "output.txt");
    //execl("../asciiworld", "-w", "coords.txt");
    //ifstream t("output.txt");
    //string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
    //return str;
    return output.str();
}
