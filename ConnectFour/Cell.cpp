#include <iostream>
#include <cstdlib>
#include <ctime> 
#include "Cell.h"

using namespace std;

namespace CelalTemiz
{
  // No parameter constructor
  Cell::Cell()
  {
    cellPosition = ' ';
    rowPosition  =  0;
    cellState = 0;   
  }

  // Constructor that take cell position
  Cell::Cell(const char& newCellPosition)
  {
    cellPosition = newCellPosition;
    rowPosition = 0;
    cellState = 0;
  }

  // Constructor that take row position
  Cell::Cell(const int& newRowPosition)
  {
    cellPosition = ' ';
    rowPosition = newRowPosition;
    cellState = 0;
  }

  // Constructor that take cell position and row position
  Cell::Cell(const char& newCellPosition, const int& newRowPosition)
  {
    cellPosition = newCellPosition;
    rowPosition  =  newRowPosition;  
    cellState = 0;
  }

  // Constructor that take cell state,cell position and row position
  Cell::Cell(const int& newCellState,const char& newCellPosition, const int& newRowPosition)
  {
    cellState = newCellState;
    cellPosition = newCellPosition;
    rowPosition =  newRowPosition;  
  }

  // Set the cell position
  // If the cell position is out of range,it will warn the players
  void Cell::setCellPosition(const char& newCellPosition)
  {
    if(newCellPosition > 'Z')
    {
        cout << "Invalid position of the cell " << endl;
        exit(1);
    }
    else {
        cellPosition = newCellPosition;   
    }    
  }

  // Set the row position
  // If the row number is illegal,it will warn the players 
  void Cell::setRowPosition(const int& newRowPosition)
  {
    if(newRowPosition < 0)
    {
        cout << "Invalid Row Position " << endl;
        exit(1);
    }
    else
        rowPosition = newRowPosition;
  }

  // Set the player cell states
  // CellState
  // User1(X)=1,User2(O)=2,Computer(O)=3,Empty( )=4,Asteriks(*)=5
  // Little User1(x)=6
  // Little User2(o)=7
  void Cell::setCellState(const int& newCellState)
  {   
    cellState = newCellState;   
  }

  // Get Cell State
  int  Cell::getCellState() const
  {
    return cellState;    
  }

  // Set cell and row position
  void Cell::setAllPosition(const char& newCellPosition,const int& newRowPosition)
  {
    cellPosition =  newCellPosition;
    rowPosition  =  newRowPosition;  
  }

  // Get Cell Position
  char  Cell::getCellPosition() const
  {
    return cellPosition;      
  }

  // Get the row position
  int Cell::getRowPosition() const
  {
    return rowPosition;
  }

} // CelalTemiz