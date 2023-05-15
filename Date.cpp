// Final Project Milestone 1 
// Date Module
// File	Date.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2021/10/29		       Preliminary release
/////////////////////////////////////////////////////////////////

/*
Student Information
Final Project Milestone 1
Module : Date module
Filename : Date.cpp
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
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"


namespace sdds
{

    bool sdds_test = false;
    int sdds_year = 2021;
    int sdds_mon = 12;
    int sdds_day = 25;

    Date::Date() :m_CUR_YEAR(systemYear())
    {
        setToToday();
    }

    bool Date::validate()
    {
        errCode(NO_ERROR);
        if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1)
        {
            errCode(YEAR_ERROR);
        }
        else if (m_mon < 1 || m_mon > 12)
        {
            errCode(MON_ERROR);
        }
        else if (m_day < 1 || m_day > mdays())
        {
            errCode(DAY_ERROR);
        }
        return !bad();
    }
    int Date::mdays()const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
    }
    int Date::systemYear()const
    {
        int theYear = sdds_year;
        if (!sdds_test)
        {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            theYear = lt.tm_year + 1900;
        }
        return theYear;
    }
    void Date::setToToday()
    {
        if (sdds_test)
        {
            m_day = sdds_day;
            m_mon = sdds_mon;
            m_year = sdds_year;
        }
        else
        {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            m_day = lt.tm_mday;
            m_mon = lt.tm_mon + 1;
            m_year = lt.tm_year + 1900;
        }
        errCode(NO_ERROR);
    }
    int Date::daysSince0001_1_1()const
    { // Rata Die day since 0001/01/01 
        int ty = m_year;
        int tm = m_mon;
        if (tm < 3)
        {
            ty--;
            tm += 12;
        }
        return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
    }

    Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear())
    {
        m_year = year;
        m_mon = mon;
        m_day = day;
        validate();
    }
    const char* Date::dateStatus()const
    {
        return DATE_ERROR[errCode()];
    }
    int Date::currentYear()const
    {
        return m_CUR_YEAR;
    }
    std::istream& Date::read(std::istream& is)
    {
        errCode(NO_ERROR);
        is >> m_year;
        is.ignore();
        is >> m_mon;
        is.ignore();
        is >> m_day;

        if (!is)
        {
            errCode(CIN_FAILED);
            is.clear();
        }
        else
            validate();

        return is;
    }
    ostream& Date::write(ostream& os)const
    {
        if (!(*this))
        {
            os << dateStatus();
        }
        else
        {
            os << m_year << "/";
            os.width(2);
            os.fill('0');
            os << m_mon;
            os << "/";
            os.width(2);
            os << m_day;
            os.fill(' ');

        }
        return os;
    }
    bool operator==(const Date& leftDateObj, const Date& rightDateObj)
    {
        return leftDateObj.daysSince0001_1_1() == rightDateObj.daysSince0001_1_1();
    }
    bool operator!=(const Date& leftDateObj, const Date& rightDateObj)// are these be private
    {
        return leftDateObj.daysSince0001_1_1() != rightDateObj.daysSince0001_1_1();
    }
    bool operator>=(const Date& leftDateObj, const Date& rightDateObj)
    {
        return leftDateObj.daysSince0001_1_1() >= rightDateObj.daysSince0001_1_1();
    }
    bool operator<=(const Date& leftDateObj, const Date& rightDateObj)
    {
        return leftDateObj.daysSince0001_1_1() <= rightDateObj.daysSince0001_1_1();
    }
    bool operator<(const Date& leftDateObj, const Date& rightDateObj)
    {
        return leftDateObj.daysSince0001_1_1() < rightDateObj.daysSince0001_1_1();
    }
    bool operator>(const Date& leftDateObj, const Date& rightDateObj)
    {
        return leftDateObj.daysSince0001_1_1() > rightDateObj.daysSince0001_1_1();
    }
    Date::operator bool()const
    {
        bool result = false;
        if (m_ErrorCode == 0)
        {
            result = true;
        }
        return result;
    }
    void Date::errCode(int readErrorCode)
    {
        m_ErrorCode = readErrorCode;
    }
    int Date::errCode()const
    {
        return m_ErrorCode;
    }
    bool Date::bad()const
    {
        return m_ErrorCode != 0;
    }
    int operator-(const Date& leftDateObj, const Date& rightDateObj)
    {
        return leftDateObj.daysSince0001_1_1() - rightDateObj.daysSince0001_1_1();
    }

    ostream& operator<<(ostream& os, const Date& RO)
    {
        return RO.write(os);
    }
    istream& operator>>(istream& is, Date& RO)
    {
        return RO.read(is);
    }


}
