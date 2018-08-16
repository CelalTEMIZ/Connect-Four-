#ifndef CONNECTFOURDIAG_H
#define	CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

namespace CelalTemiz
{
    
    class ConnectFourDiag: public ConnectFourAbstract 
    {
        
        public:
           // Constructors
           ConnectFourDiag();
           ConnectFourDiag(int newWidth, int newHeight, char newGameSelect);
        private:
           virtual void user1Win();                 // User 1 winning state
           virtual void user2OrComputerWin();       // User 2 and Computer winning state 
        
    };
      
}

#endif	/* CONNECTFOURDIAG_H */

