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

#include <EventsClientPlugin_1_0.h>
#include <pluginlib/class_list_macros.h>

using namespace iop;
using namespace urn_jaus_jss_core_EventsClient_1_0;
using namespace urn_jaus_jss_core_Transport_1_0;

EventsClientPlugin_1_0::EventsClientPlugin_1_0()
{
	p_my_service = NULL;
}

EventsClientPlugin_1_0::~EventsClientPlugin_1_0()
{

}

JTS::Service* EventsClientPlugin_1_0::get_iop_service()
{
	return p_my_service;
}

const std::type_info & EventsClientPlugin_1_0::get_iop_service_type()
{
	return typeid(EventsClientService);
}

const std::type_info & EventsClientPlugin_1_0::get_base_service_type()
{
	return typeid(TransportService);
}


void EventsClientPlugin_1_0::create_jts_service(JTS::JausRouter* jaus_router)
{
	p_my_service = new EventsClientService(jaus_router, dynamic_cast<TransportService *>(get_base_service()));
}

PLUGINLIB_EXPORT_CLASS(iop::EventsClientPlugin_1_0, iop::PluginInterface)