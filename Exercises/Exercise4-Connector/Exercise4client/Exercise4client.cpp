// Exercise4client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PatientRequester.hpp"
#include "..\Exercise 4\Connector.hpp"
#include <chrono>
#include <thread>

#define PATIENT_PORT 2003

bool running = true; 

int main(int argc, char* argv[])
{
	char* server;
	if (argc < 2)
		server = "127.0.0.1";
	else
		server = argv[2];

	INET_Address serverAddr(PATIENT_PORT, inet_addr(server));

	PatientRequester patientRequester(Reactor::instance(), running);

	Connector<PatientRequester> connector;

	connector.connect(&patientRequester, serverAddr);

	std::chrono::milliseconds dura( 20 );

	while(running)
	{
		std::this_thread::sleep_for( dura ); //add delay to allow server's response to reach client before calling select()
		Reactor::instance()->handle_events();
	}
	
	return 0;
}

