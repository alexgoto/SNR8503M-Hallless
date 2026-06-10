/*******************************************************************************
 * copy right (C)2019, SNANER SEMICONDUCTOR Co.ltd
 *
 * file name： parameter.h
 * file identification：
 * summary： parameter config
 * other： 无
 * current version： V1.0
 * Author： Li
 * completion date： 2020年8月18日
 *
 *******************************************************************************/
 
/*------------------------------prevent recursive inclusion -------------------*/ 
#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "basic.h"
#include "hardware_config.h"

/* -------------------------------Storage address related definitions---------------------------- */ 
#define MEMORY_DATA_ADDR               0x7800

/* ---------------------------------Function related definitions------------------------------ */
#define ENABLE_FUNCTION                1
#define DISABLE_FUNCTION               0

/* --------------------------------- Hardware testing PWM output function ------------------------------ */
#define DEBUG_PWM_OUTPUT               DISABLE_FUNCTION   //ENABLE_FUNCTION       /* PWM outputs a certain duty cycle during debugging */

/* ----------------------PWM frequency and dead zone definition----------------------------------- */
#define MCU_MCLK                       (48000000LL)       /* PWM module operating frequency */ 
#define PWM_MCLK                       ((u32)MCU_MCLK)    /* PWM module operating frequency */
#define PWM_PRSC                       ((u8)0)            /* PWM module operation prescaler */
#define PWM_FREQ                       ((u16)16000)       /* PWM chopping frequency */

/* Motor control PWM cycle counter value */
#define PWM_PERIOD                     ((u16)(PWM_MCLK/(u32)(2*PWM_FREQ*(PWM_PRSC+1))))
#define MAX_PWM_DUTY                   PWM_PERIOD							  /* When the PWM chopping frequency is 16K, 1500 is the maximum duty cycle (fully open) */
#define MIN_PWM_DUTY                   ((u16)(0.1*PWM_PERIOD)) 	/* When the PWM chopping frequency is 16K, 150 is the minimum duty cycle */
#define LIMT_PWM_DUTY                  ((u16)(PWM_PERIOD - MIN_PWM_DUTY))

/* -----------------------------Hardware Parameter---------------------------- */
#define ADC_SUPPLY_VOLTAGE             (3.6)              //Unit: V ADC reference voltage, 3.6 or 2.4, most applications choose 3.6
/*OPA sampling matching resistor 1K ohms, 200:10=(200/(10.0+1.0)=18.18倍 */
/*The maximum sampling current value of the phase line is   3.6/0.004/(200/(10.0+1.0)) = 44.5A*/
/*In practical projects, it is important to pay attention to setting the maximum sampling current value reasonably, usually designed according to 3 times the overload*/
#define AMPLIFICATION_GAIN             (18.18)          	//Operational amplifier amplification factor
#define RSHUNT                         (0.004)            //Unit: Ω Sampling resistance value
#define VOLTAGE_SHUNT_RATIO            (1.0/(33.0+1.0)) 	//Bus voltage divider ratio (pull-down resistance/(pull-up resistance+pull-down resistance))

/* ------------------------------ADC calibration related parameter settings---------------------------- */
#define CALIB_SAMPLES                  (512)    //ADC bias calibration times, cannot be modified
#define OFFSET_THD                     (3500)   //ADC bias error threshold, no need to modify
#define PHASE_OFFSET_MAX               (250)			
#define PHASE_OFFSET_MIN               (0)			

/* ----------------------------Current Lim SHORT-------------------------- */
#define SHORT_BUS_CURRENT              (u16)50 										  /* Short circuit current unit: A*/
#define SHORT_CURRENT_VOL              (SHORT_BUS_CURRENT * RSHUNT) /* Bus current sampling voltage result (preferably within 1.6V)*/
#define SHORT_CURRENT_DAC              (u16)((SHORT_BUS_CURRENT * RSHUNT * 256)/3)     /* The short-circuit voltage corresponds to the DAC value, and the maximum range of the DAC is 3V */

/* ----------------------------Current Lim Parameter-------------------------- */
#define CURLIM_FUNCTION                0
#define POWLIM_FUNCTION                1
#define CUR_POW_SEL        						 CURLIM_FUNCTION                           /*Current limiting or power limiting switching 0 Current limiting 1 Power limiting */
#define MAX_BUS_CURRENT_SETTINT        (u16)18                                   /* Current limiting unit: A*/
#define CURRENT_ADC_PER_A              (RSHUNT * AMPLIFICATION_GAIN * 32752/3.6)  /* ADC value per ampere current */ 
#define CURRENT_LIM_VALUE              (u16)(MAX_BUS_CURRENT_SETTINT * CURRENT_ADC_PER_A) /* Current ADC value */
#define IevgSum_Kp  Q15(0.05)
#define IevgSum_Ki  Q15(0.02)
#define IevgSum_Kc  Q15(0.5)
#define POW_LIM_VALUE              		 (u32)(24*CURRENT_LIM_VALUE>>7) /* Power ADC value voltage V * current */

