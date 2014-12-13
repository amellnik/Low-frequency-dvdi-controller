//==============================================================================
//
// Title:       2400_Mag_Control.h
// Purpose:     A short description of the interface.
//
// Created on:  6/26/2012 at 3:33:14 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef ___2400_Mag_Control_H__
#define ___2400_Mag_Control_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include <gpib.h>
#include <ansi_c.h>

//==============================================================================
// Constants
		
#define KEITHLEY_ADDRESS 29	  //GPIB address
//#define KEITHLEY_OUT			"CONF"

//==============================================================================
// Types

//==============================================================================
// External variables
		
struct {
	int handle;
	
} mag_2400;


//==============================================================================
// Global functions
void mag_2400_init(void); 
void mag_2400_setv(double volts);
void mag_2400_sett(double tesla);
double mag_tesla_to_volts(double tesla);
double mag_2400_read_volts(void);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef ___2400_Mag_Control_H__ */
