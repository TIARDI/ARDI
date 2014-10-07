#include "stdafx.h"
#include "Patient_Handler.hpp"
#include "Reactor.hpp"
#include <array>

void Patient_Handler::open()
{
	Reactor::instance()->register_handler(this, READ);
}

void Patient_Handler::handle_event(HANDLE h, Event_type eType)
{
	std::array<char, 100> buffer;
	buffer.fill(0);

	auto res = ipc_stream_.recv(buffer.data(),buffer.size() - 1);
	if (res == 0)
	{
		Reactor::instance()->remove_handler(this, eType);
		return;
	}

	std::string val(buffer.data());
	val.erase(std::remove_if(val.begin(), val.end(), ::isspace), val.end());

	std::string sendbuffer;
	if (val == "111111-1111")
		sendbuffer = "Rasmus,Bækgaard,AIDS";
	else if (val == "222222-2222")
		sendbuffer = "Lasse,Pedersen,Chlamydia";
	else if (val == "333333-3333")
		sendbuffer = "Martin,Manø,Gonorrhea";
	else if (val == "444444-4444")
		sendbuffer = "Christoffer,Werge,Herpes";
	else
		sendbuffer = "Unknown patient\n\r";

	ipc_stream_.send(sendbuffer.c_str(), sendbuffer.size() + 1);
}

Patient_Handler::~Patient_Handler()
{}
