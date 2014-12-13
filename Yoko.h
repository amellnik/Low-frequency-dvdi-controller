//==============================================================================
//
// Title:       Yoko.h
// Purpose:     A short description of the interface.
//
// Created on:  6/28/2012 at 10:16:15 AM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef __Yoko_H__
#define __Yoko_H__

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

#define YOKO_SET			"S"
#define YOKO_OUTPUT			"O"
#define YOKO_TRIGGER		"E"
#define YOKO_ADDR 24				   //GPIB adress		
		
//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

void YOKO_initialize(void);
void YOKO_mA(void);   // Set to the 1mA current sourcing mode  
void YOKO_set(double val);
void YOKO_10V(void);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Yoko_H__ */
