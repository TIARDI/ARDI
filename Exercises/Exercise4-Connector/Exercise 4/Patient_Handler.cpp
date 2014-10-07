#include "stdafx.h"
#include "Patient_Handler.hpp"
#include "Reactor.hpp"

void Patient_Handler::open()
{
	Reactor::instance()->register_handler(this, WRITE);
}

void Patient_Handler::handle_event(HANDLE h, Event_type eType)
{
	char buffer[100];
	ipc_stream_.recv(buffer,100,0);
	std::string val(buffer);
	if(val == "111111-1111")
		ipc_stream_.send("Rasmus,Bækgaard,AIDS",20,0);
	else if(val == "222222-2222")
		ipc_stream_.send("Lasse,Pedersen,Chlamydia",23,0);
	else if(val == "333333-3333")
		ipc_stream_.send("Martin,Manø,Gonorrhea",21,0);
	else if(val == "444444-4444")
		ipc_stream_.send("Christoffer,Werge,Herpes",24,0);
}

Patient_Handler::~Patient_Handler()
{}
