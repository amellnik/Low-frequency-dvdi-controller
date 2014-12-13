//==============================================================================
//
// Title:       SHE_Globals.h
// Purpose:     A short description of the interface.
//
// Created on:  6/26/2012 at 3:51:10 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

#ifndef __SHE_Globals_H__
#define __SHE_Globals_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include <userint.h>

//==============================================================================
// Constants
#define NUM_POINTS 				100000	
#define MAX_MAG_STEP 			0.0002

//Sweep step delays are set on the front panel, this is only for ramping
#define MAG_DELAY				0.001 
#define SCAN_DELAY				300

//==============================================================================
// Types

//==============================================================================
// External variables
		
struct {
	double 		volts;
	double 		tesla;
	double 		set_volts;
	double 		set;
	double		now;
	double 		start;
	double 		end;
	double 		delta;
	double 		delay;
	int 		system;
} mag;

struct {
	double 		freq_delta;
	double 		freq_start;
	double 		freq_end;
	double 		power_delta;
	double 		power_start;
	double 		power_end;
	double 		freq;
	double 		power;
	int 		handle;
} rf;

struct {
	double	    *volts;   
	double 		*tesla;
	double 		*vref;
	double 		*dvdi;
	double 		*angle;
	double 		*bias;
	int			collected;
	char 		filename[MAX_PATHNAME_LEN];
	char		prefix[MAX_PATHNAME_LEN];
}	data;



struct {
	int plotwhat;
}	graph;

struct {
	double 		set;
	double 		start;
	double 		end;
	double 		delta;
	//double 		now;
	int 		handle;
	double 		delay;
	int 		use_2k;
} bias;

struct {
	double 		set;
	double 		start;
	double 		end;
	double 		delta;
	double 		delay;
	int 		handle;
} angle;

struct {
	int 		interrupt;
	int 		num_samps;
	double		device_r;	
	double		reference_r;
	//int			use_ref;
	int			use_angle;
	int 		sweep_pause;
} experiment;



 int mainH; 

//==============================================================================
// Global functions

extern void Debug(void);
extern void SetMag(void);
extern void SetUp(void);
extern void AllocateMemForData(void);
extern void Sweep(void);
extern void TakeSingle(void);
extern void UpdateGraph(void);
extern void ClearData(void);
extern void SaveData(void);

extern void BiasSweep(void);
extern void MakeAutoFilename(void);
extern void RunScanFile(void);
extern void AngleSweep(void);
extern void RotateAngleSweep(void);
extern void BiasScan(void);
extern double sign(double val);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __SHE_Globals_H__ */
