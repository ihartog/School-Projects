#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Streamable.h"


namespace seneca {
  
    std::ostream& operator<<(std::ostream& os, const Streamable& obj) {
        if (static_cast<bool>(obj)) {
            return obj.write(os);
        }
        else {
            return os;
        }
    }
    std::istream& operator>>(std::istream& is, Streamable& obj) {
        return obj.read(is);
    }
}