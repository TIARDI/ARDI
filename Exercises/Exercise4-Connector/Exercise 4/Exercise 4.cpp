#include "stdafx.h"
#include "Acceptor.hpp"
#include "Patient_Handler.hpp"
#include "Reactor.hpp"
#include "LF_Thread_Pool.h"
#include <thread>
#include <exception>

typedef Acceptor<Patient_Handler> Patient_Acceptor;

#define PATIENT_PORT 2003

const int MAX_THREADS = 3;

void worker_function(LF_Thread_Pool *tp)
{
		tp->join();
}

int main(int argc, char* argv[])
{
	INET_Address patientAddr(PATIENT_PORT, INADDR_ANY);

	// Initialize concrete acceptor to listen for connections on 
	// well-known port
	Patient_Acceptor s_acceptor(patientAddr, Reactor::instance());

	LF_Thread_Pool* tp = LF_Thread_Pool::Instance();

	for (int i = 0; i < MAX_THREADS - 1; i++)
	{
		std::thread t(worker_function, tp);
		t.detach();
	}

	tp->join();

	// Event loop that accepts connection request events and processes
	// data from a gateway
	/*for (;;)
		Reactor::instance()->handle_events();*/
}
