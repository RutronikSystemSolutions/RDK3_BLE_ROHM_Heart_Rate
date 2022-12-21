/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the RDK3 BLE ROHM Heart Rate
*              Application for ModusToolbox.
*
* Related Document: See README.md
*
*
*  Created on: 2022-06-16
*  Company: Rutronik Elektronische Bauelemente GmbH
*  Address: Jonavos g. 30, Kaunas 44262, Lithuania
*  Author: GDR
*
*******************************************************************************
* (c) 2019-2021, Cypress Semiconductor Corporation. All rights reserved.
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
*
* Rutronik Elektronische Bauelemente GmbH Disclaimer: The evaluation board
* including the software is for testing purposes only and,
* because it has limited functions and limited resilience, is not suitable
* for permanent use under real conditions. If the evaluation board is
* nevertheless used under real conditions, this is done at one’s responsibility;
* any liability of Rutronik is insofar excluded
*******************************************************************************/

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "cycfg_ble.h"
#include "bh1792.h"
#include "bh1792_port.h"
#include "hr_bh1792.h"

/*Priority for bh1792 interrupts*/
#define BH1792_IRQ_PRIORITY		5

static void bh1792_isr(void *handler_arg, cyhal_gpio_event_t event);
static void isr_scp_timer(void *callback_arg, cyhal_timer_event_t event);
static cy_rslt_t scp_timer_init(void);
extern int HostMain(void);

cyhal_i2c_t I2C_scb3;
cyhal_i2c_cfg_t I2C_cfg;
cyhal_gpio_callback_data_t bh_isr_data =
{
		.callback = bh1792_isr,
		.callback_arg = NULL,
};
cyhal_timer_t scp_timer;
uint8_t    s_cnt_freq = 0;
bh1792_t      m_bh1792;
bh1792_data_t m_bh1792_dat;

int main(void)
{
	cy_rslt_t result;
	int32_t bh_rslt;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }

    /*Enable debug output via KitProg UART*/
    result = cy_retarget_io_init( KITPROG_TX, KITPROG_RX, CY_RETARGET_IO_BAUDRATE);
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }
    printf("\x1b[2J\x1b[;H");
    printf("RDK3 ROHM Heart Rate Sensor Example\r\n\n");

    /*Initialize LEDs*/
    result = cyhal_gpio_init( LED1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}
    result = cyhal_gpio_init( LED2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}
    result = cyhal_gpio_init( LED3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}

    /*Charger control*/
    result = cyhal_gpio_init(CHR_DIS, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}
    cyhal_gpio_write((cyhal_gpio_t)CHR_DIS, true); /*Charger OFF*/

    /*Initialize External Pin Interrupt*/
    result = cyhal_gpio_init(ARDU_IO6, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULLUP, true);
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}
    /*Register callback functions */
    cyhal_gpio_register_callback(ARDU_IO6, &bh_isr_data);
    /* Enable falling edge interrupt events */
    cyhal_gpio_enable_event(ARDU_IO6, CYHAL_GPIO_IRQ_FALL, BH1792_IRQ_PRIORITY, true);

    /*Initialize a timer for the BH1729 periodic measurements*/
    result = scp_timer_init();
    if (result != CY_RSLT_SUCCESS)
    {CY_ASSERT(0);}

    /*Enable interrupts*/
    __enable_irq();

    /*I2C Peripheral Configuration*/
    I2C_cfg.is_slave = false;
    I2C_cfg.address = 0;
    I2C_cfg.frequencyhal_hz = 100000UL;
    result = cyhal_i2c_init(&I2C_scb3, ARDU_SDA, ARDU_SCL, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }
    result = cyhal_i2c_configure(&I2C_scb3, &I2C_cfg);
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }

    /*Initialize BH1792 Sensor*/
    bh_rslt = bh1792_Init(&sBH1792);
    if(bh_rslt != BH1792_SUCCESS)
    {
    	CY_ASSERT(0);
    }

    /*Initialize BH1792 Heart Rate Library*/
    bh_rslt = hr_bh1792_Init();
    if(bh_rslt != BH1792_SUCCESS)
    {
    	CY_ASSERT(0);
    }

    /*Setup the BH1792 Sensor*/
    sBH1792.prm.sel_adc  = BH1792_PRM_SEL_ADC_GREEN;
    sBH1792.prm.msr      = BH1792_PRM_MSR_SINGLE;
    sBH1792.prm.led_en   = (BH1792_PRM_LED_EN1_0 << 1) | BH1792_PRM_LED_EN2_0;
    sBH1792.prm.led_cur1 = BH1792_PRM_LED_CUR1_MA(1);
    sBH1792.prm.led_cur2 = BH1792_PRM_LED_CUR2_MA(1);
    sBH1792.prm.ir_th    = 0xFFFC;
    sBH1792.prm.int_sel  = BH1792_PRM_INT_SEL_SGL;
    bh_rslt = bh1792_SetParams();
    if(bh_rslt != BH1792_SUCCESS)
    {CY_ASSERT(0);}
    bh_rslt = hr_bh1792_StartMeasure();
    if(bh_rslt != BH1792_SUCCESS)
    {CY_ASSERT(0);}

    /* Run Host main */
    HostMain();

    for (;;)
    {
    }
}

