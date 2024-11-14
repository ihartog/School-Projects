#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>

#include "Book.h"
#include "Lib.h"
#include "Date.h"
#include "Streamable.h"

using namespace std;
namespace seneca {
	// Constructors
	Book::Book() : m_author(nullptr) {}

	Book::Book(const char* author) : m_author(nullptr) {
		if (author) {
			m_author = new char[strlen(author) + 1];
			std::strcpy(m_author, author);
		}
	}

	Book::Book(const Book& copy) : Publication(copy), m_author(nullptr) {
		if (copy.m_author) {
			m_author = new char[std::strlen(copy.m_author) + 1];
			std::strcpy(m_author, copy.m_author);
		}
		else {
			m_author = nullptr;
		}
	}

	// Destructor
	Book::~Book() {
		delete[] m_author;
	}

	// Operator
	Book& Book::operator=(const Book& other) {
		if (this != &other) {
			Publication::operator=(other); // Call base class assignment operator
			delete[] m_author;

			if (other.m_author) {
				m_author = new char[std::strlen(other.m_author) + 1];
				std::strcpy(m_author, other.m_author);
			}
			else {
				m_author = nullptr;
			}
		}
		return *this;
	}

	// Virtual functions
	char Book::type() const {
		return 'B';
	}

	std::ostream& Book::write(std::ostream& os) const {
		Publication::write(os);
		if (!conIO(os)) {
			os << '\t' << (m_author ? m_author : "") << '\n';
		}
		else {
			os << " ";
			if (m_author && strlen(m_author) > SENECA_AUTHOR_WIDTH) {
				os.write(m_author, SENECA_AUTHOR_WIDTH);
			}
			else {
				os << std::setw(SENECA_AUTHOR_WIDTH) << std::left << std::setfill(' ') << (m_author ? m_author : "");
			}
			os << " |";
		}
		return os;
	}

	std::istream& Book::read(std::istream& is) {			
		delete[] m_author;
		m_author = nullptr;
		Publication::read(is);

		char tempAuthor[256];		

		if (conIO(is)) {
			// Console input
			
			std::cout << "Author: ";
			is.getline(tempAuthor, sizeof(tempAuthor));
		}
		else {
			// File input
			is.ignore();  // Ignore leftover whitespace
			is.get(tempAuthor, sizeof(tempAuthor));
		}

		if (is) {
			m_author = new char[strlen(tempAuthor) + 1];
			strcpy(m_author, tempAuthor);
		}
		
		return is;
	}

	void Book::set(int member_id) {
		Publication::set(member_id);
		resetDate();
	}

	// Conversion operator
	Book::operator bool() const {
		return m_author && m_author[0] != '\0' && Publication::operator bool();
	}


}