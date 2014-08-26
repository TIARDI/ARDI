
#include "stdafx.h"
#include <iostream>
#include "SOCK_Acceptor.hpp"
#include "SOCK_Connector.hpp"
#include "SOCK_stream.h"
#include "INET_Address.hpp"


void RunClient(std::string serverIp)
{
	std::string message = "Hello from client";
	SOCK_Stream stream;
	SOCK_Connector connector;
	INET_Address addr(2222,inet_addr(serverIp.c_str()));
	connector.connect(stream,addr);
	
	stream.send(message.c_str(), message.size(),0);


}

void RunServer()
{

	struct sockaddr_in sock_addr;
	INET_Address inet(2222,INADDR_ANY);
	SOCK_Acceptor acceptor(inet);
	
	SOCK_Stream stream;

	while(true) 
	{
		acceptor.accept (stream);
		//receive from
	}
}

int main(int argc, char *argv[])
{
	if(argv[1] == "c" && argc < 3)
	{
		std::cout << "Running as client..." << std::endl;
		RunClient(std::string(argv[2]));
	}
	else if(argv[1] == "s")
	{
		std::cout << "Running as server..." << std::endl;
		RunServer();
	}
	else
	{
		std::cout << "Arguments not accepted. Closing..." << std::endl;
		return -1;
	}

}

