#pragma once
/*
Student Information
Final Project Milestone 3
Module : Publication Module
Filename : Publication.h
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H
#include"Streamable.h"
#include"Lib.h"
#include"Date.h"
namespace sdds
{

	class Publication : public Streamable
	{
		char* m_title{};
		char m_shelfId[SDDS_SHELF_ID_LEN + 1]{ };
		int m_membership{};
		int m_libRef{ -1 };
		Date m_date;
	public:
		Publication();
		Publication(const Publication& publication);
		Publication& operator=(const Publication& publication);
		~Publication();
		// Setters
		virtual void set(int member_id);
		void setRef(int value);
		void resetDate();
		void setToDefault();
		// Accessors
		virtual char type()const;
		bool onLoan()const;
		Date checkoutDate()const;
		bool operator==(const char* title)const;
		operator const char* ()const;
		int getRef()const;
		bool conIO(std::ios& IO)const;
		std::ostream& write(std::ostream& os)const;
		std::istream& read(std::istream& istr);
		operator bool()const;
	};
}
#endif