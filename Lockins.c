//==============================================================================
//
// Title:       Lockins.c
// Purpose:     A short description of the implementation.
//
// Created on:  6/26/2012 at 4:20:52 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "Lockins.h"
#include <gpib.h>
#include <ansi_c.h>
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


void lockin_init(int n) {
	int addy;
	switch (n) {
		case 0:
			addy = LOCKIN0_ADDRESS;
			break;
		case 1:
			addy = LOCKIN1_ADDRESS;
			break;
		case 2:
			addy = LOCKIN2_ADDRESS;
			break;
	}
	lockins[n].handle = ibdev (0, addy, NO_SAD, T10s, 1, 0); 
	
	//char buf[30];
	//ibwrt (mag_2400.handle, "*RST", strlen("*RST"));

}

double lockin_xvolts(int n) {
	char buff[100];
	char *trash;
	ibwrt (lockins[n].handle, "X.", strlen("X."));
	ibrd (lockins[n].handle, &buff, 100);
	return strtod(buff, &trash);
}

double lockin_xvolts_n(int n, int samps) {
	double sum;
	int i;
	sum = 0.0;
	for (i=0;i<samps;i++) {
	sum += lockin_xvolts(n);	
	}
	return sum/samps;
}
	

	
