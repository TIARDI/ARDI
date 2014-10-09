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

void ConcreteReactor::deactivate_handle(HANDLE handle, Event_type eType)
{
	reactor_impl_->deactivate_handle(handle, eType);
}

void ConcreteReactor::reactivate_handle(HANDLE handle, Event_type eType)
{
	reactor_impl_->reactivate_handle(handle, eType);
}

void ConcreteReactor::handle_events(bool onlyOneEvent, const timeval *timeout)
{
	reactor_impl_->handle_events(onlyOneEvent, timeout);
}