#include "stdafx.h"
#include "Reactor.hpp"
#include "ConcreteReactor.hpp"

Reactor::Reactor(Reactor_Implementation* reactor_impl) 
	: reactor_impl_(reactor_impl)
{}

// Define a singleton access point (GoF pattern)
Reactor* Reactor::instance()
{
	static ConcreteReactor reactorInstance;

	return &reactorInstance;
}