
//==============================================================================
//
// Title:       Yoko.c
// Purpose:     A short description of the implementation.
//
// Created on:  6/28/2012 at 10:16:15 AM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "Yoko.h"
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

 void YOKO_initialize(void)       
{
	char buf[100];
	bias.handle= ibdev (0, YOKO_ADDR, NO_SAD, T100ms, 1, 0);   
	sprintf(buf,"%s%s%f%s",YOKO_SET," ",+0.0,"\n"); /* set to zero voltage */		 //S
	ibwrt (bias.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%i%s",YOKO_OUTPUT," ",1,"\n"); /* output on */						//O
	ibwrt (bias.handle, buf, strlen(buf));												//E
	sprintf(buf,"%s%s",YOKO_TRIGGER, "\n"); /* start */
	ibwrt (bias.handle, buf, strlen(buf));

}
 
void YOKO_mA(void)		  //Put yoko into mA sourcing mode
{
	char buf[100]; 
	sprintf(buf, "%s%s", "F5", "\n");
	ibwrt (bias.handle, buf, strlen(buf));
	sprintf(buf, "%s%s", "R4", "\n");
	ibwrt (bias.handle, buf, strlen(buf));
	sprintf(buf,"%s%s",YOKO_TRIGGER, "\n"); 
	ibwrt (bias.handle, buf, strlen(buf));
}

void YOKO_set(double val)  //Takes a current val and sets the voltage appropriately 
{
	SetCtrlVal(mainH, MAIN_CURRENT, val); 
	//val *= (experiment.reference_r + experiment.device_r);
	char buf[100];
	//SetCtrlVal(panelHandle, MAIN_YOKO_SET, val);
	//yoko.setpoint=val;
	//sprintf(buf,"%s%s%f%s",YOKO_SET," ",val,"\n"); // original doesn't seem to work for very small values
	sprintf(buf,"%s%s%E%s",YOKO_SET," ",val,"\n");
	ibwrt (bias.handle, buf, strlen(buf));
	sprintf(buf,"%s%s",YOKO_TRIGGER, "\n"); /* start */
	ibwrt (bias.handle, buf, strlen(buf));


}

void YOKO_10V(void)		  //Put yoko into V sourcing mode
{
	char buf[100]; 
	sprintf(buf, "%s%s", "F1", "\n");
	ibwrt (bias.handle, buf, strlen(buf));
	sprintf(buf, "%s%s", "R5", "\n");
	ibwrt (bias.handle, buf, strlen(buf));
	sprintf(buf,"%s%s",YOKO_TRIGGER, "\n"); 
	ibwrt (bias.handle, buf, strlen(buf));
}
