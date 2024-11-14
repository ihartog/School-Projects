#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include "Menu.h"
#include "Publication.h"
#include "Lib.h"

namespace seneca {
   class LibApp {

       bool m_changed;
       Menu m_mainMenu;
       Menu m_exitMenu; 
       Menu m_pubTypeMenu;

       // MS5
       char m_filename[256];
       Publication* m_ppa[SENECA_LIBRARY_CAPACITY]; // Publication Pointers Array
       int m_nolp; // Number Of Loaded Publications 
       int m_llrn; // Last Library Reference Number
       

       // Private methods
       bool confirm(const char* message);
       
       // Simple private functions
       void load();  // prints: "Loading Data"
       void save() const;  // prints: "Saving Data"
       int search(bool onLoan, bool available);  // prints: "Searching for publication"
       void returnPub();
       Publication* getPub(int libRef);

       // Methods with confirmation
       void newPublication();
       void removePublication();
       void checkOutPub();

   public:
       // Constructors       
       LibApp(const char* filename);
       ~LibApp();
       void run();
   };
}
#endif // !SENECA_LIBAPP_H



