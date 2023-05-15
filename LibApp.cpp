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

#include<fstream>
#include<iostream>
#include<string>
#include "LibApp.h"
#include"PublicationSelector.h"
#include"Book.h"
using namespace std;
namespace sdds
{

    LibApp::LibApp(const char* fileName) : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_pubMenu("Choose the type of publication:")
    {
        Utils::strCpy(m_pubFileName, fileName, Utils::strLen(fileName));
        m_changed = false;
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_pubMenu << "Book" << "Publication";
        load();
    }
    LibApp::~LibApp()
    {
        for (int i = 0; i < SDDS_LIBRARY_CAPACITY; i++)
            delete m_publications[i];
    }
    bool LibApp::confirm(const char* message)
    {
        Menu menuTitle(message);
        bool isOne;
        menuTitle << "Yes";
        isOne = menuTitle.run() == 1 ? true : false;
        return isOne;
    }

    void LibApp::load()
    {
        int i;
        char type{};
        cout << "Loading Data" << endl;
        ifstream fromFile("LibRecs.txt");
        for (i = 0; fromFile && i < SDDS_LIBRARY_CAPACITY; i++)
        {
            fromFile >> type;
            fromFile.ignore();
            if (fromFile)
            {
                if (type == 'P')
                    m_publications[i] = new Publication();
                else if (type == 'B')
                    m_publications[i] = new Book();

                if (m_publications[i])
                {
                    fromFile >> *m_publications[i];
                    m_nPubs++;
                }
            }

        }
        m_lastRefnNo = (*m_publications[i - 2]).getRef();
    }

    void LibApp::save()
    {
        cout << "Saving Data" << endl;
        ofstream outfile("LibRecs.txt");
        for (int i = 0; i < m_nPubs; i++)
        {
            if ((*m_publications[i]).getRef())
                outfile << *m_publications[i] << endl;
        }
    }

    int LibApp::search(int searchDecider)
    {

        char pubtitle[256];
        int  selection = m_pubMenu.run(), lib_ref = 0;
        char type = '\0';
        bool matchThere = false;
        PublicationSelector* ps{};
        if (selection == 1)
            type = 'B';
        else if (selection == 2)
            type = 'P';

        if (type && selection)
        {
            cout << "Publication Title: ";
            cin.ignore();
            cin.getline(pubtitle, 256);

            ps = new PublicationSelector("Select one of the following found matches:");


            if (searchDecider == 0)
            {
                for (int i = 0; i < m_nPubs; i++)
                {
                    if (m_publications[i]->getRef() && type == m_publications[i]->type() && m_publications[i]->onLoan() == false && m_publications[i]->operator==(pubtitle))
                    {
                        *ps << m_publications[i];
                        matchThere = true;
                    }
                }
            }
            else if (searchDecider == 1)
            {
                for (int i = 0; i < m_nPubs; i++)
                {
                    if (m_publications[i]->getRef() && type == m_publications[i]->type() && m_publications[i]->onLoan() && m_publications[i]->operator==(pubtitle))
                    {
                        *ps << m_publications[i];
                        matchThere = true;
                    }
                }
            }
            else if (searchDecider == 4)
            {
                for (int i = 0; i < m_nPubs; i++)
                {
                    if (m_publications[i]->getRef() && type == m_publications[i]->type() && m_publications[i]->operator==(pubtitle))
                    {
                        *ps << m_publications[i];
                        matchThere = true;
                    }
                }
            }

            if (ps && matchThere)
            {
                ps->sort();
                lib_ref = ps->run();
            }
            else
            {
                cout << "No matches found!" << endl;
            }

        }
        if (lib_ref == 0 || type == 0 || !selection)
        {
            cout << "Aborted!" << endl;
        }
        delete ps;
        return lib_ref;
    }

    Publication* LibApp::getPub(int libRef)
    {
        bool refMatched = false;
        int i, indexFound;
        for (i = 0; i < m_nPubs && !refMatched; i++)
        {
            if (m_publications[i]->getRef() == libRef)
            {
                refMatched = true;
                indexFound = i;
            }
        }
        return refMatched ? m_publications[indexFound] : nullptr;
    }


