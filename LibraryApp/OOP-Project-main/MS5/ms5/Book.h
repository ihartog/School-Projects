#ifndef SENECA_BOOK_H__
#define SENECA_BOOK_H__

#include "Publication.h"

namespace seneca {

	class Book : public Publication {
		char* m_author;
		
	public:
		// Constructors
		Book();
		Book(const char* author);
		Book(const Book& copy);

		// Destructor
		~Book();

		// Assignment operator
		Book& operator=(const Book& other);

		// Virtual functions
		char type() const override;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& is);
		void set(int member_id);

		// Conversion operator
		operator bool() const;
	};
}
#endif