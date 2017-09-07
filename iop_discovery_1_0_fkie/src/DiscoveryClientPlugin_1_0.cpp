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

#include <DiscoveryClientPlugin_1_0.h>
#include <pluginlib/class_list_macros.h>
#include <iop_component_fkie/iop_component.h>
#include "urn_jaus_jss_core_Discovery_1_0/DiscoveryService.h"

using namespace iop;
using namespace urn_jaus_jss_core_Discovery_1_0;
using namespace urn_jaus_jss_core_DiscoveryClient_1_0;
using namespace urn_jaus_jss_core_EventsClient_1_0;
using namespace urn_jaus_jss_core_Transport_1_0;


DiscoveryClientPlugin_1_0::DiscoveryClientPlugin_1_0()
{
	p_my_service = NULL;
	p_base_service = NULL;
	p_transport_service = NULL;
}

DiscoveryClientPlugin_1_0::~DiscoveryClientPlugin_1_0()
{

}

JTS::Service* DiscoveryClientPlugin_1_0::get_iop_service()
{
	return p_my_service;
}

const std::type_info & DiscoveryClientPlugin_1_0::get_iop_service_type()
{
	return typeid(DiscoveryClientService);
}

const std::type_info & DiscoveryClientPlugin_1_0::get_base_service_type()
{
	return typeid(EventsClientService);
}


void DiscoveryClientPlugin_1_0::create_jts_service(JTS::JausRouter* jaus_router)
{
	p_base_service = dynamic_cast<EventsClientService *>(get_base_service());
	p_transport_service = dynamic_cast<TransportService *>(get_base_service(2));
	p_my_service = new DiscoveryClientService(jaus_router, p_transport_service, p_base_service);
}

void DiscoveryClientPlugin_1_0::init_jts_service()
{
	iop::Component &cmp = iop::Component::get_instance();
	DiscoveryService *discovery_srv = dynamic_cast<DiscoveryService*>(cmp.get_service(typeid(DiscoveryService)));
	if (discovery_srv != NULL)
		p_my_service->pDiscoveryClient_ReceiveFSM->setDiscoveryFSM(discovery_srv->pDiscovery_ReceiveFSM);
}

void DiscoveryClientPlugin_1_0::register_service(PluginInterface *plugin)
{
	if (plugin != NULL) {
		p_my_service->pDiscoveryClient_ReceiveFSM->appendServiceUri(plugin->get_service_uri(), plugin->get_version_number_major(), plugin->get_version_number_minor());
	}
}

PLUGINLIB_EXPORT_CLASS(iop::DiscoveryClientPlugin_1_0, iop::PluginInterface)