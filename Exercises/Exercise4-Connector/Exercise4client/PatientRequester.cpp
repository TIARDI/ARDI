#include "stdafx.h"
#include "PatientRequester.hpp"
#include <iostream>
#include <array>

PatientRequester::PatientRequester(Reactor* reactor, bool& running) 
	: reactor_(reactor), running_(running)
{
}

void PatientRequester::open()
{
	reactor_->register_handler(this, (Event_type)(WRITE|READ));
}

void PatientRequester::handle_event(HANDLE h, Event_type eType)
{
	if( eType == READ)
	{
		std::array<char, 100> buffer;
		buffer.fill(0);

		auto res = ipc_stream_.recv(buffer.data(),buffer.size() - 1);
		if (res == 0)
		{
			std::cout << "CLIENT: Server closed connection." << std::endl;
			Reactor::instance()->remove_handler(this, eType);
			return;
		}

		std::string response(buffer.data());

		std::cout << "CLIENT: Server sent response: " << response << std::endl;
	}
	else if(eType == WRITE)
	{
		std::string cpr;
		std::cout << "Input patient CPR to request info: ";
		std::cin >> cpr;
		std::cout << std::endl;

		if(cpr == "exit")
		{
			running_ = false;
			return;
		}

		ipc_stream_.send(cpr.data(), cpr.size());
	}
}

PatientRequester::~PatientRequester(void)
{
}
