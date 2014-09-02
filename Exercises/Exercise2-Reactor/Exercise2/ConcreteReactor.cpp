#include "stdafx.h"
#include "ConcreteReactor.hpp"
#include "Select_Reactor_Implementation.hpp"

ConcreteReactor::ConcreteReactor()
	: Reactor(new Select_Reactor_Implementation())
{
}

ConcreteReactor::~ConcreteReactor()
{
	delete reactor_impl_;
}

void ConcreteReactor::register_handler(Event_Handler *eh, Event_type et)
{
	reactor_impl_->register_handler(eh, et);
}

void ConcreteReactor::remove_handler(Event_Handler *eh, Event_type et)
{
	reactor_impl_->remove_handler(eh, et);
}

void ConcreteReactor::handle_events(const timeval *timeout)
{
	reactor_impl_->handle_events(timeout);
}