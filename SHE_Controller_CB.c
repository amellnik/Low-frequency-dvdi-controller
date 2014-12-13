#include <userint.h>
#include "SHE Controller.h"
#include "SHE_Controller_CB.h"
#include "SHE_Globals.h"
#include "AligentSweeper.h"
#include "Yoko.h"
#include "2400_Mag_Control.h"
#include "CNS_angle.h"
#include "Keithley2k.h"

int CVICALLBACK DEBUG_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			Debug();
			break;
	}
	return 0;
}

int CVICALLBACK CONFIG_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(mainH, MAIN_MAG_START, &mag.start);
			GetCtrlVal(mainH, MAIN_MAG_END, &mag.end); 
			GetCtrlVal(mainH, MAIN_MAG_DELAY, &mag.delay); 
			GetCtrlVal(mainH, MAIN_MAG_DELTA, &mag.delta); 
			GetCtrlVal(mainH, MAIN_MAG_SYSTEM, &mag.system);  
			GetCtrlVal(mainH, MAIN_NUM_SAMPS, &experiment.num_samps);
			GetCtrlVal(mainH, MAIN_MAG_SET, &mag.set);
			//GetCtrlVal(mainH, MAIN_RF_FREQ_DELTA, &rf.freq_delta);
			//GetCtrlVal(mainH, MAIN_RF_FREQ_START, &rf.freq_start);
			//GetCtrlVal(mainH, MAIN_RF_FREQ_END, &rf.freq_end);
			//GetCtrlVal(mainH, MAIN_RF_POWER_DELTA, &rf.power_delta);
			//GetCtrlVal(mainH, MAIN_RF_POWER_START, &rf.power_start);
			//GetCtrlVal(mainH, MAIN_RF_POWER_END, &rf.power_end);
			GetCtrlVal(mainH, MAIN_FILE_PREFIX, data.prefix);
			GetCtrlVal(mainH, MAIN_CURRENT_DELTA, &bias.delta);
			GetCtrlVal(mainH, MAIN_CURRENT_START, &bias.start);
			GetCtrlVal(mainH, MAIN_CURRENT_END, &bias.end);
			GetCtrlVal(mainH, MAIN_BIAS_DELAY, &bias.delay);
			//GetCtrlVal(mainH, MAIN_DEVICE_R, &experiment.device_r);
			GetCtrlVal(mainH, MAIN_REFERENCE_R, &experiment.reference_r);
			//GetCtrlVal(mainH, MAIN_USE_REF, &experiment.use_ref);
			GetCtrlVal(mainH, MAIN_SWEEP_PAUSE, &experiment.sweep_pause); 
			GetCtrlVal(mainH, MAIN_ANGLE_START, &angle.start);
			GetCtrlVal(mainH, MAIN_ANGLE_END, &angle.end); 
			GetCtrlVal(mainH, MAIN_ANGLE_DELTA, &angle.delta); 
			GetCtrlVal(mainH, MAIN_PLOT_WHAT, &graph.plotwhat);
			GetCtrlVal(mainH, MAIN_ANGLE_DELAY, &angle.delay);
			//Dim or undim things if needed
			

			break;
	}
	return 0;
}


int CVICALLBACK MAG_RAMP_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//RampVolts();
			SetMag();
			break;
	}
	return 0;
}

int CVICALLBACK MAG_SWEEP_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			Sweep();
			break;
	}
	return 0;
}

int CVICALLBACK INTERRUPT_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainH, MAIN_INTERRUPT, &experiment.interrupt);
			
			break;
	}
	return 0;
}

int CVICALLBACK CLEAR_DATA_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ClearData();
			break;
	}
	return 0;
}

int CVICALLBACK SAVE_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SaveData();
			break;
	}
	return 0;
}

int CVICALLBACK RF_FREQ_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			break;
	}
	return 0;
}

int CVICALLBACK RF_POWER_SWEEP_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			break;
	}
	return 0;
}

int CVICALLBACK RF_SWEEP_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			break;
	}
	return 0;
}

int CVICALLBACK RF_POWER_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			break;
	}
	return 0;
}

int CVICALLBACK CURRENT_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainH, MAIN_CURRENT, &bias.set);
			YOKO_set(bias.set);
			break;
	}
	return 0;
}

int CVICALLBACK CURRENT_SWEEP_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			BiasSweep();
			break;
	}
	return 0;
}

int CVICALLBACK AUTO_SAVE_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			MakeAutoFilename();
			SaveData();
			break;
	}
	return 0;
}

int CVICALLBACK LOOP_FROM_FILE_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			RunScanFile();
			break;
	}
	return 0;
}

int CVICALLBACK MANUAL_VOLT_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double thisvolts;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainH, MAIN_MANUAL_VOLT, &thisvolts);
			mag_2400_setv(thisvolts);
			break;
	}
	return 0;
}

int CVICALLBACK USE_ANGLE_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainH, MAIN_USE_ANGLE, &experiment.use_angle); 
			SetCtrlAttribute(mainH, MAIN_ANGLE_SET, ATTR_DIMMED, experiment.use_angle==0);
			SetCtrlAttribute(mainH, MAIN_ANGLE_DELTA, ATTR_DIMMED, experiment.use_angle==0);
			SetCtrlAttribute(mainH, MAIN_ANGLE_START, ATTR_DIMMED, experiment.use_angle==0);
			SetCtrlAttribute(mainH, MAIN_ANGLE_END, ATTR_DIMMED, experiment.use_angle==0);
			SetCtrlAttribute(mainH, MAIN_ANGLE_DELAY, ATTR_DIMMED, experiment.use_angle==0);
			GetCtrlVal(mainH, MAIN_ANGLE_SET, &angle.set);
			if (experiment.use_angle==1){
				CNS_initialize();
			}
			break;
	}
	return 0;
}

int CVICALLBACK ANGLE_SWEEP_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			AngleSweep();
			break;
	}
	return 0;
}

int CVICALLBACK ANGLE_SET_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainH, MAIN_ANGLE_SET, &angle.set);
			CNS_set_angle();
			break;
	}
	return 0;
}

int CVICALLBACK ROTATE_SWEEP_CB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			RotateAngleSweep();
			break;
	}
	return 0;
}

int CVICALLBACK PLOT_WHAT_CB (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK BIAS_SWEEP_CB (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			BiasScan();
			break;
	}
	return 0;
}

int CVICALLBACK BIAS_USE_2K_CB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainH, MAIN_BIAS_USE_2K, &bias.use_2k); 
			if (bias.use_2k==1) {
				keithley2k_init();	
			}
			break;
	}
	return 0;
}
