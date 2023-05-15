#pragma once
/*
Student Information
Final Project Milestone 3
Module : Book Module
Filename : Book.h
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include "Publication.h"
namespace sdds
{
	class Book : public Publication
	{
		char* authorName{};
		void setAuthName();
	public:
		Book();
		Book(const Book& book);
		Book& operator=(const Book& book);
		~Book();
		char type()const;
		void set(int member_id);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
		operator bool()const;
	};
}
#endif