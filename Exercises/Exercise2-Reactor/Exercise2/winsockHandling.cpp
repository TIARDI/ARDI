#include "stdafx.h"
#include <winsock2.h>
#include <iostream>
#include <mutex>
#include "winsockHandling.hpp"

namespace winsockHandling
{
	static int references = 0;
	static std::mutex mut;

	void init_winsock()
	{
		std::lock_guard<std::mutex> lock(mut);

		if (references == 0) //first use of winsock. call WSAStartUp.
		{
			WSADATA wsaData;

			// MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:

			if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			{
				std::cerr << "WSAStartup failed." << std::endl;
				exit(1);
			}
		}

		references++;
	}

	void close_winsock()
	{
		std::lock_guard<std::mutex> lock(mut);

		references--;

		if (references == 0)
		{
			if (WSACleanup() != 0)
			{
				std::cerr << "WSACleanup failed." << std::endl;
			}
		}
	}
}
