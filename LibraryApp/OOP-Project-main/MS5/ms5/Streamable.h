#ifndef SENECA_STREAMABLE_H__
#define SENECA_STREAMABLE_H__
#include <iostream>

namespace seneca {

	class Streamable {
	public:
		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream&) = 0;
		virtual ~Streamable() = default;

		virtual operator bool() const = 0;

		virtual bool conIO(const std::ios& io) const = 0;
	};
	
	std::ostream& operator<<(std::ostream& os, const Streamable& obj);
	std::istream& operator>>(std::istream& is, Streamable& obj);
}


#endif