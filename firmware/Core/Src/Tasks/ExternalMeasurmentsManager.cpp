/*
 * ExternalMeasurmentsManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <PerypherialManagers/MCP356Controller.hpp>
#include <PerypherialManagers/SpiDmaController.hpp>
#include "app_freertos.h"
#include "spi.h"
#include "main.h"
#include "StackData.hpp"
#include <array>

static SPI_HandleTypeDef &hspi = hspi3;

static MCP356Controller car(GpioOut(NMES_CAR_CS_GPIO_Port, NMES_CAR_CS_Pin, true), hspi, MCP356xVersion::MCP3561);
static MCP356Controller acu(GpioOut(NMES_ACU_CS_GPIO_Port, NMES_ACU_CS_Pin, true), hspi, MCP356xVersion::MCP3561);
static MCP356Controller isens(GpioOut(NMES_ISENS_CS_GPIO_Port, NMES_ISENS_CS_Pin, true), hspi, MCP356xVersion::MCP3562);

//static std::array < std::pair < MCP356x::MuxIn, MCP356x::MuxIn >, 3 > adc_requests
//{
//	{ MCP356x::MuxIn::Ch0, MCP356x::MuxIn::Ch1 },
//	{ MCP356x::MuxIn::Ch0, MCP356x::MuxIn::Ch1 },
//	{ MCP356x::MuxIn::Ch2, MCP356x::MuxIn::Ch3 }
//};
//static std::array < MCP356Controller*, 3 > mcps_ref { &car, &acu, &isens };

extern GpioOut led_warning;
extern GpioIn charger_conected;

void vExternalMeasurmentsManagerTask(void *argument)
{
	while(true)
	{
		FullStackDataInstance::getAndModify().ltc_data.charger_connected = charger_conected.isActive();

		osDelay(100);
	}
}


