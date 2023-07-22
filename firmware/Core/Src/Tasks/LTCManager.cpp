/*
 * LTCManager.cpp
 *
 *  Created on: Jul 1, 2023
 *      Author: Piotr Lesicki
 */

#include "PerypherialManagers/LtcController.hpp"
#include "app_freertos.h"
#include "main.h"
#include "PerypherialManagers/Gpio.hpp"

static SPI_HandleTypeDef * hspi = &hspi2;
static std::array < std::array < float, 12 >, 1> volts;

void vLTCManagerTask(void *argument)
{
	LtcController ltc_ctrl(GpioOut(NLTC2_CS_GPIO_Port, NLTC2_CS_Pin, true), hspi);

	ltc_ctrl.wakeUp();
	auto cfg_status = ltc_ctrl.configure();

	while(true)
	{
		auto dr_v_status = ltc_ctrl.readVoltages(volts);
		osDelay(100);
	}

}