#define BUS_CURRENT_FIRST              (u16)20 /* First level current limiting protection unit: A*/
#define BUS_CURRENT_SECOND             (u16)22 /* Secondary current limiting protection unit: A*/
#define CURRENT_ADC_PER_A              (RSHUNT * AMPLIFICATION_GAIN * 32752/3.6) /* ADC value per ampere current */ 
#define OVER_CURRENT_FIRST_THD         (u16)(BUS_CURRENT_FIRST * CURRENT_ADC_PER_A)  /* First level current limiting protection ADC value */
#define OVER_CURRENT_SECOND_THD        (u16)(BUS_CURRENT_SECOND * CURRENT_ADC_PER_A) /* Second level current limiting protection ADC value */
#define TIME_LIMIT_FIRST               1000  /* First level current limiting protection time */
#define TIME_LIMIT_SECOND              200   /* Secondary current limiting protection time */

/****************************MOS temperature protection*************************************/
#define EN_MOS_TEMP_DETECT       		(1)     /* MOS temperature protection detection enable */ 
#define MOS_TEMP_UP_VOL              5     	/* MOS temperature detection pull-up voltage, unit: V */   
#define MOS_TEMP_UP_RES              10    	/* MOS temperature detection pull-up resistance, unit: K Ω */  
#define MOS_TEMP_OVER_RES            1.0  	/* NTC resistance value during MOS over temperature, corresponding to 1.0 at 95 ℃, voltage 0.45V */ 
#define RSM_MOS_TEMP_OVER_RES        3.0  	/* MOS over temperature recovery NTC resistance value, 60 ℃ corresponds to 3.0K, voltage 1.15V */ 
#define MOS_TEMP_OVER_THD            (u32)((MOS_TEMP_OVER_RES * MOS_TEMP_UP_VOL * 32752)/((MOS_TEMP_OVER_RES + MOS_TEMP_UP_RES) * 3.6))
#define RSM_MOS_TEMP_OVER_THD        (u32)((RSM_MOS_TEMP_OVER_RES * MOS_TEMP_UP_VOL * 32752)/((RSM_MOS_TEMP_OVER_RES + MOS_TEMP_UP_RES) * 3.6))
#define MOS_TEMP_OVER_TIME           500  	/* Unit：ms */  
#define RSM_MOS_TEMP_OVER_TIME       500  	/* Unit：ms */  

/* ---------------------------- Voltage Protect Parameter -------------------------- */
#define LOW_VOLATAGE_THD_1                5.5     	/* The first section is under voltage, and under voltage protection occurs during motor operation. Unit: V*/
#define LOW_VOLATAGE_THD_2                6.0   	  /* The second stage is under voltage, and under voltage protection occurs in the standby state of the motor. Unit: V*/
#define RSM_LO_VOLATAGE_THD               10.0 		  /* Undervoltage recovery voltage unit: V*/
#define LOW_VOLATAGE_FIRST                (u16)(LOW_VOLATAGE_THD_1 * VOLTAGE_SHUNT_RATIO/3.6*32752)  
#define LOW_VOLATAGE_SECOND               (u16)(LOW_VOLATAGE_THD_2 * VOLTAGE_SHUNT_RATIO/3.6*32752)  
#define RSM_LO_VOLATAGE_ADC               (u16)(RSM_LO_VOLATAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32752)   
#define LV_PROTECT_TIME_SLOW              500    		/* First undervoltage time unit: ms*/
#define LV_PROTECT_TIME_FAST              50	    	/* Second undervoltage time unit: ms*/
#define DIS_UV_PROTECT_TIME              	500    		/* Undervoltage recovery time delay unit: ms*/

#define OV_VOLTAGE_THD                    78   			/* Overvoltage threshold unit: V*/
#define RSM_OV_VOLTAGE_THD                70   			/* Overvoltage recovery threshold unit: V*/
#define OV_VOLTAGE_ADC                    (u16)(OV_VOLTAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32752)   
#define RSM_OV_VOLTAGE_ADC                (u16)(RSM_OV_VOLTAGE_THD * VOLTAGE_SHUNT_RATIO/3.6*32752) 
#define OV_PROTECT_TIME_FAST              10	    	/* Overvoltage time unit: ms*/
#define DIS_OV_PROTECT_TIME_SLOW        	500    		/* Overvoltage recovery time delay unit: ms*/

/* ---------------------------- Locked rotor protection -------------------------- */
#define EN_MOTOR_BLOCK_DETECT        		(1)       	/* Locked rotor protection detection enable */ 
#define MOTOR_BLOCK_DETECT_CNT     			(50)       	/* Locked rotor detection frequency */ 

