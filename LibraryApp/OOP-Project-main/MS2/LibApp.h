#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include "Menu.h"

namespace seneca {
   class LibApp {

       bool m_changed;
       Menu m_mainMenu;
       Menu m_exitMenu;  

       // Private methods
       bool confirm(const char* message);
       
       // Simple private functions
       void load();  // prints: "Loading Data"
       void save();  // prints: "Saving Data"
       void search();  // prints: "Searching for publication"
       void returnPub();

       // Methods with confirmation
       void newPublication();
       void removePublication();
       void checkOutPub();

   public:
       // Constructors
       LibApp();
       void run();
   };
}
#endif // !SENECA_LIBAPP_H



