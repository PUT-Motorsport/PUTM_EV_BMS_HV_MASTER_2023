/*
 * ChargerCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Jan
 */

#include <main.h>
#include <fdcan.h>

#include <app_freertos.h>
#include <Controllers/ChargeBalanceController.hpp>
#include <Controllers/ChargerController.hpp>
#include <Controllers/GpioController.hpp>
#include <StackData.hpp>
#include <Utils/CanUtils.hpp>
#include <Config.hpp>

static FDCAN_HandleTypeDef &hfdcan = hfdcan3;
static auto& fsd = FullStackDataInstance::set();

void vChargerCANManagerTask(void *argument)
{

	constexpr static float charge_voltage = LtcConfig::CELL_COUNT * (4.2f - 0.05f);
	startCan(hfdcan);

	static ChargerCanRxController charger_rx {};
	static ChargeBalanceController balanceController(fsd);
	balanceController.disableBalance();

	uint32_t balance_start { HAL_GetTick() };
	bool balance_toggle = false;

	while (true)
	{
		osDelay(200);

		if (not fsd.charger.balance_enable and not fsd.charger.charging_enable)
		{
			continue;
		}

		balanceController.update();

		if(HAL_GetTick() > balance_start + ChargerConfig::balance_time)
		{
			if(balance_toggle and fsd.charger.balance_enable and not fsd.charger.charging_enable)
			{
				balanceController.recalcBalance();
			}
			else
			{
				balanceController.disableBalance();
			}
			balance_toggle = not balance_toggle;
			balance_start = HAL_GetTick();
		}

		while (getCanFifoMessageCount(hfdcan))
		{
			charger_rx.update();
		}
		ChargerCanTxMessage frame
		{
			charge_voltage,
			FullStackDataInstance::get().charger.charge_current,
			FullStackDataInstance::get().charger.charging_enable
		};
		auto status = frame.send();
		if(status != HAL_OK)
			auto b = 'c';
	}
}
