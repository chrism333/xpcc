// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
// ----------------------------------------------------------------------------

#ifndef	XPCC_INTERPOLATION__LINEAR_HPP
#define	XPCC_INTERPOLATION__LINEAR_HPP

#include <stdint.h>

#include <xpcc/utils/arithmetic_traits.hpp>
#include <xpcc/data_structure/pair.hpp>
#include <xpcc/architecture/general/accessor.hpp>

namespace xpcc
{
	namespace interpolation
	{
		/**
		 * \brief	Linear interpolation between two points
		 * 
		 * Example:
		 * \code
		 * typedef xpcc::Pair<int8_t, int16_t> MyPair;
		 * 
		 * FLASH(MyPair flashValues[6]) = {
		 *     { 30, -200 },
		 *     { 50, 0 },
		 *     { 90, 50 },
		 *     { 150, 2050 },
		 *     { 200, 3000 },
		 *     { 220, 20000 }
		 * };
		 * 
		 * xpcc::interpolation::Linear<MyPair, xpcc::accessor::Flash> value(xpcc::accessor::asFlash(flashValues), 6);
		 * 
		 * ...
		 * 
		 * int8_t a = 20;
		 * int16_t b;
		 * 
		 * b = value.interpolate(a);
		 * \endcode
		 * 
		 * \todo	needs documentation
		 * \ingroup	interpolation
		 */
		template <typename T,
				  template <typename> class Accessor = ::xpcc::accessor::Ram>
		class Linear
		{
		public:
			typedef typename T::FirstType InputType;
			typedef typename T::SecondType OutputType;
			
			typedef typename ArithmeticTraits< OutputType >::SignedType OutputSignedType;
			typedef typename ArithmeticTraits< OutputSignedType >::DoubleType WideType;
			
		public:
			Linear(Accessor<T> points, uint8_t numPoints);
			
			OutputType 
			interpolate(const InputType& value) const;
			
		private:
			const accessor::Flash<T> points;
			const uint8_t numPoints; 
		};
	}
}

#include "linear_impl.hpp"

#endif	// XPCC_INTERPOLATION__LINEAR_HPP