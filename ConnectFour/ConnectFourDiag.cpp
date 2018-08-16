#include <iostream>
#include "ConnectFourDiag.h"
#include "ConnectFourAbstract.h"

using std::cout;
using std::endl;

namespace CelalTemiz
{
 
  // No parameter constructor
  ConnectFourDiag::ConnectFourDiag():ConnectFourAbstract()
  {
      // Body Intentionally Empty
  }
  
  // Parameter Constructor will call base class constructor to creating object 
  ConnectFourDiag::ConnectFourDiag(int newWidth, int newHeight, char newGameSelect)
  :ConnectFourAbstract(newWidth,newHeight,newGameSelect)
  {  
      // Body Intentionally Empty
  }
 
 // User1 Winning State
 // Only accept diagonally connected cells as the goal of the game.
  void ConnectFourDiag::user1Win()
  {
    for(int i=0; i<getCurrentHeight(); ++i)
    {         
        for(int j=0; j<getCurrentWidth(); ++j)
        {     
            if(gameBoard[i][j].getCellState() == 1)
            {    
              // DIAGONAL LEFT TO RIGHT
                  if(i  < getCurrentHeight()- 3 && j<getCurrentWidth()-3)
                  {
                      if(gameBoard[i+1][j+1].getCellState() == 1 && gameBoard[i+2][j+2].getCellState() == 1 && gameBoard[i+3][j+3].getCellState() == 1)
                      {  
                       winner=true;
                       gameBoard[i][j].setCellState(6);
                       gameBoard[i+1][j+1].setCellState(6);
                       gameBoard[i+2][j+2].setCellState(6);
                       gameBoard[i+3][j+3].setCellState(6);
                       display();
                       cout <<"Game Over .." << endl;
                       cout <<"Winner --> User 1 (X)"<<endl;
                      }   
                  }
                  
                  // DIAGONAL RIGHT TO LEFT
                  if(i  < getCurrentHeight()- 3 && j - 3 >= 0 )
                  {
                    if(gameBoard[i+1][j-1].getCellState() == 1 && gameBoard[i+2][j-2].getCellState() == 1 && gameBoard[i+3][j-3].getCellState() == 1)
                    {
                       winner=true;
                       gameBoard[i][j].setCellState(6);
                       gameBoard[i+1][j-1].setCellState(6);
                       gameBoard[i+2][j-2].setCellState(6);
                       gameBoard[i+3][j-3].setCellState(6);
                       display();
                       cout <<"Game Over .." << endl;
                       cout <<"Winner --> User 1 (X)"<<endl;
                    } 
                  }      
            }
        }
    }
  }
 
 // User2 or Computer Winning State
 // Only accept diagonally connected cells as the goal of the game.  
  void ConnectFourDiag::user2OrComputerWin()
  {
      for(int i=0; i<getCurrentHeight(); ++i)
      {
        for(int j=0; j<getCurrentWidth(); ++j)
        {
            if(gameBoard[i][j].getCellState() == 2)
            {              
               // DIAGONAL LEFT TO RIGHT
                    if(i  < getCurrentHeight()- 3 && j<getCurrentWidth()-3)
                    {
                       if(gameBoard[i+1][j+1].getCellState() == 2 && gameBoard[i+2][j+2].getCellState() == 2 && gameBoard[i+3][j+3].getCellState() == 2)
                      {
                          winner2=true;
                          gameBoard[i][j].setCellState(7);
                          gameBoard[i+1][j+1].setCellState(7);
                          gameBoard[i+2][j+2].setCellState(7);
                          gameBoard[i+3][j+3].setCellState(7);
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
                  // DIAGONAL RIGHT TO LEFT
                  if(i  < getCurrentHeight()- 3 && j - 3 >= 0  )
                  {
                    if(gameBoard[i+1][j-1].getCellState() == 2 && gameBoard[i+2][j-2].getCellState() == 2 && gameBoard[i+3][j-3].getCellState() == 2)   
                    {
                         winner2=true;
                         gameBoard[i][j].setCellState(7);
                         gameBoard[i+1][j-1].setCellState(7);
                         gameBoard[i+2][j-2].setCellState(7);
                         gameBoard[i+3][j-3].setCellState(7);
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
