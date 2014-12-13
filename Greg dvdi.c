//==============================================================================
//
// Title:       SHE Controller
// Purpose:     A short description of the application.
//
// Created on:  6/26/2012 at 3:08:59 PM by TopMob.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include <NIDAQmx.h>
#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
//#include "YOKO.h"
#include <utility.h> 
#include "Keithley2k.h"
#include <math.h>
#include <string.h>
#include "SHE Controller.h"
#include "toolbox.h"
#include "SHE_Globals.h"
#include "2400_Mag_Control.h"
#include "lockins.h"
//#include "AligentSweeper.h"
#include "Yoko.h"
#include "CNS_angle.h"

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

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
    
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (mainH = LoadPanel (0, "SHE Controller.uir", MAIN));
    
    /* display the panel and run the user interface */
    errChk (DisplayPanel (mainH));
	SetUp();
    errChk (RunUserInterface ());

Error:
    /* clean up */
    DiscardPanel (mainH);
    return 0;
}

void Debug(void)
{
	//mag_2400_init();
	//mag_2400_setv(3.14159); 
	//lockin_init(0);
	//SetCtrlVal(mainH, MAIN_DOUBLED, lockin_xvolts(0));
	
}

void SetUp(void) 
{
	CONFIG_CB (mainH, 0, EVENT_COMMIT,0, 0, 0); 
	angle.set=0;
	bias.set=0;
	mag_2400_init(); 
	//rf_init();
	//GetCtrlVal(mainH, MAIN_RF_POWER, &rf.power);
	//rf_set_power(rf.power);
	//GetCtrlVal(mainH, MAIN_RF_FREQ, &rf.freq);
	//rf_set_freq(rf.freq);
	lockin_init(0); 
	lockin_init(1);
	YOKO_initialize();
	//YOKO_mA();
	YOKO_10V();
	bias.use_2k=0;
	
	data.collected=0;
	AllocateMemForData();
	strcpy(data.filename, "");
}



void MakeAutoFilename(void)
{
	//Save space in the filename, use short versions of numbers if they are set to zero
	//May need to modify this by hand if doing dispersion scans with more than 0.1 GHz resolution

	sprintf(data.filename, "%s_%.2GOhm_%.3fV%.1f%s", data.prefix,experiment.reference_r, bias.set, angle.set, ".dat");	

}



void BiasSweep(void)
{
	ClearData();
	bias.set = bias.start;
	YOKO_set(bias.set);
	while (fabs(bias.set	-bias.end)>=bias.delta) {
		YOKO_set(bias.set); 
		Sweep();
		//sprintf(buff, ":SOURce:FREQuency:FIXed %fGHZ", freq);
		MakeAutoFilename();
		SaveData();
		bias.set+=bias.delta;
		
	}
	YOKO_set(bias.set); 
	Sweep();
	MakeAutoFilename();
	SaveData();
}
void AngleSweep(void)
{
	ClearData();	
//for(current.now = current.start; current.now<=current.end; current.now+=current.delta){
		//rf_set_power(rf.power);
	angle.set = angle.start;
	CNS_set_angle();
	while (fabs(angle.set-angle.end)>=angle.delta) {
		CNS_set_angle(); 
		Sweep();
		//sprintf(buff, ":SOURce:FREQuency:FIXed %fGHZ", freq);
		MakeAutoFilename();
		SaveData();
		angle.set+=angle.delta;
		//YOKO_set(current.now);	
	}
	//angle.set=angle.end;
	CNS_set_angle();
	Sweep();
	MakeAutoFilename();
	SaveData();
}
	
void RotateAngleSweep(void)
{   ClearData(); 
	//for(current.now = current.start; current.now<=current.end; current.now+=current.delta){
		//rf_set_power(rf.power);
	angle.set = angle.start;
	CNS_set_angle();
	while ((fabs(angle.set-angle.end)>=angle.delta)&&(experiment.interrupt==0)) {
		CNS_set_angle(); 
		TakeSingle();
		angle.set+=angle.delta;
		//YOKO_set(current.now);	
	}

	MakeAutoFilename();
	SaveData();
}

