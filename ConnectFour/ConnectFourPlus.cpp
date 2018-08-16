#include <iostream>
#include "ConnectFourPlus.h"
#include "ConnectFourAbstract.h"

using std::cout;
using std::endl;

namespace CelalTemiz
{
   // No parameter constructor
  ConnectFourPlus::ConnectFourPlus():ConnectFourAbstract()
  {
       // Body Intentionally Empty
  }
  
  // Constructor that take game features and will call base class constructor to creating an object
  ConnectFourPlus::ConnectFourPlus(int newWidth, int newHeight, char newGameSelect)
  :ConnectFourAbstract(newWidth,newHeight,newGameSelect)
  {  
       // Body Intentionally Empty
  }
 
  // User 1 Winning State
  // Only accept horizontally or vertically connected cells as the goal of the game.
  void ConnectFourPlus::user1Win()
  {
    for(int i=0; i<getCurrentHeight(); ++i)
    {         
        for(int j=0; j<getCurrentWidth(); ++j)
        {     
            if(gameBoard[i][j].getCellState() == 1)
            {    
              // UP TO DOWN - HORIZONTALLY
              if(i+3<getCurrentHeight())
              {
                 if(gameBoard[i+1][j].getCellState() == 1 && gameBoard[i+2][j].getCellState() == 1 && gameBoard[i+3][j].getCellState() == 1)  
                 {
                    winner=true;
                    gameBoard[i][j].setCellState(6);
                    gameBoard[i+1][j].setCellState(6);
                    gameBoard[i+2][j].setCellState(6);
                    gameBoard[i+3][j].setCellState(6);
                    display();
                    cout <<"Game Over .." << endl;
                    cout <<"Winner --> User 1 (X)"<<endl;  
                  }
              }
              // LEFT TO RIGHT - VERTICALLY
              if(j + 3 <getCurrentWidth())
              { 
                if(gameBoard[i][j+1].getCellState() == 1 && gameBoard[i][j+2].getCellState() == 1 && gameBoard[i][j+3].getCellState() == 1)
                { 
                   winner=true;
                   gameBoard[i][j].setCellState(6);
                   gameBoard[i][j+1].setCellState(6);
                   gameBoard[i][j+2].setCellState(6);
                   gameBoard[i][j+3].setCellState(6);
                   display();
                   cout <<"Game Over .." << endl;
                   cout <<"Winner --> User 1 (X)"<<endl;
                }
              }
            }
        }
    }
  }
  
  // User 2 or Computer Winning State
  // Only accept horizontally or vertically connected cells as the goal of the game.   
  void ConnectFourPlus::user2OrComputerWin()
  {
      for(int i=0; i<getCurrentHeight(); ++i)
      {
        for(int j=0; j<getCurrentWidth(); ++j)
        {
          if(gameBoard[i][j].getCellState() == 2)
          {   
            // UP TO DOWN - HORIZONTALLY
            if(i+3<getCurrentHeight())
            {
              if(gameBoard[i+1][j].getCellState() == 2 && gameBoard[i+2][j].getCellState() == 2 && gameBoard[i+3][j].getCellState() == 2)  
              {
                winner2=true;
                gameBoard[i][j].setCellState(7);
                gameBoard[i+1][j].setCellState(7);
                gameBoard[i+2][j].setCellState(7);
                gameBoard[i+3][j].setCellState(7);
                display();
                if(getGameSelection() == 'P')
                {
                  cout <<"Game Over .." << endl;
                  cout <<"Winner --> User 2 (O)"<<endl;   
                }
                if(getGameSelection() == 'C') 
                {
                  cout <<"Game Over .." << endl;
                  cout <<"Winner --> Computer (O)" << endl;    
                }
              }
            }

            // LEFT TO RIGHT - VERTICALLY
            if(j+ 3 < getCurrentWidth())
            {
             if(gameBoard[i][j+1].getCellState() == 2 && gameBoard[i][j+2].getCellState() == 2 && gameBoard[i][j+3].getCellState() == 2) 
             {
                winner2=true;
                gameBoard[i][j].setCellState(7);
                gameBoard[i][j+1].setCellState(7);
                gameBoard[i][j+2].setCellState(7);
                gameBoard[i][j+3].setCellState(7);
                display();
                if(getGameSelection() == 'P')
                {
                  cout <<"Game Over .." << endl;
                  cout <<"Winner --> User 2 (O)"<<endl;   
                }
                if(getGameSelection() == 'C') 
                {
                  cout <<"Game Over .." << endl;
                  cout <<"Winner --> Computer (O)" << endl;  
                }
             }
            }
          }
        }
      }    
  }

}//CelalTemiz
