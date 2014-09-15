
#include "stdafx.h"
#include "Log_EventHandler.h"

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
		char* rxValue = new char[];
		int res = _peer_stream->recv(rxValue,100,0);

		if(res == 0)
		{
			std::cout << "Connection closed... Closing handler" << std::endl;
						_reactor->remove_handler(this,READ);
			delete this;

		}
		else if(eType == READ)
		{

			std::cout << "Log message: " << std::string(rxValue) << std::endl;
			delete rxValue;
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
	return (HANDLE)_peer_stream.get_handle();
}




