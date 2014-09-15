
#include "stdafx.h"
#include "Log_EventHandler.h"
#include <array>


Log_EventHandler::Log_EventHandler(std::shared_ptr<SOCK_Stream> stream, Reactor* reactor)
	: _peer_stream(stream), _reactor(reactor)
{
	_reactor->register_handler(this, Event_type::READ);
}
Log_EventHandler::~Log_EventHandler()
{
	_reactor->remove_handler(this,READ); //Correct?
	delete this;
}
	
void Log_EventHandler::handle_event(HANDLE h, Event_type eType)
{

		if(eType == READ)
		{

			std::array<char, 100> buffer;
			buffer.fill(0);
			auto res = _peer_stream->recv(buffer.data(),buffer.size(),0);

			if(res == 0)
			{
				std::cout << "Log_EventHandler: connection closed." << std::endl;
				_reactor->remove_handler(this, eType);
				return;

			}

			std::cout << "Log message: " << buffer.data() << std::endl;
		}
		else
		{
			std::cout << "Error from Log_EventHandler" << std::endl;
			_reactor->remove_handler(this,READ);
			delete this;
		}
}

HANDLE Log_EventHandler::get_handle() const
{
	return (HANDLE)_peer_stream->get_handle();
}




