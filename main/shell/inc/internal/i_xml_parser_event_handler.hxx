/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


 
#ifndef I_XML_PARSER_EVENT_HANDLER_HXX_INCLUDED
#define I_XML_PARSER_EVENT_HANDLER_HXX_INCLUDED

#include <string>
#include <map>

#if defined(XML_UNICODE) || defined(XML_UNICODE_WCHAR_T)
	typedef std::wstring string_t;
	typedef wchar_t char_t;
#else
	typedef std::string string_t;
	typedef char char_t;
#endif

// name-value container
typedef std::map<string_t, string_t> xml_tag_attribute_container_t;


//#########################################
class i_xml_parser_event_handler
{
public:	
	virtual ~i_xml_parser_event_handler() {};
	
	virtual void start_document() = 0;
	
	virtual void end_document() = 0;

	virtual void start_element(
		const string_t& raw_name, 
		const string_t& local_name, 
		const xml_tag_attribute_container_t& attributes) = 0;

	virtual void end_element(
		const string_t& raw_name, 
		const string_t& local_name) = 0;

	virtual void characters(
		const string_t& character) = 0;

	virtual void ignore_whitespace(
		const string_t& whitespaces) = 0;

	virtual void processing_instruction(
		const string_t& target, const string_t& data) = 0;

	virtual void comment(const string_t& comment) = 0;
};

#endif

