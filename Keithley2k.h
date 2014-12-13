//==============================================================================
//
// Title:       Keithley2k.h
// Purpose:     A short description of the interface.
//
// Created on:  9/23/2013 at 1:52:41 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef __Keithley2k_H__
#define __Keithley2k_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
		
#define KEITHLEY2K_ADDRESS 19		
		
struct {
	int handle;
	
} keithley2k;

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

double keithley2k_read(void);
void keithley2k_init(void);




#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Keithley2k_H__ */
