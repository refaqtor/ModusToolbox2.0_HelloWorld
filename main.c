/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the Empty PSoC6 Application
*              for ModusToolbox.
*
* Related Document: See Readme.md
*
*
*******************************************************************************
* (c) 2019, Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* ("Software"), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries ("Cypress") and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software ("EULA").
*
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress's integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Cypress against all liability.
*******************************************************************************/

/* ==========================================================
 *    ___             _   _     _
 *   / _ \ _ __   ___| |_| |__ (_)_ __ __  __
 *  | | | | '_ \ / _ \ __| '_ \| | '_ \\ \/ /
 *  | |_| | | | |  __/ |_| | | | | | | |>  <
 *   \___/|_| |_|\___|\__|_| |_|_|_| |_/_/\_\
 *
 * Copyright Onethinx, 2018
 * All Rights Reserved
 *
 * UNPUBLISHED, LICENSED SOFTWARE.
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Onethinx BV
 *
 * ==========================================================
*/
#include "OnethinxCore01.h"
#include "DemoKit01.h"
#include "LoRaWAN_keys.h"
#include "cycfg.h"
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

/* Go to ../OnethinxCore/LoRaWAN_keys.h and fill in the fields of the TTN_OTAAkeys structure */

coreConfiguration_t	coreConfig = {
	.Join.KeysPtr = 		&TTN_OTAAkeys,
	.Join.DataRate =		DR_AUTO,
	.Join.Power =			PWR_MAX,
	.Join.MAXTries = 		100,
    .Join.SubBand_1st =     EU_SUB_BANDS_DEFAULT,
	.Join.SubBand_2nd =     EU_SUB_BANDS_DEFAULT,
	.TX.Confirmed = 		false,
	.TX.DataRate = 			DR_0,
	.TX.Power = 			PWR_MAX,
	.TX.FPort = 			1,
};

sleepConfig_t sleepConfig = {
	.sleepMode = modeDeepSleepDebugOn,
	.sleepCores = coresBoth,
	.wakeUpPin = wakeUpPinHigh(false),
	.wakeUpTime = wakeUpDelay(0, 0, 5, 0)
};

/*******************************************************************************
* Function Name: main()
********************************************************************************
* Summary:
*  Sends a "Hello World" message using LoRaWAN.
* Details:
*  Go to ../OnethinxCore/LoRaWAN_keys.h and fill in the fields of the TTN_OTAAkeys structure
*  Read the quickstart guide on how to create keys.
*******************************************************************************/

/* OnethinxCore uses the following structures and variables, which can be defined globally */
coreStatus_t 	coreStatus;
coreInfo_t 		coreInfo;

uint8_t RXbuffer[64];
uint8_t TXbuffer[64];

int main(void)
{
	cy_rslt_t result;
	result = cybsp_init() ;
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}

	uint8_t j=0;

	/* initialize hardware configuration */
	init_cycfg_all();

	/* enable global interrupts */
	__enable_irq();

	/* Blue LED ON */
	LED_B_SET(LED_ON);

	/* initialize radio with parameters in coreConfig */
	coreStatus = LoRaWAN_Init(&coreConfig);

	/* Check Onethinx Core info */
	LoRaWAN_GetInfo(&coreInfo);

	/* send join using parameters in coreConfig, blocks until either success or MAXtries */
	coreStatus = LoRaWAN_Join(true);

	/* check for successful join */
	if (!coreStatus.mac.isJoined){
		while(1) {
			LED_B_INV;
			CyDelay(100);
		}
	} else {
		LED_B_SET(LED_OFF);
		/*delay before first message will be sent */
		CyDelay(1000);
	}

	/* main loop */
	for(;;)
	{
		LED_B_SET(LED_ON);

		/* compose a message to send */
        j=0;
        TXbuffer[j++] = 0x48; /* H */
		TXbuffer[j++] = 0x45; /* E */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x4f; /* O */
		TXbuffer[j++] = 0x20; /*   */
		TXbuffer[j++] = 0x57; /* W */
		TXbuffer[j++] = 0x4f; /* O */
		TXbuffer[j++] = 0x52; /* R */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x44; /* D */
        coreStatus = LoRaWAN_Send((uint8_t *) TXbuffer, j, true);
		CyDelay(1000);
        if( coreStatus.system.errorStatus == system_BusyError ){
        	for(int i=0; i<10; i++){
				LED_B_INV;
				CyDelay(100);
        	}
        }
		LED_B_SET(LED_OFF);

		/* sleep before sending next message */
		LoRaWAN_Sleep(&sleepConfig);
	}
}
