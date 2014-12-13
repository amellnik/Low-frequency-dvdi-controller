//==============================================================================
//
// Title:       CNS_angle.c
// Purpose:     A short description of the implementation.
//
// Created on:  5/20/2013 at 11:39:03 AM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <utility.h>
#include "CNS_angle.h"
#include <gpib.h>
#include <ansi_c.h>
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

 void CNS_initialize(void)       
{
	char buf[100];
	angle.handle= ibdev (0, CNS_ADDR, NO_SAD, T1s, 1, 0);  //initialize
	ibwrt (angle.handle, "3VA2.5", strlen("3VA2.5"));	  // Set velocity to 2.5 deg/s
	Delay(angle.delay);
	sprintf(buf,"%s%+3.2f%s","3PA",angle.set,"\r\n");
	ibwrt (angle.handle, buf, strlen(buf));
	//Figure out what the max speed is for the angle and set it with VU

}
 
void CNS_set_angle(void) {
	char buf[100];
	char *trash;
	//sprintf(buf,"%s%+3.2f%s","3PA",angle.set,";3WS\r\n"); /* set angle  */		//
	sprintf(buf,"%s%+3.2f%s","3PA",angle.set,"\r\n");
	ibwrt (angle.handle, buf, strlen(buf));	
	int moving=1;
	double velocity;
	Delay(angle.delay);
	ProcessSystemEvents();
	while (moving==1) {
		sprintf(buf,"%s%s","3TV","\r\n"); /* query angle  */		//
		ibwrt (angle.handle, buf, strlen(buf));	
		Delay(angle.delay);
		ibrd (angle.handle, &buf, 100);
		Delay(angle.delay); 
		moving = (0.0!=strtod(buf, &trash)); 
		
	}
}
 
