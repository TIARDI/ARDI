#pragma once
#include "Service_Handler.hpp"

class Command_Router: public Peer_Router {
public:
	virtual void open() {
		char buf[BUFSIZ];
		peer().recv(buf, sizeof(buf));
		// routing takes place here
	}
};