/*
Final Project Milestone 1
Module : Menu module
Filename : Menu.cpp
Version 1.0
Author	Maaz Saiyed
Revision History
---------------------------------------------------------- -
Reason - For storing menu items and menu information like menu name
Date when made - 10-11-2021
Date when updated - 08-12-2021
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------- -
*/

#define _CRT_SECURE_NO_WARNINGS
#include"Menu.h"
#include"Utils.h"
using namespace std;
namespace sdds
{
	MenuItem::MenuItem()
	{
		setSafeEmpty();
	}
	MenuItem::MenuItem(const char* menuItm)
	{
		if (menuItm && menuItm[0])
		{
			menuItem = new char[strlen(menuItm) + 1];
			strcpy(menuItem, menuItm);
		}
		else
		{
			setSafeEmpty();
		}
	}
	void MenuItem::setSafeEmpty()
	{
		menuItem = nullptr;
	}
	MenuItem::~MenuItem()
	{
		delete[] menuItem;
		menuItem = nullptr;
	}
	MenuItem::operator bool()const
	{
		return menuItem != nullptr && menuItem[0] != '\0';
	}

	MenuItem::operator const char* ()const
	{
		return menuItem;
	}
	void MenuItem::display()
	{
		if (menuItem && menuItem[0])
		{
			cout << menuItem;
		}
	}
	Menu::Menu()
	{
		noOfItems = 0;
	}
	Menu::Menu(const char* mTitle)
	{
		if (mTitle && mTitle[0])
		{
			menuTitle.menuItem = new char[strlen(mTitle) + 1];
			strcpy(menuTitle.menuItem, mTitle);
		}
	}
	Menu::~Menu()
	{
		for (int i = 0; i < noOfItems; i++)
		{
			delete menuItems[i];
			menuItems[i] = nullptr;
		}
	}

	void Menu::displayTitle(ostream& ostr)const
	{
		if (menuTitle && menuTitle[0])
		{
			ostr << menuTitle.menuItem << endl;
		}
	}

	ostream& Menu::displayMenu(ostream& ostr)const
	{
		if (menuTitle && menuTitle[0])
		{
			displayTitle(ostr);
		}
		for (int i = 0; i < noOfItems; i++)
		{
			cout.width(2);
			cout.setf(ios::right);
			cout << (i + 1);
			cout << "- " << menuItems[i]->menuItem << endl;
		}
		cout << " 0- Exit" << endl << "> ";


		return ostr;

	}

	unsigned int Menu::run()const
	{
		Utils util;
		int inputNo;
		displayMenu();
		inputNo = util.getInt(0, noOfItems);
		return inputNo;
	}

	unsigned int Menu::operator~()const
	{
		int fromRun;
		fromRun = run();
		return fromRun;
	}

	Menu& Menu::operator<<(const char* menuitemConent)
	{
		if ((unsigned)noOfItems < MAX_MENU_ITEMS)
		{
			MenuItem* menuItem = new MenuItem(menuitemConent);
			menuItems[noOfItems] = menuItem;
			noOfItems++;
		}
		return *this;
	}
	Menu::operator int()const
	{
		return noOfItems;
	}
	Menu::operator unsigned int()const
	{
		return noOfItems;
	}
	Menu::operator bool()const
	{
		return noOfItems > 0;
	}
	const char* Menu::returnTitle()const
	{
		return menuTitle.menuItem;
	}
	ostream& operator<<(ostream& ostr, const Menu& menu)
	{
		menu.displayTitle(ostr);
		return ostr;
	}
	const char* Menu::operator[](int index)const
	{
		int result;
		bool indexValid = false;
		result = index > noOfItems ? index - noOfItems : index;
		do
		{
			if (result < noOfItems)
			{
				indexValid = true;
			}
			else
			{
				result = result - noOfItems;
			}
		} while (!indexValid);

		return menuItems[result]->menuItem;
	}

}