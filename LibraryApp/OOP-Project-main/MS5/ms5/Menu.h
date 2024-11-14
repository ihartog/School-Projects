#ifndef SENECA_MENU_H__
#define SENECA_MENU_H__
#include <iostream>
namespace seneca {
	const unsigned int MAX_MENU_ITEMS = 20;

	class Menu;

	class MenuItem {
		char* m_content;

		// Constructor
		MenuItem(const char* itemContent);

		// Desctructor
		~MenuItem();

		// Copy constructor
		MenuItem(const MenuItem&) = delete;

		// Assignment operator
		MenuItem& operator=(const MenuItem&) = delete;

		friend class Menu;
	};

	class Menu {
	private:
		MenuItem* m_title;
		MenuItem* m_items[MAX_MENU_ITEMS];
		int m_numItems;

		void displayTitle(std::ostream& os) const;

	public:
		Menu();
		Menu(const char* title);
		~Menu();

		void addItem(const char* itemContent);
		void display(std::ostream& os) const;

		unsigned int run() const;

		unsigned int operator~() const;
		Menu& operator<<(const char* menuitemContent);
		operator int() const;
		operator unsigned int() const;
		operator bool() const;
		const char* operator[](int index) const;

		friend std::ostream& operator<<(std::ostream& os, const Menu& menu);

	};
}
#endif