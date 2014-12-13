//==============================================================================
//
// Title:       Keithley2k.c
// Purpose:     A short description of the implementation.
//
// Created on:  9/23/2013 at 1:52:41 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <gpib.h>
#include <ansi_c.h>
#include "Keithley2k.h"
#include "SHE_Globals.h"

//==============================================================================
// Constants



//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

void keithley2k_init() 
{
	char buff[255];
	keithley2k.handle = ibdev (0, KEITHLEY2K_ADDRESS, NO_SAD, T10s, 1, 0); 
	ibwrt (keithley2k.handle, "*RST", strlen("*RST"));
	ibwrt (keithley2k.handle, ":CONFigure:VOLTage:DC", strlen(":CONFigure:VOLTage:DC")); // Set to read DC voltage 
	ibwrt (keithley2k.handle, ":SENSe:VOLTage:DC:AVERage:TCONtrol REPeat", strlen(":SENSe:VOLTage:DC:AVERage:TCONtrol REPeat"));
	sprintf(buff, ":SENSe:VOLTage:DC:AVERage:COUNT %u", experiment.num_samps);
	ibwrt (keithley2k.handle, buff, strlen(buff));
	ibwrt (keithley2k.handle, ":SENSe:VOLTage:DC:AVERage:STATe ON", strlen(":SENSe:VOLTage:DC:AVERage:STATe ON"));
}

double keithley2k_read()
{
	char buff[255];
	char *trash;
	ibwrt (keithley2k.handle, ":READ?", strlen(":READ?")); 
	ibrd (keithley2k.handle, &buff, 255);
	return strtod(buff, &trash); 
}
	
