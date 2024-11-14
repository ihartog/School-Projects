#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Publication.h"
#include "PublicationSelector.h"
#include "LibApp.h"
#include "Book.h"
using namespace std;
namespace seneca {
    // Private methods
	bool LibApp::confirm(const char* message) {
		Menu menu(message);
        menu << "Yes";
		return menu.run() == 1;
	}

    // Simple private functions
    void LibApp::load() {
        std::ifstream infile(m_filename);
        if (!infile) {
            std::cerr << "Error: could not open file " << m_filename << " for reading." << std::endl;
            return;
        }

        std::cout << "Loading Data" << std::endl;
        char type;
        while (infile >> type) {
            infile.ignore(); // Ignore the tab after the type
            Publication* pub = nullptr;
            if (type == 'B') {
                pub = new Book;
            }
            else if (type == 'P') {
                pub = new Publication;
            }
            if (pub) {
                pub->read(infile);
                if (infile) {
                    m_ppa[m_nolp++] = pub;
                }
                else {
                    delete pub;
                }
            }
        }

        if (m_nolp > 0) {
            m_llrn = m_ppa[m_nolp - 1]->getRef();
        }
    }

    void LibApp::save() const {
        std::cout << "Saving Data" << std::endl;
        std::ofstream ofs(m_filename);
        if (!ofs) {
            std::cerr << "Error: could not open file " << m_filename << " for writing." << std::endl;
            return;
        }

        for (int i = 0; i < m_nolp; ++i) {
            if (m_ppa[i]->getRef() != 0) {
                m_ppa[i]->write(ofs);
            }
        }
    }