void BiasScan(void)
{
	ClearData();	
	bias.set = bias.start;
	YOKO_set(bias.set);
	while ((fabs(bias.set	-bias.end)>=bias.delta)&&(experiment.interrupt==0)) {
		
		ProcessSystemEvents();
		TakeSingle();
		YOKO_set(bias.set); 
		Delay(bias.delay); 
		bias.set+=bias.delta;
	}
	if (experiment.interrupt==0){
		TakeSingle();
		YOKO_set(bias.set); 
		TakeSingle();
		MakeAutoFilename();
		SaveData();
	}

}	


void AllocateMemForData(void)
{
	if( ((data.tesla=malloc((NUM_POINTS)*sizeof(double)))==NULL)		//allocate space for archive  
		||((data.volts=malloc((NUM_POINTS)*sizeof(double)))==NULL)
		||((data.vref=malloc((NUM_POINTS)*sizeof(double)))==NULL)
		||((data.dvdi=malloc((NUM_POINTS)*sizeof(double)))==NULL)
		||((data.angle=malloc((NUM_POINTS)*sizeof(double)))==NULL)
		||((data.bias=malloc((NUM_POINTS)*sizeof(double)))==NULL)
		/*||((data.current=malloc((NUM_POINTS)*sizeof(float64)))==NULL)
		||((data.frequency=malloc((NUM_POINTS)*sizeof(float64)))==NULL)*/) 
	MessagePopup("Error","Not enough memory for archive of all points");	
	
}

void TakeSingle(void) 
{ //Records what's going on and adds it to the data archive
	data.tesla[data.collected] = mag.now;  
	data.volts[data.collected] = lockin_xvolts_n(0, experiment.num_samps);
	data.vref[data.collected] = lockin_xvolts_n(1, experiment.num_samps);
	data.dvdi[data.collected] = data.volts[data.collected]/data.vref[data.collected]*experiment.reference_r;
	data.angle[data.collected] = angle.set;
	if (bias.use_2k==0) {
		data.bias[data.collected] = bias.set;
	} else {
		data.bias[data.collected] = keithley2k_read();	
	}
	//data.current[data.collected] = 0;  //Currently saved in headers only
	//data.frequency[data.collected] = 0;  //Currently recorded in headers only

	data.collected++;
	UpdateGraph();
}

void UpdateGraph(void) 
{
	if ((data.collected > 1)&&(graph.plotwhat==0)) {
	DeleteGraphPlot (mainH, MAIN_GRAPH, -1, VAL_IMMEDIATE_DRAW);
	PlotXY (mainH, MAIN_GRAPH, data.tesla, data.dvdi, data.collected, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_SIMPLE_DOT, VAL_SOLID, 1, VAL_BLACK);
	}
	if ((data.collected > 1)&&(graph.plotwhat==1)) {
	DeleteGraphPlot (mainH, MAIN_GRAPH, -1, VAL_IMMEDIATE_DRAW);
	PlotXY (mainH, MAIN_GRAPH, data.angle, data.dvdi, data.collected, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_SIMPLE_DOT, VAL_SOLID, 1, VAL_BLACK);
	}
	if ((data.collected > 1)&&(graph.plotwhat==2)) {
	DeleteGraphPlot (mainH, MAIN_GRAPH, -1, VAL_IMMEDIATE_DRAW);
	PlotXY (mainH, MAIN_GRAPH, data.bias, data.dvdi, data.collected, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_SIMPLE_DOT, VAL_SOLID, 1, VAL_BLACK);
	}
}

void ClearData(void)
{
	data.collected=0;
	DeleteGraphPlot (mainH, MAIN_GRAPH, -1, VAL_IMMEDIATE_DRAW);;
}

