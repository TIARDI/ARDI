// Exercise2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Reactor.hpp"
#include "INET_Address.hpp"
#include "Alarm_EventAcceptor.hpp"
#include "PatientValue_EventAcceptor.hpp"
#include "Log_EventAcceptor.hpp"

const u_short ALARM_PORT = 2001;
const u_short PATIENT_PORT = 2002;
const u_short LOG_PORT = 2003;

int main(int argc, char* argv[])
{
	INET_Address alarmAddr(ALARM_PORT, INADDR_ANY);
	INET_Address patientAddr(PATIENT_PORT, INADDR_ANY);
	INET_Address logAddr(LOG_PORT, INADDR_ANY);

	// Get Reactor
	Reactor* reactor = Reactor::instance();

	// Register different accepters for the reactor
	Alarm_EventAcceptor aec(alarmAddr, reactor);
	PatientValue_EventAcceptor pea(patientAddr, reactor);
	Log_EventAcceptor lea(logAddr, reactor);

	// DO STUFF!!!
	while(1)
		reactor->handle_events();

	return 0;
}

