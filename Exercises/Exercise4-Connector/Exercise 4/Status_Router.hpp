#pragma once
#include "Thread_Manager.hpp"


class Status_Router: public Peer_Router {
public:
	virtual void open() {
		// Make this handler run in a separate thread
		Thread_Manager::instance()->spawn(
			&Status_Router::svc_run, this);
	}
	static void *svc_run(Status_Router *this_obj) {
		for (; ;)
			this_obj->run();
	}
	// receive and process status data from Gateway
	virtual void run() {
		char buf[BUFSIZ];
		peer().recv(buf, sizeof(buf)); 
		// routing takes place here
	}
};