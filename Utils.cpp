/*
Student Information
Final Project Milestone 3
Module : Util Module
Filename : Util.h
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include"Utils.h"
#include"Menu.h"
using namespace std;


namespace sdds
{
	const char* Utils::getCStringDynamically(std::istream& fromKeyboard, int memoryAllocated, char delimiter)
	{
		bool notoutOfMemory;
		int addedMemory = memoryAllocated;
		char* readLabel = new char[memoryAllocated];
		char* pointerPosition = readLabel;
		char* toBeReturned{};

		do
		{
			fromKeyboard.get(pointerPosition, memoryAllocated, delimiter);
			notoutOfMemory = false;
			if (fromKeyboard)
			{
				notoutOfMemory = true;
			}
			else
			{
				char* newLabel = new char[memoryAllocated + addedMemory];
				strcpy(newLabel, readLabel);
				delete[] readLabel;
				readLabel = newLabel;
				pointerPosition = &readLabel[strlen(readLabel)];
				addedMemory += memoryAllocated;
				fromKeyboard.clear();
			}
		} while (!notoutOfMemory);
		toBeReturned = new char[strlen(readLabel) + 1];
		if (toBeReturned)
		{
			strcpy(toBeReturned, readLabel);
		}
		delete[] readLabel;
		return toBeReturned;
	}

	int Utils::strLen(const char* cstr)
	{
		int i;
		for (i = 0; cstr[i]; i++);
		return i;
	}
	void Utils::strCpy(char* des, const char* src, int size)
	{
		int i;
		for (i = 0; src[i] && i < size; i++)
			des[i] = src[i];
		des[i] = '\0';
	}
	void Utils::delAlloCopy(char*& des, const char* src)
	{
		delete[] des;
		des = nullptr;
		if (src && src[0])
		{
			des = new char[strLen(src) + 1];
			strCpy(des, src, strLen(src) + 1);
		}
	}

	unsigned int Utils::getInt(int min, int nItems)
	{
		int inputNo;
		bool validate = false;
		do
		{
			cin >> inputNo;

			if (inputNo >= min && inputNo <= nItems && cin)
				validate = true;
			else if (validate == false || !cin)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Selection, try again: ";
			}

		} while (!validate);
		return (unsigned)inputNo;
	}

}