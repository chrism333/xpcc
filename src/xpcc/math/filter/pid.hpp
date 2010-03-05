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

#ifndef XPCC__PID_HPP
#define XPCC__PID_HPP

#include <xpcc/utils/arithmetic_traits.hpp>

namespace xpcc
{
	/**
	 * \brief	Dummy implementation for a feedforward function
	 * 
	 * Does not add any value to the calculation.
	 *
	 * \internal
	 */
	template<typename T>
	T
	feedforwardDummy(const T& target) {
		(void) target;
		return 0;
	}
	
	/**
	 * \brief	A proportional-integral-derivative controller (PID controller)
	 *
	 * The PID controller is one of the basic controlling algorithm.
	 *
	 * The \p maxErrorSum is to be used, to limit the internal integrator and so
	 * provide an anti wind up.
	 *
	 * With the template parameter \ScaleFactor this class provides an
	 * fix point capability with integer types.
	 *
	 * The \p feedforward can be used as hook to call a external function
	 * (call back) to calculate a forward value.
	 *
	 * \todo	check implementation
	 * \todo	use the faster avr::mul and avr::mac functions
	 * 
	 * \author	Fabian Greif
	 * \ingroup	filter
	 */
	template<typename T, unsigned int ScaleFactor = 1>
	class Pid
	{
		typedef typename ArithmeticTraits<T>::DoubleType T_DOUBLE;
		typedef T (* FeedforwardFunction)(const T&);
	
	public:
		typedef T ValueType;

		/**
		 * \brief	Parameter for a PID calculation
		 */
		struct Parameter
		{
			Parameter(const T& kp = 0, const T& ki = 0, const T& kd = 0,
					  const T& maxErrorSum = 0, const T& maxOutput = 0);
			
			T kp;		///< proportional gain
			T ki;		///< integral gain
			T kd;		///< differentail gain
			
			T maxErrorSum;	///< integral will be limited to this value
			T maxOutput;	///< output will be limited to this value
		};
		
	public:
		/**
		 * \param	kp	proportional gain
		 * \param	ki	integral gain
		 * \param	kd	differentail gain
		 * \param	maxErrorSum	integral will be limited to this value
		 * \param	maxOutput	output will be limited to this value
		 * \param	feedforward	callback function to calculate a forward value
		 **/
		Pid(const T& kp = 0, const T& ki = 0, const T& kd = 0,
				const T& maxErrorSum = 0, const T& maxOutput = 0,
				FeedforwardFunction feedforward = feedforwardDummy<T>);


		/**
		 * \param	parameter	list of parameters to the controller
		 * \param	feedforward	callback function to calculate a forward value
		 **/
		Pid(Parameter& parameter,
				FeedforwardFunction feedforward = feedforwardDummy<T>);
		
		/**
		 * Reset the parameters of the controller.
		 *
		 * \param	parameter	list of parameters to the controller
		 **/
		void
		setParameter(const Parameter& parameter);
		
		/**
		 * \brief	Reset all values
		 */
		void
		reset();
		
		/**
		 * \brief	Set a new target value
		 */
		void
		setTarget(const T& value)
		{
			target = value;
		}

		/**
		 * \brief	Returns the actual taget value
		 */
		inline const T&
		getTarget() const
		{
			return this->target;
		}
		
		/**
		 * \brief	Calculate a new output value
		 *
		 * \param	input	The actual measured value, will be compared to the
		 * 					target value.
		 */
		void
		update(const T& input);
		
		/**
		 * \brief	Returns the calculated actuating variable.
		 */
		inline const T&
		getValue() const
		{
			return output;
		}

	private:
		Parameter parameter;
		FeedforwardFunction feedforward;
		
		T target;
		T errorSum;
		T lastError;
		T output;
	};
}

#include "pid_impl.hpp"

#endif // XPCC__PID_HPP