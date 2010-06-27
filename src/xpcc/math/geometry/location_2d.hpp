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

#ifndef	XPCC__LOCATION_2D_HPP
#define	XPCC__LOCATION_2D_HPP

#include <cmath>

#include <xpcc/io/iostream.hpp>

#include "angle.hpp"
#include "point_2d.hpp"

namespace xpcc
{
	/**
	 * \brief	Location
	 * 
	 * \ingroup	geometry
	 */
	template <typename T = int16_t>
	class Location2D
	{
	public:
		typedef ::xpcc::Point2D<T> Point;
		
		Location2D();
		
		Location2D(const Point& point, const float& phi);
		
		Location2D(const T& x, const T& y, const float& phi);
		
		/// Add a position increment
		void
		update(Location2D& diff);
		
		/**
		 * \brief	Add a increment only in x-direction
		 * 
		 * \todo	usefull description what this function does
		 */
		void
		update(T x, float phi);
		
		inline const Point&
		getPoint() const;
		
		void
		setPoint(const Point& point);
		
		void
		setPoint(const T& x, const T& y);
		
		inline float
		getAngle() const;
		
		void
		setAngle(const float& phi);
		
		/// Convert between Location-objects with different base-types
		template<typename U>
		operator Location2D<U>() const;
		
	private:
		template <typename U>
		friend IOStream&
		operator <<( IOStream&, const Location2D<U>&);
		
		Point point;
		float phi;
	};

	/**
	 * \brief	Stream operator to \b xpcc::Location<T>
	 *
	 * \ingroup	geometry
	 */
	template<typename T>
	IOStream&
	operator<<(IOStream& os, const Location2D<T>& l);
}

#include "location_2d_impl.hpp"

#endif	// XPCC__LOCATION_2D_HPP