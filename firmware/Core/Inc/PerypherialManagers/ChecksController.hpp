/*
 * Checks.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_CHECKSCONTROLLER_HPP_
#define INC_PERYPHERIALMANAGERS_CHECKSCONTROLLER_HPP_

#include <algorithm>
#include <main.h>

#include <Config.hpp>
#include <Interfaces/StateErrorWarning.hpp>

namespace Checks
{

    ErrorOrWarning underVoltage(const FullStackData &stackData)
    {
    	static int32_t error_cntr{0};
        auto iter = std::ranges::find_if(stackData.ltc_data.voltages, [](const auto &cellVoltage)
                                         { return cellVoltage < ChecksConfig::CELL_MIN_VOLTAGE; });
        if (iter not_eq std::end(stackData.ltc_data.voltages))
        {
        	++error_cntr;
        }
        else if(error_cntr > 0){
        	--error_cntr;
        }

        if(error_cntr > ChecksConfig::VOLTAGE_ERROR_COUNT_MAX){
        	return std::make_pair(CriticalErrorsEnum::UnderVoltage, std::distance(std::begin(stackData.ltc_data.temp_C), iter));
        }
        return std::nullopt;
    }

    ErrorOrWarning overVoltage(const FullStackData &stackData)
    {
    	static int32_t error_cntr{0};

    	if(stackData.charge_balance.balance_enable){
    		return std::nullopt;
    	}

    	auto iter = std::ranges::find_if(stackData.ltc_data.voltages, [](const auto &cellVoltage)
                                         { return cellVoltage < ChecksConfig::CELL_MIN_VOLTAGE; });

        if (iter not_eq std::end(stackData.ltc_data.voltages))
        {
        	++error_cntr;
        }
        else if(error_cntr > 0){
        	--error_cntr;
        }

        if(error_cntr > ChecksConfig::VOLTAGE_ERROR_COUNT_MAX){
        	return std::make_pair(CriticalErrorsEnum::UnderVoltage, std::distance(std::begin(stackData.ltc_data.temp_C), iter));
        }
        return std::nullopt;
    }

    ErrorOrWarning underTemperature(const FullStackData &stackData)
    {
    	static int32_t error_cntr{0};
        auto iter = std::ranges::find_if(stackData.ltc_data.temp_C, [](const auto &cellTemperature)
                                         { return cellTemperature < ChecksConfig::CELL_MIN_TEMPERATURE; });
        if (iter not_eq std::end(stackData.ltc_data.temp_C))
        {
        	++error_cntr;
        }
        else if(error_cntr > 0){
        	--error_cntr;
        }

        if(error_cntr > ChecksConfig::TEMP_ERROR_COUNT_MAX){
        	return std::make_pair(CriticalErrorsEnum::UnderTemperature, std::distance(std::begin(stackData.ltc_data.temp_C), iter));
        }
        return std::nullopt;
    }

    ErrorOrWarning overTemperature(const FullStackData &stackData)
    {
    	static int32_t error_cntr{0};
        auto iter = std::ranges::find_if(stackData.ltc_data.temp_C, [](const auto &cellTemperature)
                                         { return cellTemperature > ChecksConfig::CELL_MAX_TEMPERATURE; });

        if (iter not_eq std::end(stackData.ltc_data.temp_C))
        {
        	++error_cntr;
        }
        else if(error_cntr > 0){
        	--error_cntr;
        }

        if(error_cntr > ChecksConfig::TEMP_ERROR_COUNT_MAX){
        	return std::make_pair(CriticalErrorsEnum::UnderTemperature, std::distance(std::begin(stackData.ltc_data.temp_C), iter));
        }
        return std::nullopt;
    }

    ErrorOrWarning overCurrent(const FullStackData &stackData)
    {
    	static int32_t error_cntr{0};
        bool overcurrent = std::abs(stackData.external_data.acu_curr) > ChecksConfig::BATTERY_MAX_CURRENT;
        bool disconnect = std::abs(stackData.external_data.acu_curr) > ChecksConfig::BATTERY_SENSOR_DISCONNECT;
        if (overcurrent and not disconnect)
        {
        	++error_cntr;
        }
        else if(error_cntr > 0){
        	--error_cntr;
        }

        if(error_cntr > ChecksConfig::CURRENT_ERROR_COUNT_MAX	){
        	return std::make_pair(CriticalErrorsEnum::OverCurrent, 0);
        }
        return std::nullopt;
    }

    ErrorOrWarning CurrentSensorDisconnect(const FullStackData &stackData)
    {
    	static int32_t error_cntr{0};
    	bool disconnect = std::abs(stackData.external_data.acu_curr) > ChecksConfig::BATTERY_MAX_CURRENT;
    	if (disconnect)
    	{
    		++error_cntr;
    	}
    	else if(error_cntr > 0){
    		--error_cntr;
    	}
    	if(error_cntr > ChecksConfig::CURRENT_ERROR_COUNT_MAX	){
    		return std::make_pair(CriticalErrorsEnum::CurrentSensorDisconnected, 0);
    	}
    	return std::nullopt;
    }

}

#endif /* INC_PERYPHERIALMANAGERS_CHECKSCONTROLLER_HPP_ */
