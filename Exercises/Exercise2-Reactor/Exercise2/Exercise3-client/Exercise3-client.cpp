// Exercise3-client.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../INET_Address.hpp"
#include "../Reactor.hpp"
#include "LogSender_EventHandler.h"
#include "AlarmSender_EventHandler.hpp"
#include "PatientValSender_EventHandler.hpp"

const u_short ALARM_PORT = 2001;
const u_short PATIENT_PORT = 2002;
const u_short LOG_PORT = 2003;

int main(int argc, char* argv[])
{
	char* server;
	if (argc < 2)
		server = "127.0.0.1";
	else
		server = argv[2];

	INET_Address logAddr(LOG_PORT, inet_addr(server));
	INET_Address alarmAddr(ALARM_PORT, inet_addr(server));
	INET_Address patientAddr(PATIENT_PORT, inet_addr(server));	

	// Get Reactor
	auto reactor = Reactor::instance();

	// Register different eventHandlers for the reactor
	LogSender_EventHandler logSender(logAddr, reactor);
	AlarmSender_EventHandler alarmSender(alarmAddr, reactor);
	PatientValSender_EventHandler patientValSender(patientAddr, reactor);


	// DO STUFF!!!
	//for (;;)
		reactor->handle_events(); //don't loop, just send one message pr. handler.

	return 0;
}

