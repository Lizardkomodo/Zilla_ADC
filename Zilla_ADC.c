/*
 * Zilla_ADC.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Benny
 */

#include "Zilla_ADC.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal.h"
#include <math.h>


extern I2C_HandleTypeDef hi2c1;
extern ADC_HandleTypeDef hadc1;

static float R1 = 18000;
static float logR2, R2, T;
static float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


void Zilla_ADC_Init(){
	 HAL_ADC_Init(&hadc1);

//	 HAL_ADC_Init(&hadc2);
//	 HAL_ADC_Init(&hadc3);
}

uint8_t Zilla_I2C_GetValue_DMA(){


	return 1;

}

uint8_t Zilla_ADC_GetValue_DMA();

uint8_t Zilla_I2C_GetValue(){
	uint8_t charge_status_data =0;
	HAL_I2C_Mem_Read(&hi2c1, ADC_ADDRESS << 1, ADC_REGISTER, 1, &charge_status_data, 1, 100);
return charge_status_data;



}

uint16_t Zilla_ADC_GetValue(){
	float tempdata16bit;
	//uint8_t tempdat8bit;
	   HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 100);
		//HAL_ADC_PollForConversion(&hadc1, 100);
		//HAL_ADC_PollForConversion(&hadc1, 100);

		tempdata16bit = HAL_ADC_GetValue(&hadc1);
		//HAL_ADC_GetValue(&hadc1);
		//HAL_ADC_GetValue(&hadc1);

		return tempdata16bit;


}

uint16_t Zilla_ADC_GetTemperatureF(){
	float tempdata;
	//uint8_t tempdat8bit;
	   HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 100);
		//HAL_ADC_PollForConversion(&hadc1, 100);
		//HAL_ADC_PollForConversion(&hadc1, 100);

		tempdata = HAL_ADC_GetValue(&hadc1);
		//HAL_ADC_GetValue(&hadc1);
		//HAL_ADC_GetValue(&hadc1);

		  R2 = R1 * (4095 / (float)tempdata - 1.0);
		  R2 = fabsf(R2);
		  logR2 = log(R2);
		  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
		  T = T - 273.15;
		  T = (T * 9.0)/ 5.0 + 32.0;
		return T;


}







void zilla_i2c_write(uint8_t device_address, uint8_t register_pointer,
		uint8_t register_value) //Made static so its only valid ion this file, and does not conflict if zilla functions are used in main code
{
	uint8_t data[2];

	data[0] = register_pointer;     // 0x0C in your example
	data[1] = register_value;       // LSB byte of 16bit data

	HAL_I2C_Master_Transmit(&hi2c1, device_address << 1, data, 2, 100); // data is the start pointer of our array
}




