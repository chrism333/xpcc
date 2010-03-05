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

#ifndef XPCC__TIPC_H
#define XPCC__TIPC_H

#include <xpcc/driver/tipc/header.hpp>
#include <xpcc/driver/tipc/tipc_receiver.hpp>
#include <xpcc/driver/tipc/tipc_transmitter.hpp>
#include <xpcc/data_structure/smart_pointer.hpp>

#include "../backend_interface.hpp"

namespace xpcc
{
	namespace tipc
	{
		/**
		 * \brief	Class that connects the communication to the tipc.
		 *
		 * \ingroup	tipc
		 * \author	Martin Rosekeit <martin.rosekeit@rwth-aachen.de>
		 */
		class Tipc : public BackendInterface
		{
			public :
				Tipc();

				~Tipc();

				inline void
				addEventId(uint8_t id)
				{
					this->receiver.addEventId(id);
				}

				inline void
				addReceiverId(uint8_t id)
				{
					this->receiver.addReceiverId(id);
				}

				/// Check if a new packet was received by the backend
				virtual bool
				isPacketAvailable() const;

				/// Access the packet.
				virtual const ::xpcc::Header&
				getPacketHeader() const;

				virtual const ::xpcc::SmartPointer
				getPacketPayload() const;

				virtual uint8_t
				getPacketPayloadSize() const;

				virtual void
				dropPacket();

				virtual void
				update();
				
				/**
				 * Send a Message.
				 */
				virtual void
				sendPacket(const ::xpcc::Header &header,
						   SmartPointer payload = SmartPointer());

			private :
				Receiver	receiver;
				Transmitter	transmitter;
		};
	};
};
 
#endif	// XPCC__TIPC_H