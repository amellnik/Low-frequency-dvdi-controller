/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2014. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MAIN                             1       /* callback function: panelCB */
#define  MAIN_DEBUG                       2       /* control type: command, callback function: DEBUG_CB */
#define  MAIN_DOUBLED                     3       /* control type: numeric, callback function: (none) */
#define  MAIN_MAG_SET                     4       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_RAMP                    5       /* control type: command, callback function: MAG_RAMP_CB */
#define  MAIN_MAG_DELTA                   6       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_START                   7       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_END                     8       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_DELAY                   9       /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_MAG_SWEEP                   10      /* control type: command, callback function: MAG_SWEEP_CB */
#define  MAIN_NUM_SAMPS                   11      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_INTERRUPT                   12      /* control type: textButton, callback function: INTERRUPT_CB */
#define  MAIN_GRAPH                       13      /* control type: graph, callback function: (none) */
#define  MAIN_CLEAR_DATA                  14      /* control type: command, callback function: CLEAR_DATA_CB */
#define  MAIN_SAVE                        15      /* control type: command, callback function: SAVE_CB */
#define  MAIN_FILE_PREFIX                 16      /* control type: string, callback function: CONFIG_CB */
#define  MAIN_CURRENT                     17      /* control type: numeric, callback function: CURRENT_CB */
#define  MAIN_CURRENT_START               18      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_CURRENT_DELTA               19      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_CURRENT_END                 20      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_CURRENT_SWEEP               21      /* control type: command, callback function: CURRENT_SWEEP_CB */
#define  MAIN_AUTO_SAVE                   22      /* control type: command, callback function: AUTO_SAVE_CB */
#define  MAIN_MAG_SYSTEM                  23      /* control type: ring, callback function: CONFIG_CB */
#define  MAIN_REFERENCE_R                 24      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_SWEEP_PAUSE                 25      /* control type: radioButton, callback function: CONFIG_CB */
#define  MAIN_MANUAL_VOLT                 26      /* control type: numeric, callback function: MANUAL_VOLT_CB */
#define  MAIN_ANGLE_SET                   27      /* control type: numeric, callback function: ANGLE_SET_CB */
#define  MAIN_ANGLE_DELTA                 28      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_ANGLE_START                 29      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_ANGLE_END                   30      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_USE_ANGLE                   31      /* control type: radioButton, callback function: USE_ANGLE_CB */
#define  MAIN_ANGLE_SWEEP                 32      /* control type: command, callback function: ANGLE_SWEEP_CB */
#define  MAIN_PLOT_WHAT                   33      /* control type: ring, callback function: CONFIG_CB */
#define  MAIN_DECORATION                  34      /* control type: deco, callback function: (none) */
#define  MAIN_ROTATE_SWEEP                35      /* control type: command, callback function: ROTATE_SWEEP_CB */
#define  MAIN_DECORATION_3                36      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_4                37      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_2                38      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_5                39      /* control type: deco, callback function: (none) */
#define  MAIN_TEXTMSG                     40      /* control type: textMsg, callback function: (none) */
#define  MAIN_ANGLE_DELAY                 41      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_BIAS_SWEEP                  42      /* control type: command, callback function: BIAS_SWEEP_CB */
#define  MAIN_BIAS_DELAY                  43      /* control type: numeric, callback function: CONFIG_CB */
#define  MAIN_BIAS_USE_2K                 44      /* control type: radioButton, callback function: BIAS_USE_2K_CB */
#define  MAIN_DECORATION_6                45      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ANGLE_SET_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ANGLE_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AUTO_SAVE_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BIAS_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BIAS_USE_2K_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CLEAR_DATA_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CONFIG_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CURRENT_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CURRENT_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DEBUG_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK INTERRUPT_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAG_RAMP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAG_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MANUAL_VOLT_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ROTATE_SWEEP_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SAVE_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK USE_ANGLE_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
