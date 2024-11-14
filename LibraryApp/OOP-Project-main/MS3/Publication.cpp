#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include <string>
#include "Publication.h"
#include "Lib.h"
#include "Date.h"

namespace seneca {
    // Default constructor sets all attributes to their default values
    Publication::Publication()
        : m_membership(0), m_libRef(-1), m_date(){
		m_title[0] = '\0';
		m_shelfId[0] = '\0';
	}

	// Sets the membership attribute to either zero or a five-digit integer.
	void Publication::set(int member_id) {
		m_membership = member_id;
	}
	// Sets the **libRef** attribute value
	void Publication::setRef(int value) {
		if (m_libRef == -1) {
			m_libRef = value;
		}
	}
	// Sets the date to the current date of the system.
	void Publication::resetDate() {		
		m_date = Date(seneca_year, seneca_mon, seneca_day);

	}

	// Queries
	//Returns the character 'P' to identify this object as a "Publication object"
	char Publication::type()const {
		return 'P';
	}
	//Returns true is the publication is checkout (membership is non-zero)
	bool Publication::onLoan()const {
		return m_membership != 0;
	}
	//Returns the date attribute
	Date Publication::checkoutDate()const {
		return m_date;
	}
	//Returns true if the argument title appears anywhere in the title of the 
   //publication. Otherwise, it returns false; (use strstr() function in <cstring>)
	bool Publication::operator==(const char* title)const {
		return (strstr(m_title, title) != nullptr);
	}
	//Returns the title attribute
	Publication::operator const char* ()const {
		return m_title;
	}
	//Returns the libRef attirbute.
	int Publication::getRef()const {
		return m_libRef;
	}

	// Streams
	std::ostream& Publication::write(std::ostream& os) const {
		if (conIO(os)) {
			os << "| " << m_shelfId << " | "
				<< std::setw(30) << std::left << std::setfill('.') << m_title << " | "
				<< (m_membership == 0 ? " N/A " : std::to_string(m_membership)) << " | "
				<< m_date << " |";
		}
		else {
			os << type() << '\t'
				<< m_libRef << '\t'
				<< m_shelfId << '\t'
				<< m_title << '\t'
				<< (m_membership == 0 ? "N/A" : std::to_string(m_membership)) << '\t'
				<< m_date;
		}
		return os;
	}

	std::istream& Publication::read(std::istream& istr) {
		// Temporary local variables
		char tempTitle[256];
		char tempShelfId[SENECA_SHELF_ID_LEN + 1];
		int tempLibRef = -1;
		int tempMembership = 0;
		Date tempDate;

		// Clear all attributes to their default values
		m_title[0] = '\0';
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;

		if (conIO(istr)) {
			// Console input
			std::cout << "Shelf No: ";
			istr.getline(tempShelfId, sizeof(tempShelfId));
			if (std::strlen(tempShelfId) != SENECA_SHELF_ID_LEN) {				
				istr.setstate(std::ios::failbit);			
				std::cout << "Title: ";
				std::cout << "Date: ";								
			}
			else {
				std::cout << "Title: ";
				istr.getline(tempTitle, sizeof(tempTitle));
				if (istr.fail()) {	
					istr.setstate(std::ios::failbit);
					std::cout << "Date: ";					
				}
				else {
					std::cout << "Date: ";
					istr >> tempDate;
					if (!tempDate) {
						istr.setstate(std::ios::failbit);						
					}					
				}
			}			
		}
		else {
			// File input
			istr >> tempLibRef;
			istr.ignore();
			istr.getline(tempShelfId, sizeof(tempShelfId), '\t');
			if (std::strlen(tempShelfId) != SENECA_SHELF_ID_LEN) {
				istr.setstate(std::ios::failbit);
			}
			else {
				istr.getline(tempTitle, sizeof(tempTitle), '\t');
				istr >> tempMembership;
				istr.ignore();
				istr >> tempDate;
				if (!tempDate) {
					istr.setstate(std::ios::failbit);
				}
				
			}
		}

		if (istr) {
			std::strncpy(m_title, tempTitle, sizeof(m_title) - 1);
			m_title[sizeof(m_title) - 1] = '\0';

			std::strncpy(m_shelfId, tempShelfId, SENECA_SHELF_ID_LEN + 1);
			m_shelfId[SENECA_SHELF_ID_LEN] = '\0';

			m_membership = tempMembership;
			m_date = tempDate;
			m_libRef = tempLibRef;
		}

		return istr;
	}



	Publication::operator bool() const {
		return m_title[0] != '\0' && m_shelfId[0] != '\0';
	}

	bool Publication::conIO(const std::ios& io) const {
		return &io == &std::cin || &io == &std::cout;
	}


}