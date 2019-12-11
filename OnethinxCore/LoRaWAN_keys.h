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

#ifndef LORAWAN_KEYS_H
#define LORAWAN_KEYS_H

#include "OnethinxCore01.h"

LoRaWAN_keys_t TTN_OTAAkeys = {
	.KeyType 						= OTAA_10x_key,
	.PublicNetwork					= true,
	.OTAA_10x.DevEui				= {{ 0x00, 0x59, 0xC9, 0x68, 0x1F, 0x7C, 0x6D, 0x36 }},
	.OTAA_10x.AppEui				= {{ 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x01, 0x91, 0x38 }},
	.OTAA_10x.AppKey				= {{ 0x2A, 0x19, 0xA6, 0x5A, 0x69, 0x24, 0x84, 0x6E, 0xDC, 0x7B, 0x81, 0xA0, 0xF5, 0xC9, 0xFD, 0x6F }}
};

#endif /* LORAWAN_KEYS_H */
/* [] END OF FILE */
