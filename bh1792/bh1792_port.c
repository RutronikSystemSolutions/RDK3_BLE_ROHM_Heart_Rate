/*
 * bh1792_port.c
 *
 *  Created on: Sep 1, 2022
 *      Author: Gintaras
 */

#include "bh1792_port.h"
#include "stdlib.h"

extern cyhal_i2c_t I2C_scb3;

static int32_t bh1792_i2c_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint8_t size);
static int32_t bh1792_i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint8_t size);

bh1792_t sBH1792 =
{
		.fnRead = bh1792_i2c_read,
		.fnWrite = bh1792_i2c_write,
};

int32_t bh1792_i2c_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint8_t size)
{
	cy_rslt_t result;

	result = cyhal_i2c_master_write( &I2C_scb3, (uint16_t)slave_addr, &reg_addr, 1, 5, false );
    if (result != CY_RSLT_SUCCESS)
    {
    	return BH1792_I2C_ERR;
    }

	result = (int8_t)cyhal_i2c_master_read(&I2C_scb3,(uint16_t)slave_addr, data, (uint16_t)size, 5, true);
	if (result != CY_RSLT_SUCCESS)
	{
		 return BH1792_I2C_ERR;
	}

    return BH1792_SUCCESS;
};

int32_t bh1792_i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint8_t size)
{
	cy_rslt_t result;
	uint8_t* i2c_data = NULL;

	/*Allocate buffer for transmission*/
    i2c_data = malloc(size+1);
    if(i2c_data == NULL)
    {
    	return BH1792_I2C_ERR;
    }
    /*Copy register address and all the data*/
    i2c_data[0] = reg_addr;
    memcpy(&i2c_data[1], data, size);

	result = (int8_t)cyhal_i2c_master_write(&I2C_scb3,(uint16_t)slave_addr, &reg_addr, 1, 5, true);
	if (result != CY_RSLT_SUCCESS)
	{
		free(i2c_data);
		return BH1792_I2C_ERR;
	}

	result = (int8_t)cyhal_i2c_master_write(&I2C_scb3,(uint16_t)slave_addr, i2c_data, (uint16_t)size+1, 5, true);
	if (result != CY_RSLT_SUCCESS)
	{
		free(i2c_data);
		return BH1792_I2C_ERR;
	}

	free(i2c_data);
    return BH1792_SUCCESS;
};



