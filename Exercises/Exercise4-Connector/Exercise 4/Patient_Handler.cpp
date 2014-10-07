#include "stdafx.h"
#include "Patient_Handler.hpp"
#include "Reactor.hpp"
#include <array>
#include <iostream>
#include <thread>
#include "LF_Event_Handler.hpp"

void Patient_Handler::open()
{
	LF_Event_Handler* lf_eh = new LF_Event_Handler(this, LF_Thread_Pool::Instance());	Reactor::instance()->register_handler(lf_eh, (Event_type)(READ|WRITE));}

void Patient_Handler::handle_event(HANDLE h, Event_type eType)
{
	static std::string sendbuffer;

	if(eType == READ)
	{
		std::array<char, 100> buffer;
		buffer.fill(0);

		auto res = ipc_stream_.recv(buffer.data(),buffer.size() - 1);
		if (res == 0)
		{
			std::cout << "SERVER: Client closed connection." << std::endl;
			Reactor::instance()->remove_handler(this, eType);
			return;
		}

		std::string val(buffer.data());
		val.erase(std::remove_if(val.begin(), val.end(), ::isspace), val.end()); //trim whitespace

		std::cout << "SERVER: Client sent request: " << val << std::endl;

		if (val == "111111-1111")
			sendbuffer = "Rasmus,Bækgaard,MRSA";
		else if (val == "222222-2222")
			sendbuffer = "Lasse,Pedersen,SARS";
		else if (val == "333333-3333")
			sendbuffer = "Martin,Manø,Otitis Media";
		else if (val == "444444-4444")
			sendbuffer = "Christoffer,Werge,EBOLA";
		else
			sendbuffer = "Unknown patient";
	} 
	else if(eType == WRITE)
	{
		if(!sendbuffer.empty())
		{
			std::cout << "SERVER: Sending response: " << sendbuffer << std::endl;
			ipc_stream_.send(sendbuffer.c_str(), sendbuffer.size() + 1);
			sendbuffer.clear();
		}
	}

	//std::this_thread::sleep_for(std::chrono::seconds::duration(10));
}

Patient_Handler::~Patient_Handler()
{}