void Sweep(void) 	  //Now always measures while sweeping toward zero
{

	ClearData();
	mag.set=mag.start;
	SetMag();
	
	//for (mag.tesla=0.0; mag.tesla>=mag.start; mag.tesla-=0.0004) {
	//	ProcessSystemEvents();
	//	if (experiment.interrupt==1) {mag_2400_sett(0.0);  break;}
	//	mag_2400_sett(mag.tesla);
	//	Delay(0.03); //Safe maximum ramp speed is hard wired in here
	//}
	
/*	while ((fabs(mag.set)>mag.delta)&&(experiment.interrupt==0)) {
		Delay(mag.delay);
		TakeSingle();
		mag.set+=mag.delta;
		SetMag();
	}
	Delay(mag.delay);
	TakeSingle();
	
	mag.set = mag.end;
	SetMag();
	
	while ((fabs(mag.set)>mag.delta)&&(experiment.interrupt==0)) {
		Delay(mag.delay);
		TakeSingle();
		mag.set-=mag.delta;
		SetMag();
	}
	Delay(mag.delay);
	TakeSingle();
	
	mag.set = 0;
	SetMag(); */
	
///////////
	while (((mag.set)<mag.end)&&(experiment.interrupt==0)) {
		Delay(mag.delay);
		TakeSingle();
		mag.set+=mag.delta;
		SetMag();
	}
	Delay(mag.delay);
	TakeSingle();
	
	mag.set = mag.end;
	SetMag();
	
	while (((mag.set)>mag.start)&&(experiment.interrupt==0)) {
		Delay(mag.delay);
		TakeSingle();
		mag.set-=mag.delta;
		SetMag();
	}
	Delay(mag.delay);
	TakeSingle();
	
	mag.set = 0;
	SetMag();   ///////////////////
	
	if (experiment.sweep_pause==1) {
		Delay(SCAN_DELAY);
	}
	
}


void SetMag(void) 
{
	if (experiment.interrupt==1){
			mag.set=0;
		}
	while (fabs(mag.set-mag.now)>MAX_MAG_STEP) {
		mag.now += sign(mag.set-mag.now)*MAX_MAG_STEP;
		SetCtrlVal(mainH, MAIN_MAG_SET, mag.now);
		//YOKO_set(ProjTeslaToVolts(mag.now), mag.handle);
		mag_2400_sett(mag.now);
		
		Delay(MAG_DELAY);
		ProcessSystemEvents();
		if (experiment.interrupt==1){
			mag.set=0;
		}
	}
	ProcessSystemEvents();
	mag.now = mag.set;
	SetCtrlVal(mainH, MAIN_MAG_SET, mag.now);
	mag_2400_sett(mag.now);
}

double sign(double val) 
{
	if (val>0) {
		return 1;
	}
	if (val<0) {
		return -1;
	}
	return 0;
}

void SaveData(void) 
{		//Needs to be changed to voltage
	int i;
	FILE *out;
	int brag;
	brag = 1;
	if (strcmp(data.filename,"")==1) {
		brag = 0;
	} else {
		FileSelectPopup (data.filename,"*.dat", "*.dat","Save data", VAL_SAVE_BUTTON, 0, 0, 1, 1, data.filename);
	}
		
	
	//if ((strcmp(data.filename,""))||(FileSelectPopup (data.filename,"*.dat", "*.dat","Save data", VAL_SAVE_BUTTON, 0, 0, 1, 1, data.filename)))
	//{
		
		
		out= fopen(data.filename,"w");
		//Print a standardized header of info
		/*fprintf(out, "%s", "---Begin Header---");
		fprintf(out, "%s%f", "\nReference resistance (Ohm) :", experiment.ref_r);
		fprintf(out, "%s%E", "\nFull scale reference sensitivity (V) :", lockins.ref_sens);		
		fprintf(out, "%s%E", "\nFull scale Vxx sensitivity (V) :", lockins.vxx_sens);
		fprintf(out, "%s%E", "\nFull scale Vxy sensitivity (V) :", lockins.vxy_sens);
		fprintf(out, "%s%i", "\nSamples per point :", experiment.num_samps);
		fprintf(out, "%s%i", "\nSample frequency (Hz) :", experiment.freq_samps);
		fprintf(out, "%s", "\n---End Header---\n\n"); */
		
		fprintf( out , "%s", "dvdi\tField\tVx\tVref\tAngle\tBias\n");  // Units are volts, ohms, oersted, kelvin, amps
		for(i=1;i<data.collected;i++) 
		{
			fprintf( out , "%E%s%E%s%E%s%E%s%E%s%E%s", data.dvdi[i], "\t",data.tesla[i], "\t", data.volts[i], "\t", data.vref[i], "\t", data.angle[i], "\t", data.bias[i], "\n");				
		}
		fclose(out);
		if (brag==1){
		   MessagePopup ("Victory!", "Data has been saved");
		}
		strcpy(data.filename, "");
	//}
}

void RunScanFile(void)   // Reads power in DB, freq in GHz and current in mA
{

}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}
