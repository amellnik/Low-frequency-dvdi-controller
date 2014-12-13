//==============================================================================
//
// Title:       AligentSweeper.c
// Purpose:     A short description of the implementation.
//
// Created on:  6/27/2012 at 4:46:11 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "AligentSweeper.h"
#include <gpib.h>
#include <ansi_c.h>
//#include "2400_Mag_Control.h"
#include "SHE_Globals.h"
#include "SHE Controller.h"
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

void rf_init(void)	   //If magnet is energized when the program is turned on this ramps it down first.
{
	//double initial_volts;
	char buff[255];
	rf.handle = ibdev (0, SWEEPER_ADDRESS, NO_SAD, T10s, 1, 0);	
	
	
	//Set AM source
	sprintf(buff, ":AM1:SOURce INT1");
	ibwrt (rf.handle, buff, strlen(buff));	
	//Set AM frequency
	sprintf(buff, ":AM1:INTernal1:FREQuency +1.713E+003Hz");
	ibwrt (rf.handle, buff, strlen(buff));
	//Set AM modulation type
	sprintf(buff, ":AM1:TYPE LINear");
	ibwrt (rf.handle, buff, strlen(buff));
	//Set AM modulation depth
	sprintf(buff, ":AM1:DEPTh:LINear 100PCT");
	ibwrt (rf.handle, buff, strlen(buff));
	//Set AM modulation depth
	sprintf(buff, ":AM1:DEPTh:LINear 100PCT");
	ibwrt (rf.handle, buff, strlen(buff));
	//Turn AM on
	sprintf(buff, ":AM1:STATe ON");
	ibwrt (rf.handle, buff, strlen(buff));
	
	
	//Tie INT1 to the external LF output
	sprintf(buff, ":LFOutput:SOURce INT1");
	ibwrt (rf.handle, buff, strlen(buff));
	//Set amplitude of signal at LF output
	sprintf(buff, ":LFOutput:AMPLitude 3.0VP");
	ibwrt (rf.handle, buff, strlen(buff));
	//Turn LF output on
	sprintf(buff, ":LFOutput:STATe ON");
	ibwrt (rf.handle, buff, strlen(buff));
	
	//Turn on RF
	sprintf(buff, ":OUTput:STATe ON");
	ibwrt (rf.handle, buff, strlen(buff));
	//Turn on modulation	
	//sprintf(buff, ":OUTput:MODulation:STATe ON");
	//ibwrt (rf.handle, buff, strlen(buff));

}

void rf_set_freq(double freq) 
{
	freq=freq/pow(10,9);
	char buff[255];
	sprintf(buff, ":SOURce:FREQuency:FIXed %fGHZ", freq);
	ibwrt (rf.handle, buff, strlen(buff));
}

void rf_set_power(double power) 
{
	
	char buff[255];
	sprintf(buff, ":SOURce:POWer %fDBM", power);
	ibwrt (rf.handle, buff, strlen(buff));
}
