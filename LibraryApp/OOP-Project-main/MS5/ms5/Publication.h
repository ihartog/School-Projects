#ifndef PUBLICATION_H
#define PUBLICATION_H

#include "Streamable.h"
#include "Date.h"

namespace seneca {
	class Publication : public Streamable {
	private:
		char m_title[256];
		char m_shelfId[5];
		int m_membership;
		int m_libRef;
		Date m_date;
		
	public:
		// Const
		Publication();


		// Methods		
		void set(int member_id);		
		void setRef(int value);		
		void resetDate();

		// Queries
		virtual char type()const;
		const char* title() const;
		bool onLoan()const;
		Date checkoutDate()const;		
		bool operator==(const char* title)const;
		operator const char* ()const;
		int getRef()const;
		int getMemberID()const;
		

		// Streams 
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& is);

		explicit operator bool() const;
		bool conIO(const std::ios& io) const;
	};

}


#endif