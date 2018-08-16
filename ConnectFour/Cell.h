#ifndef CELL_H
#define	CELL_H

namespace CelalTemiz 
{
    
    class Cell {

        public:
            //Constructors to Cell Class
            Cell();
            Cell(const char& newCellPosition);
            Cell(const int& newRowPosition);
            Cell(const char& newCellPosition,const int& newRowPosition);
            Cell(const int& newCellState,const char& newCellPosition,const int& newRowPosition);

       
            // Mutator Functions - Setters
            void  setAllPosition(const char& newCellPosition,const int& newRowPosition);
            void  setCellPosition(const char& newCellPosition);
            void  setRowPosition(const int& newRowPosition);
            void  setCellState(const int& newCellState);

            // Accessor Functions - Getters
            char  getCellPosition() const;
            int   getRowPosition() const;
            int   getCellState() const;
            
        protected:
            char cellPosition;
            int  rowPosition;
            int  cellState; 
            // CellState
            // User1(X)=1,User2(O)=2,Computer(O)=3,Empty( )=4,Asteriks(*)=5
            // Little User1(x)=6
            // Little User2(o)=7

    };

} //CelalTemiz 



#endif	/* CELL_H */