/* Interrupt handler callback function */
void bh1792_isr(void *handler_arg, cyhal_gpio_event_t event)
{
	CY_UNUSED_PARAMETER(handler_arg);
    CY_UNUSED_PARAMETER(event);
    int32_t bh_rslt = 0;
    u16_pair_t s_pwData_test;
    float32_t pw_test;
    //static uint8_t  bpm     = 0U;
    //static uint8_t  wearing = 0U;

    bh_rslt = hr_bh1792_Calc(s_cnt_freq, &m_bh1792_dat, &s_pwData_test, &pw_test);
    if(bh_rslt != BH1792_SUCCESS)
    {CY_ASSERT(0);}

    /*Indicate heart beat*/
    if((int)pw_test > 0)
    {cyhal_gpio_write((cyhal_gpio_t)LED3, CYBSP_LED_STATE_ON);}
    else
    {cyhal_gpio_write((cyhal_gpio_t)LED3, CYBSP_LED_STATE_OFF);}

    //hr_bh1792_GetData(&bpm, &wearing);
    //printf("%d, %d, %d,\r\n", bpm, wearing, (int)pw_test);
}

/*Timer Interrupt for BH1792 Measurements*/
static void isr_scp_timer(void *callback_arg, cyhal_timer_event_t event)
{
    (void) callback_arg;
    (void) event;
    int32_t bh_rslt = 0;

    pw_GetParam(BH1792_PRM_CTRL2_CUR_LED1, &(m_bh1792.prm.led_cur1));
    pw_GetParam(BH1792_PRM_CTRL3_CUR_LED2, &(m_bh1792.prm.led_cur2));
    bh_rslt = bh1792_SetParams();
    if(bh_rslt != BH1792_SUCCESS)
    {CY_ASSERT(0);}
    bh_rslt = hr_bh1792_StartMeasure();
    if(bh_rslt != BH1792_SUCCESS)
    {CY_ASSERT(0);}

    if(s_cnt_freq <31)
    {
    	s_cnt_freq++;
    }
}

/*Timer for BH1792 Measurements Initialization*/
static cy_rslt_t scp_timer_init(void)
{
	 cy_rslt_t result;
	 const cyhal_timer_cfg_t scp_cfg =
	 {
	     .compare_value = 0,                 /* Timer compare value, not used */
	     .period = 3124,                     /* Defines the timer period */
		 //.period = 312,                     /* Defines the timer period */
	     .direction = CYHAL_TIMER_DIR_UP,    /* Timer counts up */
	     .is_compare = false,                /* Don't use compare mode */
	     .is_continuous = true,              /* Run the timer indefinitely */
	     .value = 0                          /* Initial value of counter */
	 };

	 result = cyhal_timer_init(&scp_timer, NC, NULL);
	 if (result != CY_RSLT_SUCCESS)
	 {return result;}

	 result = cyhal_timer_configure(&scp_timer, &scp_cfg);
	 if (result != CY_RSLT_SUCCESS)
	 {return result;}

	 result = cyhal_timer_set_frequency(&scp_timer, 100000);
	 if (result != CY_RSLT_SUCCESS)
	 {return result;}

	 cyhal_timer_register_callback(&scp_timer, isr_scp_timer, NULL);

	 cyhal_timer_enable_event(&scp_timer, CYHAL_TIMER_IRQ_TERMINAL_COUNT, 3, true);

	 result =  cyhal_timer_start(&scp_timer);
	 if (result != CY_RSLT_SUCCESS)
	 {return result;}

	 return result;
}

/* [] END OF FILE */
