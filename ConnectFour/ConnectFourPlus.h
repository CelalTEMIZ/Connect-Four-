#ifndef CONNECTFOURPLUS_H
#define	CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

namespace CelalTemiz
{
    
    class ConnectFourPlus: public ConnectFourAbstract 
    {
        
        public:
           //Constructors
           ConnectFourPlus();
           ConnectFourPlus(int newWidth, int newHeight, char newGameSelect);
        protected:
           virtual void user1Win();                 // User 1 winning state
           virtual void user2OrComputerWin();       // User 2 and Computer winning state 
        
    };
  
}

#endif	/* CONNECTFOURPLUS_H */

