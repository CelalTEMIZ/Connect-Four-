#ifndef CONNECTFOURPLUSUNDO_H
#define	CONNECTFOURPLUSUNDO_H

#include "ConnectFourPlus.h"

namespace CelalTemiz
{
    
    class ConnectFourPlusUndo: public ConnectFourPlus 
    {
        
        public:
           ConnectFourPlusUndo();
           ConnectFourPlusUndo(int newWidth, int newHeight, char newGameSelect);
           void playGame();
        private:
           void load(string  inputFileName); 
           static int fileFlag;
           static int secondFileFlag; 
    };
  
}

#endif	/* CONNECTFOURPLUSUNDO_H */

