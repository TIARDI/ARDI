#pragma once

class Bulk_Data_Router: public Peer_Router {
public:
	virtual void open() {
		// activate router in a separate process
		if (fork() ==0) {
			// this method can block because it runs in its own process
			for (; ;)
				run();
		}
		// receive and route bulk data from/to peers
		virtual void run() {
			char buf[BUFSIZ];
			peer().recv(buf, sizeof(buf));
			// routing takes place here
		}
	};