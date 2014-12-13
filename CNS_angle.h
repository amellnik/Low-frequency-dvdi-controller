//==============================================================================
//
// Title:       CNS_angle.h
// Purpose:     A short description of the interface.
//
// Created on:  5/20/2013 at 11:39:03 AM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef __CNS_angle_H__
#define __CNS_angle_H__

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
		
#define CNS_ADDR 1				   //GPIB adress

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

void CNS_initialize(void);  
void CNS_set_angle(void); 


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __CNS_angle_H__ */
