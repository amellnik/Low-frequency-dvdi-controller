//==============================================================================
//
// Title:       AligentSweeper.h
// Purpose:     A short description of the interface.
//
// Created on:  6/27/2012 at 4:46:11 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef __AligentSweeper_H__
#define __AligentSweeper_H__

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
#define SWEEPER_ADDRESS 25	
//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

void rf_init(void);
void rf_set_freq(double freq) ;
void rf_set_power(double power);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __AligentSweeper_H__ */
