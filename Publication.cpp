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

#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include"Publication.h"
#include"Lib.h"
#include"Utils.h"
using namespace std;
namespace sdds
{
	Publication::Publication()
	{
	}

	Publication::Publication(const Publication& publication)
	{
		*this = publication;
	}

	Publication& Publication::operator=(const Publication& publication)
	{
		if (this != &publication)
		{
			m_membership = publication.m_membership;
			m_date = publication.m_date;
			m_libRef = publication.m_libRef;

			if (publication.m_shelfId[0] != 0 && publication.m_title && publication.m_title[0] != '\0')
			{
				delete[] m_title;
				strcpy(m_shelfId, publication.m_shelfId);
				m_title = new char[strlen(publication.m_title) + 1];
				strcpy(m_title, publication.m_title);
			}
		}
		else
			m_title = nullptr;
		return *this;
	}

	Publication::~Publication()
	{
		delete[] m_title;
		m_title = nullptr;
	}

	void Publication::set(int member_id)
	{
		if (member_id != 0)
			m_membership = member_id;
		else
			m_membership = 0;
	}

	void Publication::setRef(int value)
	{
		m_libRef = value;
	}

	void Publication::resetDate()
	{
		m_date = Date();
	}

	char Publication::type() const
	{
		return 'P';
	}

	bool Publication::onLoan() const
	{
		return m_membership != 0;
	}

	Date Publication::checkoutDate() const
	{
		return m_date;
	}

	bool Publication::operator==(const char* title) const
	{
		/*return (title && m_title) && (strstr(m_title, title) != nullptr);*/
		bool subStringExist = false;
		if (title && m_title)
		{
			subStringExist = (strstr(m_title, title) != nullptr);
		}
		return subStringExist;
	}
	void Publication::setToDefault()
	{
		delete[] m_title;
		m_title = nullptr;
		m_libRef = -1;
		m_membership = 0;
		m_shelfId[0] = 0;
		m_date = Date();
	}
	Publication::operator const char* () const
	{
		return m_title;
	}


	int Publication::getRef() const
	{
		return m_libRef;
	}
	bool Publication::conIO(ios& io)const
	{
		return (&io == &cin || &io == &cout);
	}


	ostream& Publication::write(ostream& os) const
	{
		if (conIO(os))
		{
			os << "| " << m_shelfId << " | ";
			os.setf(ios::left);
			if (Utils::strLen(m_title) > SDDS_TITLE_WIDTH)
			{
				int i;
				for (i = 0; i < SDDS_TITLE_WIDTH; i++)
					cout << m_title[i];
			}
			else if (Utils::strLen(m_title) <= SDDS_TITLE_WIDTH)
			{
				/*char temp[SDDS_AUTHOR_WIDTH + 1] = { '\0' };
				Utils::strCpy(temp, authorName, SDDS_AUTHOR_WIDTH + 1);
				if (temp[0])
					Utils::delAlloCopy(authorName, temp);*/
				os.width(SDDS_TITLE_WIDTH);
				os.fill('.');
				os << m_title;
			}

			os.unsetf(ios::left);
			os << " | ";
			if (m_membership != 0)
				os << m_membership;
			else
				os << " N/A ";
			os << " | " << m_date << " |";
		}
		else
			os << type() << '\t' << getRef() << '\t' << m_shelfId << '\t' << m_title << '\t' << m_membership << '\t' << checkoutDate();
		return os;
	}
	istream& Publication::read(istream& istr)
	{
		const char* title{};
		char shelfId[SDDS_SHELF_ID_LEN + 1]{};
		int membershipId = 0, libRef = -1;;
		Date date;
		setToDefault();

		if (conIO(istr))
		{
			istr.ignore();
			cout << "Shelf No: ";
			istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\n');
			if (strlen(shelfId) != (SDDS_SHELF_ID_LEN))
				istr.setstate(ios::failbit);
			cout << "Title: ";
			if (istr)
				title = Utils::getCStringDynamically(istr, 64, '\n');
			if (!title)
				istr.setstate(ios::failbit);
			cout << "Date: ";
			istr >> date;
		}
		else
		{
			istr >> libRef;
			istr.ignore();
			istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			if (istr)
				title = Utils::getCStringDynamically(istr, 64, '\t');
			istr >> membershipId;
			istr.ignore();
			istr >> date;
		}
		if (!date)
			istr.setstate(ios::failbit);

		if (istr)
		{
			if (title)
			{
				m_title = new char[strlen(title) + 1];
				strcpy(m_title, title);
			}
			strcpy(m_shelfId, shelfId);
			set(membershipId);
			m_date = date;
			setRef(libRef);
		}
		delete[] title;
		return istr;
	}
	Publication::operator bool()const
	{
		return  m_shelfId[0] != '\0' && m_title && m_title[0] != '\0';
	}

}