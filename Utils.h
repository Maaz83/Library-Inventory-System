#pragma once
/*
Student Information
Final Project Milestone 3
Module : Util Module
Filename : Util.cpp
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
#include<iostream>
#include<cstring>

namespace sdds
{
	class Utils
	{
	public:
		static const char* getCStringDynamically(std::istream& fromKeyboard, int memoryAllocated, char delimiter);
		static int strLen(const char* cstr);
		static void strCpy(char* des, const char* src, int size);
		static void delAlloCopy(char*& des, const char* src);
		unsigned int getInt(int max, int min);

	};
}
#endif // !SDDS_UTILS_H
