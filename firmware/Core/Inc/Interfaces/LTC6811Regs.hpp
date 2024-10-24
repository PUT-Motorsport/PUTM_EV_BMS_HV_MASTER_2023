/*
 * LTC6811Regs.hpp
 *
 *  Created on: Jul 27, 2023
 *      Author: piotr
 */

#ifndef INC_PERYPHERIALMANAGERS_LTC6811REGS_HPP_
#define INC_PERYPHERIALMANAGERS_LTC6811REGS_HPP_

#include <main.h>
#include <concepts>
#include <cstring>

namespace Ltc6811
{
	// dummy structs for clarification for other shit
	struct IWriteReadRegisterGroup { };
	struct IReadRegisterGroup { };

	// config registers rd/wr
	struct __packed Config : public IWriteReadRegisterGroup
	{
		struct
		{
			uint32_t adcopt : 1;
			uint32_t dten : 1;
			uint32_t refon : 1;
			uint32_t gpio1 : 1;
			uint32_t gpio2 : 1;
			uint32_t gpio3 : 1;
			uint32_t gpio4 : 1;
			uint32_t gpio5 : 1;

			uint32_t vuv : 12;
			uint32_t vov : 12;
		};

		struct
		{
			uint16_t dcc1 : 1;
			uint16_t dcc2 : 1;
			uint16_t dcc3 : 1;
			uint16_t dcc4 : 1;
			uint16_t dcc5 : 1;
			uint16_t dcc6 : 1;
			uint16_t dcc7 : 1;
			uint16_t dcc8 : 1;

			uint16_t dcc9 : 1;
			uint16_t dcc10 : 1;
			uint16_t dcc11 : 1;
			uint16_t dcc12 : 1;
			DischargeTime dcto : 4;
		};
	};
	// cell voltage rd [A:D] / [1:4]
	struct CellVoltage : public IReadRegisterGroup
	{
		struct Cell
		{
			//uint8_t bytes[2];
			uint16_t val;
		} channel[3];
	};
	// generic reg gpio[0:2] OR gpio[3:4] + ref voltage   rd
	struct AuxilliaryVoltage : public IReadRegisterGroup
	{
		struct Gpio
		{
			//uint8_t bytes[2];
			uint16_t val;
		} gpio[3];
	};
	// gpio[0:2] voltage A  rd
	struct AuxilliaryVoltageA : public IReadRegisterGroup
	{
		struct Gpio
		{
			//uint8_t bytes[2];
			uint16_t val;
		} gpio[3];
	};
	// gpio[3:4] + ref voltage A  rd
	struct AuxilliaryVoltageB : public IReadRegisterGroup
	{
		struct Gpio
		{
			//uint8_t bytes[2];
			uint16_t val;
		} gpio[2];
		struct Ref
		{
			//uint8_t bytes[2];
			uint16_t val;
		} ref;
	};
	// status rd
	struct StatusA : public IReadRegisterGroup
	{
		//uint8_t sc[2];
		uint16_t sc;
		//uint8_t itmp[2];
		uint16_t itmp;
		//uint8_t va[2];
		uint16_t va;
	};
	struct StatusB : public IReadRegisterGroup
	{
		//uint8_t vd[2];
		uint16_t vd;
		struct
		{
			uint8_t c1ov : 1;
			uint8_t c1uv : 1;
			uint8_t c2ov : 1;
			uint8_t c2uv : 1;
			uint8_t c3ov : 1;
			uint8_t c3uv : 1;
			uint8_t c4ov : 1;
			uint8_t c4uv : 1;
		};
		struct
		{
			uint8_t c5ov : 1;
			uint8_t c5uv : 1;
			uint8_t c6ov : 1;
			uint8_t c6uv : 1;
			uint8_t c7ov : 1;
			uint8_t c7uv : 1;
			uint8_t c8ov : 1;
			uint8_t c8uv : 1;
		};
		struct
		{
			uint8_t c9ov : 1;
			uint8_t c9uv : 1;
			uint8_t c10ov : 1;
			uint8_t c10uv : 1;
			uint8_t c11ov : 1;
			uint8_t c11uv : 1;
			uint8_t c12ov : 1;
			uint8_t c12uv : 1;
		};
		struct
		{
			uint8_t thsd : 1;
			uint8_t muxfail : 1;
			uint8_t rsvd : 2;
			uint8_t rvs : 4;
		};
	};
	// communication rd
	struct Communication : public IWriteReadRegisterGroup
	{
		struct
		{
			uint8_t d0_msb : 4;
			uint8_t icom0 : 4;
		};
		struct
		{
			uint8_t fcomm0 : 4;
			uint8_t d0_lsb : 4;
		};
		struct
		{
			uint8_t d1_msb : 4;
			uint8_t icomm1 : 4;
		};
		struct
		{
			uint8_t fcomm1 : 4;
			uint8_t d1_lsb : 4;
		};
		struct
		{
			uint8_t d2_msb : 4;
			uint8_t icomm2 : 4;
		};
		struct
		{
			uint8_t fcomm2 : 4;
			uint8_t d2_lsb : 4;
		};
	};
	#if LTC6804_COMPATIBLE_ONLY == 0
	// S control rd/wr
	struct SControl : public IWriteReadRegisterGroup
	{
		struct
		{
			uint8_t sctl1 : 4;
			uint8_t sctl2 : 4;
		};
		struct
		{
			uint8_t sctl3 : 4;
			uint8_t sctl4 : 4;
		};
		struct
		{
			uint8_t sctl5 : 4;
			uint8_t sctl6 : 4;
		};
		struct
		{
			uint8_t sctl7 : 4;
			uint8_t sctl8 : 4;
		};
		struct
		{
			uint8_t sctl9 : 4;
			uint8_t sctl10 : 4;
		};
		struct
		{
			uint8_t sctl11 : 4;
			uint8_t sctl12 : 4;
		};
	};

