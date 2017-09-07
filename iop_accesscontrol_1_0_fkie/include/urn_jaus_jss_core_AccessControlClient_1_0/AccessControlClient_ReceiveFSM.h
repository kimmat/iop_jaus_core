/*
 * Copyright (c) 2015, Fraunhofer FKIE/CMS
 * All rights reserved.
 * Parts of this code are generated by JAUS Tool Set
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Fraunhofer nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


/** \author Alexander Tiderko */


#ifndef ACCESSCONTROLCLIENT_RECEIVEFSM_H
#define ACCESSCONTROLCLIENT_RECEIVEFSM_H

#include "JausUtils.h"
#include "InternalEvents/InternalEventHandler.h"
#include "Transport/JausTransport.h"
#include "JTSStateMachine.h"
#include "urn_jaus_jss_core_AccessControlClient_1_0/Messages/MessageSet.h"
#include "urn_jaus_jss_core_AccessControlClient_1_0/InternalEvents/InternalEventsSet.h"

typedef JTS::Receive_1_0 Receive;
typedef JTS::Send_1_0 Send;

#include "urn_jaus_jss_core_Transport_1_0/Transport_ReceiveFSM.h"
#include "urn_jaus_jss_core_EventsClient_1_0/EventsClient_ReceiveFSM.h"


#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <ros/ros.h>
#include "AccessControlClient_ReceiveFSM_sm.h"

namespace urn_jaus_jss_core_AccessControlClient_1_0
{

class DllExport AccessControlClient_ReceiveFSM : public JTS::StateMachine
{
public:
	static unsigned char ACCESS_STATE_NOT_AVAILABLE;
	static unsigned char ACCESS_STATE_NOT_CONTROLLED;
	static unsigned char ACCESS_STATE_CONTROL_RELEASED;
	static unsigned char ACCESS_STATE_CONTROL_ACCEPTED;
	static unsigned char ACCESS_STATE_TIMEOUT;
	static unsigned char ACCESS_STATE_INSUFFICIENT_AUTHORITY;

	AccessControlClient_ReceiveFSM(urn_jaus_jss_core_Transport_1_0::Transport_ReceiveFSM* pTransport_ReceiveFSM, urn_jaus_jss_core_EventsClient_1_0::EventsClient_ReceiveFSM* pEventsClient_ReceiveFSM);
	virtual ~AccessControlClient_ReceiveFSM();

	/// Handle notifications on parent state changes
	virtual void setupNotifications();

	/// Action Methods
	virtual void handleConfirmControlAction(ConfirmControl msg, Receive::Body::ReceiveRec transportData);
	virtual void handleRejectControlAction(RejectControl msg, Receive::Body::ReceiveRec transportData);
	virtual void handleReportAuthorityAction(ReportAuthority msg, Receive::Body::ReceiveRec transportData);
	virtual void handleReportControlAction(ReportControl msg, Receive::Body::ReceiveRec transportData);
	virtual void handleReportTimeoutAction(ReportTimeout msg, Receive::Body::ReceiveRec transportData);
	virtual void resetControlTimerAction();


	/// Guard Methods

	template<class T>
	void requestAccess(JausAddress address, void(T::*reply_handler)(JausAddress &, unsigned char code), T*obj, jUnsignedByte authority=255)
	{
		boost::function<void (JausAddress &, unsigned char code)> callback = boost::bind(reply_handler, obj, _1, _2);;
		p_reply_callbacks[address.get()].push_back(callback);
		pRequestAccess(address, authority);
	}

	template<class T>
	void releaseAccess(JausAddress address, void(T::*reply_handler)(JausAddress &, unsigned char code), T*obj)
	{
		boost::function<void (JausAddress &, unsigned char code)> callback = boost::bind(reply_handler, obj, _1, _2);;
		p_reply_callbacks[address.get()].push_back(callback);
		pReleaseAccess(address);
	}
	void releaseAccess(JausAddress address)
	{
		pReleaseAccess(address);
	}
	bool hasAccess(JausAddress address);
//	template<class T>
//	void set_access_reply_handler(void(T::*handler)(JausAddress &, unsigned char code), T*obj) {
//		p_class_access_reply_callback = boost::bind(handler, obj, _1, _2);
//	}

	AccessControlClient_ReceiveFSMContext *context;

protected:

	/// References to parent FSMs
	urn_jaus_jss_core_Transport_1_0::Transport_ReceiveFSM* pTransport_ReceiveFSM;
	urn_jaus_jss_core_EventsClient_1_0::EventsClient_ReceiveFSM* pEventsClient_ReceiveFSM;

	std::map <unsigned int, std::vector<boost::function<void (JausAddress &, unsigned char code)> > > p_reply_callbacks;  // unsigned int -> JausAddress::get(), list with callbacks to this address
	boost::function<void (JausAddress &, unsigned char code)> p_class_access_reply_callback;
	jUnsignedByte p_default_timeout;
	DeVivo::Junior::JrMutex mutex;
	ros::WallTimer p_timer;
	std::map <unsigned int, int> p_timeouts; // unsigned int -> JausAddress::get(), timeout, reported from services
	std::map <unsigned int, double> p_controlled_clients; // unsigned int -> JausAddress::get(), timestamp of last request
	std::map <unsigned int, jUnsignedByte> p_auths; // unsigned int -> JausAddress::get(), authority
	std::map <unsigned int, JausAddress> p_addresses; // unsigned int -> JausAddress::get(), JausAddress
	std::vector< JausAddress > p_on_request_clients;
	JTS::InternalEvent *p_timeout_event;
	bool pIsOnAccess(JausAddress address);
	void pTimeoutCallback(const ros::WallTimerEvent& event);
	void pInformReplyCallbacks(JausAddress &address, unsigned char code);
	void pRequestAccess(JausAddress address, jUnsignedByte authority=255);
	void pReleaseAccess(JausAddress address);
};

};

#endif // ACCESSCONTROLCLIENT_RECEIVEFSM_H