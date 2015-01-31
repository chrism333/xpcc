// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

//
// 32F072DISCOVERY
// Discovery kit for STM32F072 series
// http://www.st.com/web/en/catalog/tools/FM116/SC959/SS1532/PF259724
//

#ifndef XPCC_STM32_F072_DISCOVERY_HPP
#define XPCC_STM32_F072_DISCOVERY_HPP

using namespace xpcc::stm32;

using LedUp    = GpioOutputC6;
using LedDown  = GpioOutputC7;
using LedLeft  = GpioOutputC8;
using LedRight = GpioOutputC9;
using Button   = GpioInputA0;

/// STM32F072 running at 48MHz generated from the internal 48MHz clock
//using DefaultSystemClock = SystemClock<InternalClock<MHz48>, MHz48>;

#endif	// XPCC_STM32_F072_DISCOVERY_HPP