    void LibApp::returnPub()
    {
        bool isReturned;
        Publication* pub{};
        Date date{};
        int days, cents = 50;
        double penalty;
        cout << "Return publication to the library" << endl;
        int lib_ref = search(1);
        if (lib_ref)
        {


            pub = getPub(lib_ref);
            if (pub)
            {
                pub->write(cout);
                cout << endl;
            }
            isReturned = confirm("Return Publication?");

            if (isReturned)
            {
                days = (date - pub->checkoutDate());
                if (days > 15)
                {
                    days = days - 15;
                    penalty = (double)days * (double)cents;
                    penalty = penalty / 100;
                    cout << "Please pay $";
                    cout.setf(ios::fixed);
                    cout.precision(2);
                    cout << penalty;
                    cout.unsetf(ios::fixed);
                    cout.precision(6);
                    cout << " penalty for being " << days << " days late!" << endl;
                }
                pub->set(0);
                m_changed = true;
                cout << "Publication returned" << endl;
            }
        }

    }
    void LibApp::newPublication()
    {
        bool isPublicationAdded;
        int selection = 0;
        Book* book{};
        Publication* publication{};
        if (m_nPubs == SDDS_LIBRARY_CAPACITY)
            cout << "Library is at its maximum capacity!" << endl;

        else
        {
            cout << "Adding new publication to the library" << endl;
            selection = m_pubMenu.run();

            if (selection == 1)
            {
                book = new Book();
                book->read(cin);
            }
            else if (selection == 2)
            {
                publication = new Publication();
                publication->read(cin);
            }
            else if (selection)
            {
                isPublicationAdded = confirm("Add this publication to the library?");
                if (isPublicationAdded)
                {
                    if (publication || book)
                    {
                        if (publication)
                        {
                            publication->setRef(++m_lastRefnNo);
                            m_publications[m_nPubs] = publication;
                            m_nPubs++;
                        }
                        else if (book)
                        {
                            book->setRef(++m_lastRefnNo);
                            m_publications[m_nPubs] = book;
                            m_nPubs++;
                        }
                        m_changed = true;
                        cout << "Publication added" << endl;
                    }
                    else
                    {
                        cout << "Failed to add publication!";
                        if (publication)
                            delete book;
                        else if (book)
                            delete publication;
                    }
                }

            }
            else
                cout << "Aborted!" << endl;


        }
    }
    void LibApp::removePublication()
    {
        bool isPublicationRemoved;
        Publication* pub{};
        cout << "Removing publication from the library" << endl;
        int lib_ref = search(4);
        pub = getPub(lib_ref);
        if (pub)
        {
            pub->write(cout);
            cout << endl;
        }
        if (lib_ref)
        {
            isPublicationRemoved = confirm("Remove this publication from the library?");
            if (isPublicationRemoved)
            {
                pub->setRef(0);
                m_changed = true;
                cout << "Publication removed" << endl;
            }
        }
    }

    void LibApp::checkOutPub()
    {
        bool publicationCheckedOut, ok;
        Publication* pub{};
        cout << "Checkout publication from the library" << endl;

        int lib_ref = search(0), memNo = 0;
        if (lib_ref)
        {
            pub = getPub(lib_ref);
            if (pub)
            {
                pub->write(cout);
                cout << endl;
            }
            publicationCheckedOut = confirm("Check out publication?");
            if (publicationCheckedOut)
            {
                cout << "Enter Membership number: ";
                do
                {
                    ok = true;
                    cin >> memNo;
                    if (!cin || memNo > 99999)
                    {
                        ok = false;
                        std::cout << "Invalid membership number, try again: ";
                    }
                } while (!ok);
                pub = getPub(lib_ref);
                if (pub)
                {
                    pub->set(memNo);
                    m_changed = true;
                    cout << "Publication checked out" << endl;
                }
            }
        }
    }
    void LibApp::run()
    {
        unsigned int selectedOption;

        bool done = false;
        bool warningShown = false;
        do
        {
            selectedOption = m_mainMenu.run();
            if (selectedOption == 1)
            {
                newPublication();
            }
            else if (selectedOption == 2)
            {
                removePublication();
            }
            else if (selectedOption == 3)
            {
                checkOutPub();
            }
            else if (selectedOption == 4)
            {
                returnPub();
            }
            else
            {
                done = true;
                warningShown = true;
            }

            if (m_changed && warningShown)
            {
                selectedOption = m_exitMenu.run();

                if (selectedOption == 1)
                {
                    save();
                    done = true;
                }
                else if (selectedOption == 2)
                {
                    done = false;
                }
                else
                {
                    if (confirm("This will discard all the changes are you sure?"))
                    {
                        done = true;
                    }
                }
            }
            cout << endl;
        } while (!done);

        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }

}
