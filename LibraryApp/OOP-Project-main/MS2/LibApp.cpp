#include <iostream>
#include "LibApp.h"

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
        std::cout << "Loading Data" << std::endl;
    }

    void LibApp::save() {
        std::cout << "Saving Data" << std::endl;
    }

    void LibApp::search() {
        std::cout << "Searching for publication" << std::endl;
    }

    void LibApp::returnPub() {
        search();
        std::cout << "Returning publication" << std::endl;
        std::cout << "Publication returned" << std::endl << std::endl;
        m_changed = true;
    }

    // Methods with confirmation
    void LibApp::newPublication() {
        std::cout << "Adding new publication to library" << std::endl;
        if (confirm("Add this publication to library?")) {
            m_changed = true;
        std::cout << "Publication added" << std::endl;
        }
        else {
            std::cout << endl;
        }
    }
    void LibApp::removePublication() {
        std::cout << "Removing publication from library" << std::endl;
        search();
        if (confirm("Remove this publication from the library?")) {
            m_changed = true;
            std::cout << "Publication removed" << std::endl << std::endl;
        }
        else {
            std::cout << endl;
        }
    }
    void LibApp::checkOutPub() {
        search();
        if (confirm("Check out publication?")) {
            m_changed = true;
            std::cout << "Publication checked out" << std::endl << std::endl;
        }
        else {
            std::cout << endl;
        }
    }

    // Constructors
    LibApp::LibApp()
        : m_changed(false),
        m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?") {

        m_mainMenu << "Add New Publication"
            << "Remove Publication"
            << "Checkout publication from library"
            << "Return publication to library";

        m_exitMenu << "Save changes and exit"
            << "Cancel and go back to the main menu";

        load();
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
