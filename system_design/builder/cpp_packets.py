#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright (c) 2009, Roboterclub Aachen e.V.
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of the Roboterclub Aachen e.V. nor the
#    names of its contributors may be used to endorse or promote products
#    derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# $Id$
# -----------------------------------------------------------------------------

import os
import builder_base
import filter.cpp as filter

# -----------------------------------------------------------------------------
def filter_subtype(value):
	""" value needs to be parser.structure.SubType """
	type = filter.typeName(value.type.name)
	variable = filter.variableName(value.name)
	if value.type.isArray:
		return "%s %s[%s]" % (type, variable, value.type.count)
	else:
		return "%s %s" % (type, variable)

def filter_constructor(classtype, default=True):
	if default:
		return "%s()" % filter.typeName(classtype.name)
	else:
		parameter = []
		for item in classtype.iter():
			if item.type.isArray:
				raise builder.BuilderException("Array handling is incomplete " \
						"right now! Could not generate code for %s" % item)
			else:
				type = filter.typeName(item.type.name)
				name = filter.variableName(item.name)
				
				parameter.append("%s %s" % (type, name))
		
		return "%s(%s)" % (filter.typeName(classtype.name), ", ".join(parameter))

def filter_initialization_list(classtype, default=True):
	initList = []
	for item in classtype.iter():
		if item.type.isArray:
			raise builder.BuilderException("Array handling is incomplete " \
					"right now! Could not generate code for %s" % item)
		else:
			type = filter.typeName(item.type.name)
			name = filter.variableName(item.name)
			
			if default:
				initList.append("%s()" % name)
			else:
				initList.append("%s(%s)" % (name, name))
	
	return ", ".join(initList)

# -----------------------------------------------------------------------------
class TypeBuilder(builder_base.Builder):
	
	VERSION = "$Id$"
	
	def setup(self, optparser):
		optparser.add_option(
				"--source_path",
				dest = "source_path",
				default = None,
				help = "Output path for the source file")
		optparser.add_option(
				"--header_path",
				dest = "header_path",
				default = None,
				help = "Output path for the header file")
	
	def generate(self):
		# check the commandline options
		if self.options.outpath:
			source_path = self.options.outpath
			header_path = self.options.outpath
		elif self.options.source_path and self.options.header_path:
			source_path = self.options.source_path
			header_path = self.options.header_path
		else:
			raise builder.BuilderException("You need to provide an output path!")
		
		cppFilter = {
			'enumElement': filter.enumElement,
			'variableName': filter.variableName,
			'typeName': filter.typeName,
			'subtype': filter_subtype,
			'generateConstructor': filter_constructor,
			'generateInitializationList': filter_initialization_list
		}
		
		template_header = self.template('templates/robot_packets.hpp.tpl', filter=cppFilter)
		template_source = self.template('templates/robot_packets.cpp.tpl', filter=cppFilter)
		
		substitutions = {
			'components': self.tree.components,
			'actions': self.tree.components.actions,
			'events': self.tree.events,
			'packets': self.tree.types
		}
		
		file = os.path.join(header_path, 'packets.hpp')
		self.write(file, template_header.render(substitutions) + "\n")
		
		file = os.path.join(source_path, 'packets.cpp')
		self.write(file, template_source.render(substitutions) + "\n")

# -----------------------------------------------------------------------------
if __name__ == '__main__':
	TypeBuilder().generate()