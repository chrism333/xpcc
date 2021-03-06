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
 */
// ----------------------------------------------------------------------------

#include <cmath>

#include <xpcc/math/filter/moving_average.hpp>

#include "moving_average_test.hpp"

namespace
{
    struct TestData
	{
		typedef int16_t Type;
		
		Type input;
		Type output;
	};

	struct TestDataFloat
	{
		typedef double Type;

		Type input;
		Type output;
	};

	static const TestData data[] =
	{
		{ 10,	2 },
		{ 10,	5 },
		{ 10,	7 },
		{ 10,	10 },
		{ -10,	5 },
		{ -10,	0 },
		{ 5,	-2 },
		{ 5,	-3 },
		{ 5,	1 },
		{ 5,	5 },
		{ 100,	28 },
		{ 100,	52 },
		{ 200,	101 },
		{ 200,	150 },
		{ 200,	175 },
		{ 200,	200 },
	};

	static const TestDataFloat dataF[] =
	{
		{ 10.0,	2.5 },
		{ 10.0,	5.0 },
		{ 10.0,	7.5 },
		{ 10.0,	10.0 },
		{ -10.0,	5.0 },
		{ -10.0,	0.0 },
		{ 5,	-1.25 },
		{ 5,	-2.5 },
		{ 5,	1.25 },
		{ 5,	5.0 },
		{ 100,	28.75 },
		{ 100,	52.5 },
		{ 200,	101.25 },
		{ 200,	150.0 },
		{ 200,	175.0 },
		{ 200,	200.0 },
	};
}

void
MovingAverageTest::testDefaultConstructor()
{
	xpcc::filter::MovingAverage<int16_t, 4> filter;

	TEST_ASSERT_EQUALS(filter.getValue(), 0);
}

void
MovingAverageTest::testConstructor()
{
	xpcc::filter::MovingAverage<int16_t, 4> filter(20);

	TEST_ASSERT_EQUALS(filter.getValue(), 20);
}

void
MovingAverageTest::testAverage()
{
	xpcc::filter::MovingAverage<TestData::Type, 4> filter;

	for (uint_fast8_t i = 0; i < (sizeof(data) / sizeof(TestData)); ++i)
	{
		filter.update(data[i].input);
		TEST_ASSERT_EQUALS(filter.getValue(), data[i].output);
	}
}

void
MovingAverageTest::testFloatAverage()
{
	xpcc::filter::MovingAverage<TestDataFloat::Type, 4> filter;
	for (uint_fast8_t i = 0; i < (sizeof(data) / sizeof(TestDataFloat)); ++i)
	{
		filter.update(dataF[i].input);
		TEST_ASSERT_TRUE(std::abs(filter.getValue()-dataF[i].output) < 1e-4);
	}
}
