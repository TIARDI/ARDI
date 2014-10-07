#include "stdafx.h"
#include "PatientRequester.hpp"
#include <iostream>


PatientRequester::PatientRequester(Reactor* reactor, INET_Address addr, bool& running) 
	: reactor_(reactor), running_(running)
{
}


void PatientRequester::open()
{
	reactor_->register_handler(this, WRITE);
}

void PatientRequester::handle_event(HANDLE h, Event_type eType)
{
	if(eType != WRITE)
	{
		std::cout << "CLIENT: Unhandled event type: " << eType << std::endl;
		return;
	}

	std::string cpr;
	std::cout << "Input patient CPR to request info: ";
	std::cin >> cpr;
	std::cout << std::endl;


}

PatientRequester::~PatientRequester(void)
{
}
