/*
 * stackData.hpp
 *
 *  Created on: 20 lip 2023
 *      Author: piotr
 */

#ifndef STACKDATA_HPP_
#define STACKDATA_HPP_

#include "Config.hpp"
#include "Interfaces/StateErrorWarning.hpp"
#include <array>
#include <atomic>
#include "etl/flat_map.h"

struct FullStackData
{
	struct Ltc
	{
		std::array<std::atomic<float>, LtcConfig::CELL_COUNT> voltages { 0.f };
		std::array<std::atomic<bool>, LtcConfig::CELL_COUNT> discharge { false };
		std::array<std::atomic<float>, LtcConfig::TEMP_COUNT> temp { 0.f };
		std::array<std::atomic<float>, LtcConfig::TEMP_COUNT> temp_C { 0.f };
		std::atomic<float> min_temp { 0.f };
		std::atomic<float> avg_temp { 0.f };
		std::atomic<float> max_temp { 0.f };
		std::atomic<float> bat_volt { 0.f };
		std::atomic<float> soc { 0.f };
	} ltc;

	struct External
	{
		std::atomic<float> car_volt { 0.f };
		std::atomic<float> acu_volt { 0.f };
		std::atomic<float> acu_curr { 0.f };
		std::atomic<float> isens_ref { 0.f };

		std::atomic<bool> tsms_on { false };
		std::atomic<bool> charger_connected { true };

		std::atomic<bool> p_state{false};
		std::atomic<bool> m_state{false};
		std::atomic<bool> pre_state{false};

		std::atomic<int> imd_state { 0 };

		std::atomic<bool> ts_activation_button { false };
	} external;

	struct State
	{
		std::optional<Checks::CriticalError> error{std::nullopt};
		std::array<Checks::ErrorListElement, 6> list_of_errors;
		std::atomic<bool> in_error { false };
	} state;

	struct ChargeBalance
	{
		std::atomic<float> max_cell_voltage{4.15f};
		std::atomic<float> min_cell_voltage{3.0f};
		std::atomic<float> avg_cell_voltage{0.0f};
		std::atomic<float> median_cell_voltage{0.0f};
		std::atomic<float> std_dev_cell_voltage{0.0f};
		std::atomic<float> voltage_sum{0.0f};
		std::array<std::atomic<float>, LtcConfig::CELL_COUNT> pre_balance_voltages;
	} charge_balance;

	struct SoC
	{
		std::array<std::atomic<float>, LtcConfig::CELL_COUNT> cells_soc;
		std::atomic<float> avg;
	} soc;

	struct Charger
	{
		std::atomic<bool> balance_enable{false};
		std::atomic<uint32_t> balance_disable_tick{};
		std::atomic<bool> charging_enable{false};
		std::atomic<float> charge_current{0.0f};
		std::atomic<float> battery_voltage{0.0f};
		std::atomic<float> battery_current{0.0f};
	} charger;

	struct UsbEvents
	{
		std::atomic<bool> discharge_optical_visualisation { false };
		std::atomic<bool> charger_on { false };
		std::atomic<bool> communication_test { false };
	} usb_events;

	struct Time
	{
		std::atomic<uint32_t> tick;
	} time;

	FullStackData() = default;
	FullStackData(const FullStackData &) = delete;
	FullStackData &operator=(const FullStackData &) = delete;
};

class FullStackDataInstance
{
	public:
		inline static FullStackData instance;
		inline static FullStackData &set()
		{
			return instance;
		}

		inline static const FullStackData &get()
		{
			return instance;
		}
};

#endif /* STACKDATA_HPP_ */
