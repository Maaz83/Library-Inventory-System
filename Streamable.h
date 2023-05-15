#pragma once
/*
Student Information
Final Project Milestone 3
Module : Streamable module
Filename : Streamable.h
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#ifndef STREAMABLE_SDDS_H
#define STREAMABLE_SDDS_H
#include<iostream>
namespace sdds
{
	class Streamable
	{
	public:
		virtual std::ostream& write(std::ostream& toScreen)const = 0;
		virtual std::istream& read(std::istream& fromKeyboard) = 0;
		virtual bool conIO(std::ios& IO)const = 0; // checks whether the object is of type istream or ostream and return if that is.
		virtual operator bool()const = 0;

		virtual ~Streamable();

	};
	std::ostream& operator<<(std::ostream& toScreen, const Streamable& Streamable);
	std::istream& operator>>(std::istream& fromKeyboard, Streamable& Streamable);

}
#endif