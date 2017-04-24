/**
ROS/IOP Bridge
Copyright (c) 2017 Fraunhofer

This program is dual licensed; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation, or
enter into a proprietary license agreement with the copyright
holder.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; or you can read the full license at
<http://www.gnu.de/documents/gpl-2.0.html>
*/

/** \author Alexander Tiderko */


#ifndef EVENTSPLUGIN_1_0_H
#define EVENTSPLUGIN_1_0_H

#include <iop_component_fkie/iop_plugin_interface.h>
#include "urn_jaus_jss_core_Events_1_0/EventsService.h"
#include "urn_jaus_jss_core_Transport_1_0/TransportService.h"


namespace iop
{

class DllExport EventsPlugin_1_0 : public PluginInterface
{
public:
	EventsPlugin_1_0();

	JTS::Service* get_iop_service();
	const std::type_info & get_iop_service_type();
	const std::type_info & get_base_service_type();
	void create_jts_service(JTS::JausRouter* jaus_router);
	virtual ~EventsPlugin_1_0();

	jVariableLengthString get_service_uri() { return "urn:jaus:jss:core:Events"; }
	jUnsignedByte get_version_number_major() { return 1; }
	jUnsignedByte get_version_number_minor() { return 0; }

protected:
	urn_jaus_jss_core_Events_1_0::EventsService *p_my_service;

};

};

#endif