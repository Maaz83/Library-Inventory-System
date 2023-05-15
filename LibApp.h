#pragma once
/*
Final Project Milestone 1
Module : LibApp
Filename : LibApp.cpp
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include"Menu.h"
#include"Lib.h"
#include"Publication.h"
namespace sdds
{
	class LibApp
	{
		char m_pubFileName[256]{};
		Publication* m_publications[SDDS_LIBRARY_CAPACITY]{};
		int m_nPubs{};
		int m_lastRefnNo{};
		bool m_changed{};
		Menu m_mainMenu;
		Menu m_exitMenu;
		Menu m_pubMenu;
		bool confirm(const char* message);
		void load();
		void save();
		int search(int searchDecider);
		Publication* getPub(int libRef);
		void returnPub();
		void newPublication();
		void removePublication();
		void checkOutPub();
		void display()const;
	public:
		LibApp(const char* filename = "NoFile");
		~LibApp();
		void run();



	};
}
#endif // !SDDS_LIBAPP_H



