//
// Celal TEMIZ - 101044070
//
// CSE 241 - Object Oriented Programming - HW05
// ConnectFour Game Implementation
//
// Inheritance
// Polymorphism
// Abstract Class - Pure Virtual Functions
//

#include <iostream>
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

using namespace CelalTemiz;

int main(int argc, char** argv) 
{   

	char objectType = '\0';

	cout <<endl<<"Select Object Type :"<<endl;
	cout <<endl<< "P - Plus Object\nD - Diagonal Object\nU - Undo Object    > ";
	cin>>objectType;
    
  // If the object type is ConnectFourPlus,create a ConnectFourPlus object and then start the game.
	if(objectType == 'P')
	{
  	ConnectFourPlus cfPlusObject;
  	cfPlusObject.setObjectType('P'); 
  	cfPlusObject.playGame();
	}
	// If the object type is ConnectFourDiag,create a ConnectFourDiag object and then start the game.
  else if(objectType == 'D')
  {
  	ConnectFourDiag cfDiagObject;
  	cfDiagObject.setObjectType('D'); 
  	cfDiagObject.playGame();
  }
  // If the object type is ConnectFourPlusUndo,create a ConnectFourPlusUndo object and then start the game.  
  else if(objectType == 'U')
  {
  	ConnectFourPlusUndo cfPlusUndoObject;
	  cfPlusUndoObject.setObjectType('U'); 
	  cfPlusUndoObject.playGame();
  } 

  else
  	cerr << endl<< "Invalid Object Selection !"<<endl<<endl; 

    return 0;
}