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

static float A = 0.6416252210e-3, B = 2.280518351e-4, C = 0.5691148404e-7;  //100k Values from datasheet https://www.tme.eu/Document/f9d2f5e38227fc1c7d979e546ff51768/NTCM-100K-B3950.pdf

#define SERIESRESISTOR 102000          //Value of the series resistor in ohms
#define THERMISTOR25C 100000       //Nominal resistance of the thermistor at 25°C in ohms



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



uint16_t Zilla_ADC_GetTemperature_HighSideNTC_SciFiDev(){
	float resistance;
	float temperature;
	float placeholder;
	float logRes;
		//uint8_t tempdat8bit;
		   HAL_ADC_Start(&hadc1);
			HAL_ADC_PollForConversion(&hadc1, 100);
			//HAL_ADC_PollForConversion(&hadc1, 100);
			//HAL_ADC_PollForConversion(&hadc1, 100);
			placeholder = HAL_ADC_GetValue(&hadc1);
			//HAL_ADC_GetValue(&hadc1);
			//HAL_ADC_GetValue(&hadc1);


			resistance = 4094 * SERIESRESISTOR;
			resistance = resistance / placeholder;
			resistance = resistance - SERIESRESISTOR;
			logRes = log(resistance);
			temperature = A + B*logRes + C*logRes*logRes*logRes;
			temperature = 1 / temperature;
			temperature = temperature - 273.15;
			temperature = (temperature * 9.0)/ 5.0 + 32.0;
	          return temperature;



}

uint16_t Zilla_ADC_GetTemperature_LowSideNTC_SciFiDev(){
	float resistance;
	float placeholder;
	float temperature;
	float logRes;
		//uint8_t tempdat8bit;
		   HAL_ADC_Start(&hadc1);
			HAL_ADC_PollForConversion(&hadc1, 100);
			//HAL_ADC_PollForConversion(&hadc1, 100);
			//HAL_ADC_PollForConversion(&hadc1, 100);
			resistance = HAL_ADC_GetValue(&hadc1);
			//HAL_ADC_GetValue(&hadc1);
			//HAL_ADC_GetValue(&hadc1);
			placeholder = 4094 - resistance;
			resistance = resistance * SERIESRESISTOR;
			resistance = resistance / placeholder;
			logRes = log(resistance);
			temperature = A + B*logRes + C*logRes*logRes*logRes;
			temperature = 1 / temperature;
			temperature = temperature - 273.15;
			temperature = (temperature * 9.0)/ 5.0 + 32.0;
	          return temperature;

}





void zilla_i2c_write(uint8_t device_address, uint8_t register_pointer,
		uint8_t register_value) //Made static so its only valid ion this file, and does not conflict if zilla functions are used in main code
{
	uint8_t data[2];

	data[0] = register_pointer;     // 0x0C in your example
	data[1] = register_value;       // LSB byte of 16bit data

	HAL_I2C_Master_Transmit(&hi2c1, device_address << 1, data, 2, 100); // data is the start pointer of our array
}



