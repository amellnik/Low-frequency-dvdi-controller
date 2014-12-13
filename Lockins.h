//==============================================================================
//
// Title:       Lockins.h
// Purpose:     A short description of the interface.
//
// Created on:  6/26/2012 at 4:20:52 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef __Lockins_H__
#define __Lockins_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
#define LOCKIN0_ADDRESS 28
#define LOCKIN1_ADDRESS 27 
#define LOCKIN2_ADDRESS 26 

//==============================================================================
// Types
		
struct {
	int handle;
} lockins[3];


	

//==============================================================================
// External variables

//==============================================================================
// Global functions

void lockin_init(int lockin);
double lockin_xvolts(int n);
double lockin_xvolts_n(int n, int samps);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Lockins_H__ */
