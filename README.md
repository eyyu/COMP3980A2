# DCGPS - COMP3980 GPS Console Program
**Version:** 2.0
**Designers:** Eva Yu / John Agapeyev   
**Programmers:** John Agapeyev / Eva Yu   

- You can this read doc using any Markdown editor or text editor.

## Summary   
A simple location tracking program with map plotting

## Software Requirements: 
- Linux O/S 
- gpsd 
- shapelib c library
- gd c library
- [asciiworld installation](https://github.com/vain/asciiworld)
- ERSI Shapefile ( Map )
- gps dongle

## Disclosures
   
- This program is is suitable for gpsd version 3.11 ( ran on Raspberry Pi 1 )
- This program will not be suitable for gpsd version 3.16 ( current version )
   
## Commands

* *-h* or *-help* will show you this  

## Project layout

    makefile      		  # The make utility tool file.
    src/
    	/headers  
    		const.h 		# The constants used in the program
    		dcgps.h 		# The main function declaration
    		gps-utils.h 	# The utility function declarations
    		gpsprint.h		# The printing function declarations
            map.h           # map get function
		dcgps.cpp 		  # Holds the main function definition	       
		gps-utils.cpp	  # Holds the read function definition		
		gpsprint.c     	  # Holds the console print function definitions
        map.cpp           # uses an asciiworld.exe to draw and mark an ascii map

    bin/ 
    	a2		  		  # the executable of the program. click to run or run "$ a2" in command line
	designs/		
		A3_V1_Design.docx # The FSM and pseudo code of the project

_**Last update:** October 19th, 2016_
