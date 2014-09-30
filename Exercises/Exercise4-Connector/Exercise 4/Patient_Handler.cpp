#include "stdafx.h"
#include "Patient_Handler.hpp"

void Patient_Handler::open()
{
	handle_event(get_handle(),Event_type::READ);
}

void Patient_Handler::handle_event(HANDLE h, Event_type eType)
{
	//Get data here
}

Patient_Handler::~Patient_Handler()
{}
