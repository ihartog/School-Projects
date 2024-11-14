#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
#include "Menu.h"
using namespace std;
namespace seneca {
	// Constructor
	MenuItem::MenuItem(const char* itemContent) {
		if (itemContent) {
			m_content = new char[strlen(itemContent) + 1];
			strcpy(m_content, itemContent);
		}
		else {
			m_content = nullptr;
		}
	}

	// Desctructor
	MenuItem::~MenuItem() {
		delete[] m_content;
	}
	Menu::Menu() {
		m_title = nullptr;
		m_numItems = 0;
		for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
			m_items[i] = nullptr;
		}
	}

	Menu::Menu(const char* title) {
		m_numItems = 0;
		m_title = title ? new MenuItem(title) : nullptr;
		for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
			m_items[i] = nullptr;
		}
	}

	Menu::~Menu() {
		delete m_title;
		for (int i = 0; i < m_numItems; i++) {
			delete m_items[i];
		}
	}

	void Menu::addItem(const char* itemContent) {
		if (m_numItems < static_cast<int>(MAX_MENU_ITEMS)) {
			m_items[m_numItems] = new MenuItem(itemContent);
			++m_numItems;
		}
		else {
			std::cerr << "Menu has reached its maximum capacity of " << MAX_MENU_ITEMS << " items." << endl;
		}
	}

	void Menu::displayTitle(std::ostream& os) const {
		if (m_title && m_title->m_content) {
			os << m_title->m_content;
		}
	}

	void Menu::display(std::ostream& os) const {
		if (m_title && m_title->m_content) {
			os << m_title->m_content << "\n";
		}
		for (int i = 0; i < m_numItems; i++) {
			if (m_items[i]->m_content) {
				os.width(2);
				os << (i + 1) << "- " << m_items[i]->m_content << endl;
			}
		}
		os << " 0- Exit" << endl << "> ";
	}

	unsigned int Menu::run() const {
		unsigned int selection;
		bool valid = false;

		// Display the menu once initially
		display(cout);

		do {

			cin >> selection;

			// Check if input is valid
			if (cin.fail() || selection > static_cast<unsigned int>(m_numItems)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				// Invalid input handling
				cout << "Invalid Selection, try again: ";

				// Prompt again immediately
				cin >> selection;
			}

			// Check if the second input is valid
			if (!cin.fail() && selection <= static_cast<unsigned int>(m_numItems)) {
				valid = true; // Exit the loop if selection is valid
			}

		} while (!valid);

		return selection;
	}

	unsigned int Menu::operator~() const {
		return run();
	}

	Menu& Menu::operator<<(const char* menuitemContent) {
		if (m_numItems < static_cast<int>(MAX_MENU_ITEMS)) {
			m_items[m_numItems] = new MenuItem(menuitemContent);
			++m_numItems;
		}
		return *this;
	}

	Menu::operator int() const {
		return m_numItems;
	}

	Menu::operator unsigned int() const {
		return static_cast<unsigned int>(m_numItems);
	}

	Menu::operator bool() const {
		return m_numItems > 0;
	}

	const char* Menu::operator[](int index) const {
		if (m_numItems == 0) {
			return nullptr;
		}
		return m_items[index % m_numItems]->m_content;
	}

	std::ostream& operator<<(std::ostream& os, const Menu& menu) {
		menu.displayTitle(os);
		return os;
	}

}