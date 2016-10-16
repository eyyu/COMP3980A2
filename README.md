# DCGPS - COMP3980 GPS Console Program
**Designers:** Eva Yu / John Agapeyev   
**Programmers:** John Agapeyev / Eva Yu   

- You can this read doc using any Markdown editor or text editor.

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
		dcgps.cpp 		  # Holds the main function definition	       
		gps-utils.cpp	  # Holds the read function definition		
		gpsprint.c     	  # Holds the console print function definition 
    bin/ 
    	a2		  		  # the executable of the program. click to run or run "$ a2" in command line
	designs/		
		A3_V1_Design.docx # The FSM and pseudo code of the project

_**Last update:** October 16th, 2016_
