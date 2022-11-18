/*******************************************************************************
* File Name: common.h
*
*  Version 1.0
*
* Description:
*  The common BLE application header.
*
*******************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef COMMON_H
#define COMMON_H
    
#include <stdio.h>


/***************************************
* Conditional Compilation Parameters
***************************************/
#define ENABLED                             (1u)
#define DISABLED                            (0u)

#define DEBUG_UART_ENABLED                  (ENABLED)


/***************************************
*        API Constants
***************************************/
#define ADV_TIMER_TIMEOUT                   (1u)              /* Сounts in s */ 
    
/***************************************
*      API Function Prototypes
***************************************/
/* Function Prototypes from host_main.c */
int HostMain(void);

/***************************************
*        Macros
***************************************/
#if (DEBUG_UART_ENABLED == ENABLED)
    #define DBG_PRINTF(...)                 (printf(__VA_ARGS__))
#else
    #define DBG_PRINTF(...)
#endif /* (DEBUG_UART_ENABLED == ENABLED) */


#endif /* COMMON_H */

/* [] END OF FILE */
