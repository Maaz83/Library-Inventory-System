/*
Student Information
Final Project Milestone 3
Module : Book Module
Filename : Book.cpp
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/
#include "Book.h"
#include "Utils.h"
#include"Lib.h"
using namespace std;

namespace sdds
{
	Book::Book()
	{
	}
	Book::Book(const Book& book)
	{
		*this = book;
	}
	Book& Book::operator=(const Book& book)
	{
		Publication::operator=(book);
		if (this != &book)
		{
			Utils::delAlloCopy(authorName, book.authorName);
		}
		else
			authorName = nullptr;
		return *this;
	}
	Book::~Book()
	{
		delete[] authorName;
	}
	char Book::type() const
	{
		return 'B';
	}
	void Book::set(int member_id)
	{
		Publication::set(member_id);
		Publication::resetDate();
	}

	void Book::setAuthName()
	{
		delete[] authorName;
		authorName = nullptr;
	}
	Book::operator bool()const
	{
		return Publication::operator bool() && authorName && authorName[0];
	}
	std::ostream& Book::write(std::ostream& ostr) const
	{
		Publication::write(ostr);
		if (conIO(ostr))
		{
			ostr << " ";
			ostr.setf(ios::left);
			if (Utils::strLen(authorName) > SDDS_AUTHOR_WIDTH)
			{
				int i;
				for (i = 0; i < SDDS_AUTHOR_WIDTH; i++)
					ostr << authorName[i];
			}
			else if (Utils::strLen(authorName) <= SDDS_AUTHOR_WIDTH)
			{
				ostr.width(SDDS_AUTHOR_WIDTH);
				ostr << authorName;
			}
			ostr.unsetf(ios::left);
			ostr << " |";

		}
		else
			ostr << "\t" << authorName;
		return ostr;
	}
	std::istream& Book::read(std::istream& istr)
	{
		const char* lAuthorName = nullptr;
		Publication::read(istr);
		setAuthName();

		if (conIO(istr))
		{
			istr.ignore(1000, '\n');
			cout << "Author: ";
			if (istr)
				lAuthorName = Utils::getCStringDynamically(istr, 264, '\n');

		}
		else
		{
			if (istr)
			{
				istr.ignore();
				lAuthorName = Utils::getCStringDynamically(istr, 264, '\n');
			}
		}

		if (!lAuthorName)
			istr.setstate(ios::failbit);

		if (istr)
		{
			if (lAuthorName)
			{
				int size = Utils::strLen(lAuthorName) + 1;
				authorName = new char[size];
				Utils::strCpy(authorName, lAuthorName, size);
			}
		}
		delete[] lAuthorName;
		return istr;
	}
}