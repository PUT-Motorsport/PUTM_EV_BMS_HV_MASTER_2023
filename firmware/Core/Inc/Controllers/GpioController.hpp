/*
 * Gpio.hpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#ifndef INC_CONTROLLERS_GPIOCONTROLLER_HPP_
#define INC_CONTROLLERS_GPIOCONTROLLER_HPP_

#include <main.h>

class Gpio
{
	public:
		Gpio(const GPIO_TypeDef * const port, const uint32_t pin, const bool is_inverted);

		//virtual ~Gpio() = default;

	protected:
		const GPIO_TypeDef * const port;
		const uint32_t pin;
		const bool is_inverted;
};

class GpioOut : public Gpio
{
	public:
		GpioOut(const GPIO_TypeDef * const port, const uint32_t pin);
		GpioOut(const GPIO_TypeDef * const port, const uint32_t pin, const bool is_inverted);

		void activate();
		void deactivate();

		void toggle();

		~GpioOut() { };
};

class GpioIn : public Gpio
{
	public:
		GpioIn(const GPIO_TypeDef * const port, const uint32_t pin);
		GpioIn(const GPIO_TypeDef * const port, const uint32_t pin, const bool is_inverted);

		bool isActive();

		~GpioIn() { };
};

#endif /* INC_CONTROLLERS_GPIOCONTROLLER_HPP_ */
