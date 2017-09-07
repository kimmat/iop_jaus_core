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


#ifndef MANAGEMENTSERVICE_H
#define MANAGEMENTSERVICE_H

#include "Service.h"
#include "InternalEvents/InternalEventHandler.h"
#include "Transport/JausTransport.h"
#include "JConstants.h"
#include "urn_jaus_jss_core_Management_1_0/Messages/MessageSet.h"
#include "urn_jaus_jss_core_Management_1_0/InternalEvents/InternalEventsSet.h"
#include "Transport/OS.h"

#include "urn_jaus_jss_core_Transport_1_0/TransportService.h"
#include "urn_jaus_jss_core_Events_1_0/EventsService.h"
#include "urn_jaus_jss_core_AccessControl_1_0/AccessControlService.h"
#include "Management_ReceiveFSM.h"
#include "Management_SendFSM.h"


namespace urn_jaus_jss_core_Management_1_0
{

class DllExport ManagementService : public JTS::Service
{
public:
	ManagementService( JTS::JausRouter* jausRouter , urn_jaus_jss_core_Transport_1_0::TransportService* pTransportService, urn_jaus_jss_core_Events_1_0::EventsService* pEventsService, urn_jaus_jss_core_AccessControl_1_0::AccessControlService* pAccessControlService);
	virtual ~ManagementService();

	virtual bool processTransitions(JTS::InternalEvent* ie);
	virtual bool defaultTransitions(JTS::InternalEvent* ie);

	// FSMs are public so that children services can access them
	Management_ReceiveFSM* pManagement_ReceiveFSM;
	Management_SendFSM* pManagement_SendFSM;

        jVariableLengthString getUri() { return "urn:jaus:jss:core:Management"; }
        jUnsignedByte getMajorVersionNumber() { return 1; }
        jUnsignedByte getMinorVersionNumber() { return 0; }



protected:
	virtual void run();

};

};

#endif // MANAGEMENTSERVICE_H