/* ---------------------------- VSP Speed command Parameter 0~5V Corresponding AD value 0~1800 -------------------------- */
#define VSP_OFF_VALUE                		(200)       /* VSP closing threshold (0.3V) Unit: AD value*/        
#define VSP_START_VALUE                	(300)       /* VSP startup threshold (0.5V) Unit: AD value*/          
#define VSP_MAX_VALUE                		(1800)      /* VSP maximum value (3.2V) Unit: AD value*/      
#define VSP_DUTY_ACC_LOAD       				(1)         /* PWM DUTY increases every 1ms, with faster acceleration as it increases*/ 
#define VSP_DUTY_DEC_LOAD        				(1)         /* The PWM DUTY decreases every 1ms, and the greater the value, the faster the deceleration*/ 

/* ----------------------------direction check Parameter----------------------- */
#define EN_IOSET_CWCCW        	 			 (1)       	/* Read the CW-CCW IO setting and enable CWCCW. The following configuration will be invalid */ 
#define CW                             (1)      	/* Motor rotation: clockwise */ 
#define CCW                            (0)      	/* Motor rotation: counterclockwise*/	
#define CW_CCW                         CW      	  /* Motor steering setting，effected when EN_IOSET_CWCCW=0*/	

/* ----------------------------Parking brake function----------------------- */
#define EN_BRAKE                  			0       	/* Motor shutdown brake function */

/* ----------------------------Downwind detection function----------------------- */
#define EN_MOTOR_FREERUN_DETECT   			1       	/* Downwind detection function switch */
#define MOTOR_FREERUN_DETECT_CNT				4000			/* Maximum detection time unit：TIMER1_TIMEBASE */

/* ----------------------------Pre drive bootstrap capacitor pre charging parameters--------------------------- */
#define EN_PRE_CHARGE										1					/* Bootstrap capacitor pre charging function */
#define CHARGE_TIMECNT									16666			/* A total of 100ms of pre charging time per phase, modified according to actual hardware parameters. Unit:TIMER1_TIMEBASE */

/* ---------------------------- Motor startup PWM DUTY -------------------------- */
#define MOTOR_STARTUP_PWMDUTY           ((u16)(0.2*PWM_PERIOD)) /* When the PWM chopping frequency is 16K, 150 is the starting duty cycle */
#define STARTUP_DRAG_TIME         			100            			/* When starting, the duration of the strong drag on duty is measured in 1ms */

/* ---------------------------- Motor startup parameter -------------------------- */
#define TIMER1_TIMEBASE									6										//Suggest no modification, unit: us
#define TIMER1_TH_VALUE									(TIMER1_TIMEBASE*MCU_MCLK/1000000)
#define MAX_SPEED_CNT               		1500 								//Motor Minimum speed  Unit： TIM1_TIMEBASE;  2500 
#define MIN_SPEED_CNT                		10									//Motor Maximum speed  Unit： TIM1_TIMEBASE; 

/* ---------------------------- phase compensation -------------------------- */
#define EN_PHASE_COMP   				0       							/* Phase compensation function switch */
#define PHASE_COMP_LEAD_ANGLE   0.0										// Leading phase range: 0-2.5

/* ---------------------------- Motor Speed Close-loop--------------------------- */
#define EN_MOTOR_SPEED_CLOSELOOP				(0)											/* Speed closed-loop function */
#define MOTOR_POLES											2											  /* Number of motor poles 10 */
#define MOTOR_SPEED_X										((60*1000000/MOTOR_POLES)/TIMER1_TIMEBASE)	/* Speed calculation coefficient */ 	// RPM = MOTOR_SPEED_X/T 
#define MOTOR_SPEED_MAX_RPM							50000										/* unit: RPM, Closed loop maximum target speed */
#define MOTOR_SPEED_MIN_RPM							200						   				/* unit: RPM, Closed loop minimum target speed */
#define SPEED_ACC_MS                   (float)(5.0)             //Speed loop ramp acceleration RPM/MS
#define SPEED_DEC_MS                   (float)(5.0)             //Speed loop climbing deceleration RPM/MS	
#define SPEED_PI_PRC                   (2)                 			//Speed loop pre division, this macro needs to be manually adjusted when changing the time base
#define SSum_Kp  											  Q15(0.05)
#define SSum_Ki  												Q15(0.01)
#define SSum_Kc  												Q15(0.5)

/* ---------------------------- Motor IPD--------------------------- */
#define EN_MOTOR_ROTOR_DETECT						0
#define UART0_FUNCTION               	 DISABLE_FUNCTION         /* Motor Control UART0 Serial Port Control Communication Protocol */
#define UART0_BaudRate              	 9600     			 		      /* Motor control UART0 baud rate */


#endif  /* __PARAMETER_H */

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR **********************/
/* -----------------------------------END OF FILE------------------------------- */

