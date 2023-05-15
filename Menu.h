#pragma once
/*
Final Project Milestone 1
Module : Menu module
Filename : Menu.h
Version 1.0
Name	Maaz Saiyed
Revision History
Date - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include<iostream>
#include "Utils.h"
namespace sdds
{
    class Menu;
    const unsigned int MAX_MENU_ITEMS = 20;

    class MenuItem
    {
        char* menuItem{};
        MenuItem();
        MenuItem(const char* menuItm);
        void setSafeEmpty();
        MenuItem(const MenuItem& menuItm) = delete;
        MenuItem& operator=(const MenuItem& menuItm) = delete;
        ~MenuItem();
        operator bool() const;
        operator const char* ()const;
        void display();
        friend class Menu;

    };

    class Menu
    {
        MenuItem menuTitle;
        MenuItem* menuItems[MAX_MENU_ITEMS]{}; // stores the adderss of MenuItem dynamically
        int noOfItems = 0;
    public:
        std::ostream& displayMenu(std::ostream& ostr = std::cout) const;
        Menu();
        Menu(const char* mTitle);
        Menu(const Menu& menu) = delete;
        Menu& operator=(const Menu& menu) = delete;
        unsigned int run()const;
        unsigned int operator~()const;
        operator int()const;
        operator unsigned int()const;
        operator bool()const;
        Menu& operator<<(const char* menuitemConent);
        const char* operator[](int index)const;
        void displayTitle(std::ostream& ostr = std::cout)const;
        const char* returnTitle()const;
        ~Menu();
    };
    std::ostream& operator<<(std::ostream& ostrLO, const Menu& menu);

}
#endif
