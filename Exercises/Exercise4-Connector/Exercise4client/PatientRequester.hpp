#pragma once
#include "..\exercise 4\service_handler.hpp"
#include "..\exercise 4\INET_address.hpp"
#include "..\Exercise 4\Reactor.hpp"

class PatientRequester : public Service_Handler
{
public:
	PatientRequester(Reactor* reactor, bool& running);
	virtual void open();
	virtual void handle_event(HANDLE h, Event_type eType);
	virtual ~PatientRequester(void);

private:
	Reactor* reactor_;
	bool& running_;
};