    int LibApp::search(bool onLoan, bool available) {
        // Get the type of publication from the user
        int pubType = m_pubTypeMenu.run();
        if (pubType == 0) {
            std::cout << "Operation cancelled." << std::endl;
            return 0; // Exit if the user cancels
        }

        char typeChar = (pubType == 1) ? 'B' : 'P'; // 1 for Book, 2 for Publication

        // Prompt the user for the publication title
        char inputTitle[256] = { 0 };
        std::cin.ignore(1000, '\n'); // Clear input buffer
        std::cout << "Publication Title: ";
        std::cin.getline(inputTitle, 256);

        PublicationSelector selector("Select one of the following found matches:", 15);

        // Search for publications matching the title and type
        for (int i = 0; i < m_nolp; ++i) {
            if (m_ppa[i]->getRef() != 0) {  // Ensure the publication is not deleted
                bool matchesType = m_ppa[i]->type() == typeChar;
                bool matchesTitle = strstr(m_ppa[i]->title(), inputTitle) != nullptr;

                if (matchesType && matchesTitle) {
                    bool matchesStatus = (onLoan && m_ppa[i]->onLoan()) || (available && !m_ppa[i]->onLoan());

                    if (matchesStatus || (!onLoan && !available)) {
                        selector << m_ppa[i];
                    }
                }
            }
        }

        if (selector) {
            selector.sort();
            int ref = selector.run();
            if (ref > 0) {
                // Get the selected publication and print its details
                Publication* pub = getPub(ref);
                if (pub != nullptr) {
                    std::cout << *pub << std::endl;  // Display the full details of the selected publication
                }
                return ref;
            }
            else {
                std::cout << "Aborted!" << std::endl << std::endl;
                return 0;
            }
        }
        else {
            std::cout << "No matches found!" << std::endl;
            return 0;
        }
    }

    
    // return the address of a Publication object in the PPA that has the library reference number matching the "libRef" argument
    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < m_nolp; i++) {
            if (m_ppa[i]->getRef() == libRef) {
                return m_ppa[i];
            }
        }
        return nullptr;
    }

    // Methods with confirmation
    void LibApp::newPublication() {
        if (m_nolp >= SENECA_LIBRARY_CAPACITY) {
            std::cout << "Library is at its maximum capacity!" << std::endl << std::endl;
            return;
        }

        std::cout << "Adding new publication to the library" << std::endl;

        int pubType = m_pubTypeMenu.run();
        Publication* newPub = nullptr;

        if (pubType == 1) {
            newPub = new Book;
        }
        else if (pubType == 2) {
            newPub = new Publication;
        }

        if (newPub == nullptr) {
            std::cout << "Aborted!" << std::endl << std::endl;
            return;
        }

        if (!(newPub->read(std::cin))) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Aborted!" << std::endl << std::endl;
            delete newPub;
            return;
        }

        if (!confirm("Add this publication to the library?")) {
            std::cout << "Aborted!" << std::endl;
            delete newPub;
            return;
        }

        bool isValid = newPub->title() != nullptr && newPub->title()[0] != '\0';

        if (isValid) {
            m_llrn++;
            newPub->setRef(m_llrn);
            m_ppa[m_nolp++] = newPub;
            m_changed = true;
            std::cout << "Publication added" << std::endl << std::endl;
        }
        else {
            std::cout << "Failed to add publication!" << std::endl;
            delete newPub;
        }
    }
    void LibApp::removePublication() {
        std::cout << "Removing publication from the library" << std::endl;

        // Get the type of publication from the user first
        int pubType = m_pubTypeMenu.run();
        char typeChar = (pubType == 1) ? 'B' : 'P'; // 1 for Book, 2 for Publication

        // Then prompt for the publication title        
        char inputTitle[256] = { 0 };
        std::cin.ignore(1000, '\n');
        std::cout << "Publication Title: ";
        std::cin.getline(inputTitle, 256);

        PublicationSelector selector("Select one of the following found matches:", 15);

        for (int i = 0; i < m_nolp; ++i) {
            if (m_ppa[i]->getRef() != 0) {  // Ensure the publication is not deleted
                bool matchesType = m_ppa[i]->type() == typeChar;
                bool matchesTitle = strstr(m_ppa[i]->title(), inputTitle) != nullptr;

                if (matchesType && matchesTitle) {
                    selector << m_ppa[i];
                }
            }
        }

        if (selector) {
            selector.sort();
            int ref = selector.run();
            if (ref > 0) {
                Publication* pub = getPub(ref);
                if (pub) {
                    // Output the full details of the selected publication
                    std::cout << *pub << std::endl;  // Using the overloaded << operator

                    if (confirm("Remove this publication from the library?")) {
                        // Find the publication in the array and remove it
                        for (int i = 0; i < m_nolp; ++i) {
                            if (m_ppa[i] == pub) {
                                delete m_ppa[i]; // Free the memory
                                // Shift remaining elements left by one position
                                for (int j = i; j < m_nolp - 1; ++j) {
                                    m_ppa[j] = m_ppa[j + 1];
                                }
                                m_ppa[m_nolp - 1] = nullptr; // Optional: clear last pointer
                                --m_nolp; // Decrease the number of publications
                                break;
                            }
                        }
                        m_changed = true;
                        std::cout << "Publication removed" << std::endl << std::endl;
                    }
                }
            }
            else {
                std::cout << "Aborted!" << std::endl << std::endl;
            }
        }
        else {
            std::cout << "No matches found!" << std::endl;
        }
    }


    void LibApp::checkOutPub() {
        std::cout << "Checkout publication from the library" << std::endl;

        // First, prompt the user to select the type of publication
        int pubType = m_pubTypeMenu.run();

        // Ensure the input is correctly processed before moving on
        if (pubType == 0) {
            std::cout << "Operation cancelled." << std::endl;
            return; // Exit if the user cancels
        }

        char typeChar = (pubType == 1) ? 'B' : 'P'; // Determine the type (1 for Book, 2 for Publication)

        // Now, prompt the user to enter the title of the publication
        std::cin.ignore(1000, '\n'); // Clear any newline left in the buffer
        char inputTitle[256] = { 0 };
        std::cout << "Publication Title: ";
        std::cin.getline(inputTitle, 256);

        PublicationSelector selector("Select one of the following found matches:", 15);

        // Search for publications matching the title and type
        for (int i = 0; i < m_nolp; ++i) {
            if (m_ppa[i]->getRef() != 0 && m_ppa[i]->type() == typeChar && m_ppa[i]->getMemberID() == 0) {  // Ensure the publication is not deleted and matches the type
                if (strstr(m_ppa[i]->title(), inputTitle) != nullptr) {  // Check if the title contains the search string
                    selector << m_ppa[i];
                }
            }
        }

        // Handle the selection or absence of matches
        if (selector) {
            selector.sort();
            int ref = selector.run();
            if (ref > 0) {
                Publication* pub = getPub(ref);
                if (pub != nullptr) {
                    std::cout << *pub << std::endl;  // Display the full details of the selected publication

                    if (confirm("Check out publication?")) {
                        int membershipNumber;
                        bool valid = false;

                        // Prompt for the membership number once before the loop
                        std::cout << "Enter Membership number: ";

                        do {
                            std::cin >> membershipNumber;

                            // Validate the membership number is a 5-digit integer
                            if (std::cin.fail() || membershipNumber < 10000 || membershipNumber > 99999) {
                                std::cin.clear();  // Clear the error flag on cin
                                std::cin.ignore(1000, '\n');  // Ignore the rest of the input
                                std::cout << "Invalid membership number, try again: ";
                            }
                            else {
                                valid = true;
                            }
                        } while (!valid);

                        if (pub->type() == 'B') {
                            pub->resetDate();
                        }
                        // Set the membership number on the publication
                        pub->set(membershipNumber);
                        m_changed = true;
                        std::cout << "Publication checked out" << std::endl << std::endl;
                    }
                }
            }
            else {
                std::cout << "Aborted!" << std::endl;
            }
        }
        else {
            std::cout << "No matches found!" << std::endl << std::endl;
        }
    }
    void LibApp::returnPub() {       
        std::cout << "Return publication to the library" << std::endl;
        int ref = search(true, false);

        if (ref > 0) {
            if (confirm("Return Publication?")) {
                Publication* pub = getPub(ref);
                if (pub != nullptr) {
                    Date today;
                    int daysOnLoan = today - pub->checkoutDate();

                    if (daysOnLoan > 15) {
                        int lateDays = daysOnLoan - 15;
                        double penalty = lateDays * 0.50;
                        std::cout << std::fixed << std::setprecision(2);
                        std::cout << "Please pay $" << penalty << " penalty for being " << lateDays << " days late!" << std::endl;
                    }

                    if (pub->type() == 'B') {
                        pub->resetDate();
                    }
                    
                    pub->set(0);
                    m_changed = true;
                    std::cout << "Publication returned" << std::endl << std::endl;
                }
                else {
                    std::cout << "Publication not found!" << std::endl;
                }
            }
            else {
                std::cout << "Aborted!" << std::endl;
            }
        }      
    }

    // Constructors
    LibApp::LibApp(const char* filename)
        : m_changed(false),
        m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?"),
        m_pubTypeMenu("Choose the type of publication:"),
        m_nolp(0),
        m_llrn(0) {

        strncpy(m_filename, filename, sizeof(m_filename) - 1);
        m_filename[sizeof(m_filename) - 1] = '\0';

        m_mainMenu << "Add New Publication"
            << "Remove Publication"
            << "Checkout publication from library"
            << "Return publication to library";

        m_exitMenu << "Save changes and exit" 
            << "Cancel and go back to the main menu";

        m_pubTypeMenu << "Book" 
            << "Publication";

        // Initialize PPA to nullptr
        for (int i = 0; i < SENECA_LIBRARY_CAPACITY; ++i) {
            m_ppa[i] = nullptr;
        }

        load();
    }

    LibApp::~LibApp() {
        for (int i = 0; i < m_nolp; ++i) {
            delete m_ppa[i];
        }
    }    
    
    // Driver
    void LibApp::run() {
        bool done = false;
        while (!done) {
            switch (m_mainMenu.run()) {
            case 1:
                newPublication();
                break;
            case 2:
                removePublication();
                break;
            case 3:
                checkOutPub();
                break;
            case 4:
                returnPub();
                break;
            case 0:
                if (m_changed) {
                    switch (m_exitMenu.run()) {
                    case 1:
                        save();
                        done = true;
                        break;
                    case 0:
                        if (confirm("This will discard all the changes are you sure?")) {
                            done = true;
                        }
                        break;
                    case 2:
                        std::cout << "\n";
                    }
                }
                else {
                    done = true;
                }
                break;
            }
        }
        std::cout << "\n-------------------------------------------\n";
        std::cout << "Thanks for using Seneca Library Application\n";
    }

    
}
