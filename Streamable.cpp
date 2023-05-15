/*
Student Information
Final Project Milestone 3
Module : Streamable module
Filename : Streamable.cpp
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#include "Streamable.h"


namespace sdds
{
	Streamable::~Streamable()
	{
	}
	std::ostream& Streamable::write(std::ostream& toScreen)const
	{
		return toScreen;
	}

	std::istream& Streamable::read(std::istream& fromKeyboard)
	{
		return fromKeyboard;
	}
	bool Streamable::conIO(std::ios& IO)const
	{
		return true;
	}

	std::ostream& operator<<(std::ostream& toScreen, const Streamable& streamable)
	{
		if (streamable)
		{
			streamable.write(toScreen);
		}
		return toScreen;
	}
	std::istream& operator>>(std::istream& fromKeyboard, Streamable& streamable)
	{
		streamable.read(fromKeyboard);
		return fromKeyboard;
	}
}