	enum struct PwmValue : uint8_t
	{
		Disable
	};
	// PWM rd/wr
	struct Pwm : public IWriteReadRegisterGroup
	{
		struct
		{
			PwmValue pwm1 : 4;
			PwmValue pwm2 : 4;
		};
		struct
		{
			PwmValue pwm3 : 4;
			PwmValue pwm4 : 4;
		};
		struct
		{
			PwmValue pwm5 : 4;
			PwmValue pwm6 : 4;
		};
		struct
		{
			PwmValue pwm7 : 4;
			PwmValue pwm8 : 4;
		};
		struct
		{
			PwmValue pwm9 : 4;
			PwmValue pwm10 : 4;
		};
		struct
		{
			PwmValue pwm11 : 4;
			PwmValue pwm12: 4;
		};
	};
	#endif

	template < typename RegisterGroup >
	concept WriteReadRegisterGroup = 	std::is_base_of<IWriteReadRegisterGroup, RegisterGroup>::value	and
										not std::is_polymorphic< RegisterGroup >::value						and
										sizeof(RegisterGroup) == 6;

	template < typename RegisterGroup >
	concept ReadRegisterGroup = std::is_base_of<IReadRegisterGroup, RegisterGroup>::value 	and
								not std::is_polymorphic< RegisterGroup >::value					and
								sizeof(RegisterGroup) == 6;

	template < WriteReadRegisterGroup RegisterGroup >
	void serializeRegisterGroup(uint8_t *destination, RegisterGroup &source)
	{
		std::memcpy(destination, &source, 6);
	}

//	std::array < uint8_t, 6 > serializeRegisterGroup(RegisterGroup &source)
//	{
//		std::array < uint8_t, 6 > destination;
//		std::memcpy(destination.data(), &source, 6);
//		return destination;
//	}

	template < ReadRegisterGroup RegisterGroup >
	void deserializeRegisterGroup(RegisterGroup *destination, uint8_t const *source)
	{
		std::memcpy(destination, source, 6);
	}

//	template < ReadRegisterGroup RegisterGroup >
//	RegisterGroup deserializeRegisterGroup(uint8_t const *source)
//	{
//		static RegisterGroup destination;
//		std::memcpy(&destination, source, 6);
//		return destination;
//	}
}

#endif /* INC_PERYPHERIALMANAGERS_LTC6811REGS_HPP_ */
