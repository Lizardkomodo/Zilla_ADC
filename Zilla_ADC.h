/*
 * Zilla_ADC.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Benny
 */

#ifndef INC_ZILLA_ADC_H_
#define INC_ZILLA_ADC_H_
#endif /* INC_ZILLA_ADC_H_ */

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"


//Define address for I2C ADC
#define ADC_ADDRESS 0x00
#define ADC_REGISTER 0x00





void Zilla_ADC_Init();

uint8_t Zilla_I2C_GetValue_DMA();

uint8_t Zilla_ADC_GetValue_DMA();

uint8_t Zilla_I2C_GetValue();

uint16_t Zilla_ADC_GetValue();

uint16_t Zilla_ADC_GetTemperatureF();

uint16_t Zilla_ADC_GetTemperature_Steinhart();

uint16_t Zilla_ADC_GetTemperature_SciFiDev();

void zilla_i2c_write(uint8_t device_address, uint8_t register_pointer, uint8_t register_value); //Made static so its only valid ion this file, and does not conflict if zilla functions are used in main code


void zilla_i2c_read(uint8_t device_address, uint8_t register_hex, uint8_t receive_array);
