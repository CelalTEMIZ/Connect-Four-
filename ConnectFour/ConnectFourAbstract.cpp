#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime> 

#include "ConnectFourAbstract.h"
#include "Cell.h"

using namespace std;

namespace CelalTemiz
{   
    
     // Static member initializations
    int ConnectFourAbstract::livingCellAll=0;
    int ConnectFourAbstract::livingCellUser1=0;
    int ConnectFourAbstract::livingCellUser2=0;
    int ConnectFourAbstract::livingCellInFile=0;
    int ConnectFourAbstract::order=0;
    bool ConnectFourAbstract::winner=false;
    bool ConnectFourAbstract::winner2=false;
    
    
    // No parameter constructor
    ConnectFourAbstract::ConnectFourAbstract():currentWidth(30),currentHeight(30)
    {
       
        gameBoard = new Cell*[getCurrentHeight()]; // Row number  
        for(int i=0; i<getCurrentHeight(); ++i)
            gameBoard[i] = new Cell[getCurrentWidth()];   // Column Number 
    }
       
    ConnectFourAbstract::ConnectFourAbstract(int newCurrentWidth, int newCurrentHeight,char newgameSelection)
    :currentWidth(newCurrentWidth),currentHeight(newCurrentHeight),gameSelection(newgameSelection)
    { 
     
        gameBoard = new Cell*[getCurrentHeight()]; // Row number  
        for(int i=0; i<getCurrentHeight(); ++i)
            gameBoard[i] = new Cell[getCurrentWidth()];   // Column Number
      
    }
     
  
    ConnectFourAbstract::~ConnectFourAbstract()
    {
       for(int i=0; i<getCurrentHeight(); ++i)
          delete [] gameBoard[i];

        delete [] gameBoard;
        gameBoard = NULL;  
    }
  
    // Board Initializaton
    void ConnectFourAbstract::initialBoard()
    {      
        for(int i=0; i<getCurrentHeight(); ++i)
        {
            for(int j=0; j<getCurrentWidth(); ++j)
            {   
               gameBoard[i][j].setCellState(5);     
            }
        } 
    }
    // Set current game width
    void ConnectFourAbstract::setCurrentWidth(int newCurrentWidth)
    {           
        if(newCurrentWidth < 4 || newCurrentWidth>30 )
        {
                cerr <<endl << "Invalid Game Board Width !!" << endl;
                exit(1);
        }
        else
        {
                currentWidth = newCurrentWidth;
        }
    }
    // Set current game height
    void ConnectFourAbstract::setCurrentHeight(int newCurrentHeight)
    {    
        if(newCurrentHeight < 4)
        {
            cerr << endl << "Invalid Game Board Height !!" << endl;
            exit(1);
        }
        else 
        {
            currentHeight = newCurrentHeight;    
        }
    }

    // Set game object type
    void ConnectFourAbstract::setObjectType(char newObjectType)
    {   
       if(newObjectType =='P' || newObjectType == 'D' || newObjectType == 'U' ) 
       {
           objectType = newObjectType;
       }else{
           cerr << endl << "Object type must be P or D or U " << endl;
           exit(1);
       }
    }
       
    // Set the current game selection 
    void ConnectFourAbstract::setGameSelection(char newGameSelection)
    {
         
       if(newGameSelection == 'P' || newGameSelection == 'C')
       {
           gameSelection= newGameSelection;
       }
       else
       {
           cerr << endl << "Game selection must be P or C " << endl;
           exit(1);
       }     
     }

     // Get the current game object type
    char ConnectFourAbstract::getObjectType() const
    {
        return objectType;   
    }
   
    // Get the current game selection
    char ConnectFourAbstract::getGameSelection() const 
    {
        return gameSelection;   
    }

    // Get the current game board width - row number
    int ConnectFourAbstract::getCurrentWidth() const 
    {
        return currentWidth;  
    }

    // Get the current game board height - column number
    int ConnectFourAbstract::getCurrentHeight() const
    {
        return currentHeight;
    }
      
    
  // Load command function
  void ConnectFourAbstract::load(string  inputFileName)
  {

    int  flag=1;
    ifstream fin;
    fin.open(inputFileName,ios::in | ios::binary);
   
    if(fin.fail())
    {
      cerr << "Input file opening failed" << endl;
      exit(1);
    }
      
    // Read object type P, D or U from the saved file

      char nextInputChar;
      
      while(flag==1){
            fin.get(nextInputChar);
            if(nextInputChar == 'P' || nextInputChar == 'D' || nextInputChar == 'U'){
                    setObjectType(nextInputChar);
                    flag=0;
            }
      }

     
      // Read new board width and heightfrom the saved file
      int boardWidth=0,boardHeight=0;
      fin >> boardWidth >> boardHeight;

      livingCellInFile=0;

      // Set new board parameters and resize new game
      setCurrentWidth(boardWidth);
      setCurrentHeight(boardHeight);
      resizeNewBoard(getCurrentWidth(),getCurrentHeight());
      initialBoard();
      
      // This array holds the user input characters 
      char * charArray = new char [getCurrentWidth()*getCurrentHeight()];               

      flag=1;
      while(flag==1){
          fin.get(nextInputChar);
          if(nextInputChar == 'P' || nextInputChar == 'C'){
                setGameSelection(nextInputChar);
                  flag=0;
          }
      }
      
     // Read user inputs to load command and save the array
      int i=0,availableInputNumber=0;
      char letter = 'A';

      while(!fin.eof()) 
      {
        nextInputChar = fin.get();       
        // Check available characters in text file
        if(nextInputChar != '\n' && nextInputChar !='\0' && nextInputChar >='A' && nextInputChar<='Z')
        {     
          if(nextInputChar >='A' && nextInputChar<(getCurrentWidth()+'A'))
          { 
            //cout << nextInputChar << endl;
            charArray[i] = nextInputChar;  
            ++i;
            ++availableInputNumber;
            ++livingCellInFile;
          }
        }      
      }                    
        
      int tempOrder=order;
     // Put available chars to game board 
      if(availableInputNumber != 0)  
      {
        for(int i=0; i<availableInputNumber; ++i)
        {
          if(i%2==0)
          {
            order = 0;
            movement(letterToBoardPosition(charArray[i]));
          }
          else
          {
            order = 1;
            movement(letterToBoardPosition(charArray[i]));
          }
         }   
      }

      order = tempOrder;

      fin.close();   
  }

  // Create new board to new input file
  void ConnectFourAbstract::resizeNewBoard(int rowNumber, int columnNumber)
  {   
      gameBoard = new Cell*[getCurrentHeight()]; // Row number
      
      for(int i=0; i<getCurrentHeight(); ++i)
          gameBoard[i] = new Cell[getCurrentWidth()];   // Column Number  
  }

  // Convert the input file characters to int values.
  int ConnectFourAbstract::letterToBoardPosition(char& inputData)
  {
      char letter = 'A';  
      int  intValue=0;

      for(intValue=0,letter='A'; letter<='Z'; ++letter,++intValue) 
              if(letter == inputData)
                      return intValue;  
  }

  // Display board situation during the game
  // CellState
  // User1(X)=1,User2(O)=2,Computer(O)=3,Empty( )=4,Asteriks(*)=5
  // Little User1(x)=6
  // Little User2(o)=7
  void  ConnectFourAbstract::display() const
  { 
           
    char boardCharacter = 'A';  
    
    cout << endl;
    
    for(int i = 0; i<getCurrentWidth(); i++)
          cout << " " <<static_cast<char>(boardCharacter + i) << " " ;
      cout << "\n";
                         
      int j=0;

      for(int i=0; i<getCurrentHeight(); ++i)
      {
          if(j==getCurrentWidth())
                  cout << endl;

              for(j=0; j<getCurrentWidth(); ++j){
                                                                      // Every integer number is equal to game character
                      if(gameBoard[i][j].getCellState() == 1)     
                              cout << " " << "X" << " ";
                      else if (gameBoard[i][j].getCellState() == 2) 
                              cout << " " << "O" << " ";
                      else if (gameBoard[i][j].getCellState() == 3)
                              cout << " " << "O" << " ";
                      else if (gameBoard[i][j].getCellState() == 4)
                              cout << " " << " " << " ";
                      else if(gameBoard[i][j].getCellState() ==  5)
                              cout << " " << "*" << " ";
                      else if(gameBoard[i][j].getCellState() ==  6)
                              cout << " " << "x" << " ";
                      else if(gameBoard[i][j].getCellState() ==  7)
                              cout << " " << "o" << " ";
                      else
                              cout << " " << " " << " ";
                  }
    }
    cout << endl;  
  }

  // Prompt the user to input data
  void ConnectFourAbstract::printBoardStepRange() const
  {
      char boardCharacter = 'A';  
      for(int i = 0; i<getCurrentWidth(); i++)
         cout << static_cast<char>(boardCharacter + i) << "." ;  
  }

  // String parse to load and save commands
  string ConnectFourAbstract:: partition(string userInput, int& index)
  {
      
    int i=0,firstCharPosition = index;
    string token = "";

      i = firstCharPosition;
      int inputSize = userInput.length();
      while(i<=inputSize){
        if (userInput[i] == ' ' || userInput[i] == '\0' || userInput[i] == '\t') {
              token = userInput.substr(firstCharPosition, i - index);
              index = i;
              break;
          }
          ++i;
      }

      while(index <= inputSize && (token == " " || token == "\0" || token == "\t")) {
          index++;
          return partition(userInput, index);
      }

      return token;  
      
  }

  // Is the cell is live ?
  bool ConnectFourAbstract::isLivingUser1Cells(Cell cell)
  { 
   // User 1 = 1
      for(int i=0;i<getCurrentHeight(); ++i)
      {  
          for(int j=0; j<getCurrentWidth(); ++j )
              
          if(gameBoard[i][j].getCellState() == 1 && cell.getCellState() == 1)
          {
              return true;
          }
      }
      return false;
  }
  // Is the cell is live ?
  bool ConnectFourAbstract::isLivingUser2Cells(Cell cell)
  {  
      // User 2 = 2
      for(int i=0;i<getCurrentHeight(); ++i)
      {  
          for(int j=0; j<getCurrentWidth(); ++j )
              
          if(gameBoard[i][j].getCellState() == 2 && cell.getCellState() == 2)
          {
              return true;
          }
      }   
      return false;
  }

  // Put the step characters to game board
  // User1(X)=1,User2(O)=2,Computer(O)=3,Empty( )=4,Asteriks(*)=5
  // Little User1(x)=6
  // Little User2(o)=7
  bool ConnectFourAbstract::movement(int yPosition)
  {      

    bool inputState = true;

      for(int i=getCurrentHeight()-1; i>=0; --i)
      {
          if(gameBoard[i][yPosition].getCellState() == 5) // If the cell is asteriks,put the game cell 
          {  
            // User 1 movement paramaters set the game board
            if(order==0)
            {
               gameBoard[i][yPosition].setCellPosition(yPosition+'A');                     
               gameBoard[i][yPosition].setRowPosition(i);
               gameBoard[i][yPosition].setCellState(1);
               ++livingCellAll;
               inputState = true;     // If the movement is valid, it will return true
               break;
            }
            else
            {  
               // User 2 and Computer movement paramaters set the game board
               gameBoard[i][yPosition].setCellPosition(yPosition+'A');  
               gameBoard[i][yPosition].setRowPosition(i);
               gameBoard[i][yPosition].setCellState(2);
               ++livingCellAll;
               inputState = true;
               break; 
            }
            
         }  

         // Check the available board positions
         // If the movement is İnvalid, it will return false
        else if(gameBoard[i][yPosition].getCellState() == 4 || 
                      (gameBoard[0][yPosition].getCellState() == 1 || gameBoard[0][yPosition].getCellState() == 2))
          {
            cerr << endl<< endl << "> Column is full.Invalid Step !!!"<<endl<<endl;
            inputState = false;
            break;
          }
    
      }  
      
      return inputState;      
  }

  // Smart computer move
  // The character will put left to right
  void ConnectFourAbstract::computerSmartMove()
  {
    bool flag = false;
    char computerStepChar='A';
    int i=0,j=0;

    for(i=getCurrentHeight()-1; (i>=0) && !flag; --i)
      for(j=0; (j<getCurrentWidth()) && !flag; ++j)
        if(gameBoard[i][j].getCellState() == 5){
          gameBoard[i][j].setCellState(2);
          flag = true;
        }

    ++livingCellAll;
    cout << endl << "Smart Computer (O) Movement: ";
    cout << static_cast<char>(computerStepChar + (j-1)) << endl ;
  }

  // Multiple mode play function to user 1
  void ConnectFourAbstract::play(char& cellPosition)
  {

    char letter = 'A';  
    int  intValue=0; 

  // Check the input data
    // If it is fail, re-enter new step
    if(cellPosition >'A'+(getCurrentWidth()-1) || !(cellPosition>='A' && cellPosition<='Z'))
    {
      char repeatChar='\0';
      while(1){
          cerr << endl << "> Wrong character.Invalid Step !" << endl;
          cout << endl << "Re-Enter Movement: ";
          cin >> repeatChar;
          if(repeatChar<'A'+getCurrentWidth() && (repeatChar>='A' && repeatChar<='Z') ){
              cellPosition = repeatChar;
              break; 
          }        
      }   
    }

  // Check the input data
  // If it is fail, re-enter new step
   if(isLivingUser1Cells(Cell(cellPosition,0))|| isLivingUser2Cells(Cell(cellPosition,0)))
   {
      char repeatChar='\0';
      while(1){
          cerr << endl << "> Column is full.Invalid Step !" << endl;
          cout << endl << "Re-Enter Movement: ";
          cin >> repeatChar;
          
          if(!isLivingUser1Cells(Cell(repeatChar,0)) && !isLivingUser2Cells(Cell(repeatChar,0))){
              cellPosition = repeatChar;
              break; 
          }        
      }    
   }  
    
   
    // If the cell is dead,put the step.
    // If the cell is live,re-enter new step 
    if(!isLivingUser1Cells(Cell(cellPosition,0)) && !isLivingUser2Cells(Cell(cellPosition,0)))
    {    
      // User 1 state  
        if (order==0)
        {
              for(intValue=0,letter='A'; letter<='Z'; ++letter, ++intValue) 
              {
                  if(letter == cellPosition)
                  {
                    // Fail user 1 step
                    if(movement(intValue) == false) 
                    {
                        while(1)
                        {
                          cout << "Re-Enter Movement: ";
                          char reStep;
                          cin >> reStep;

                          // Success user 1 step 
                          if((movement(letterToBoardPosition(reStep))) == true)
                          {
                            order=0;
                            break;
                          }
                        }
                    }
                    // Success user 1 step
                    ++livingCellUser1;
                    display();
                    user1Win(); 
                    order=1;
                    if(gameEnded())
                         cout<<endl<<endl<<"Board Filled !"<<endl<<endl;
                    return ; 
                  }
              }  
        } 
        
        // User 2 state
        if(order==1 && getGameSelection()=='P') {
            for(intValue=0,letter='A'; letter<='Z'; ++letter, ++intValue) 
              {
                  if(letter == cellPosition)
                  {              
                    order=1;
                    
                    // Fail user 2 step
                    if(movement(intValue) == false) 
                    {
                          while(1)
                          {
                            cout << "Re-Enter Movement: ";
                            char reStep;
                            cin >> reStep;

                            // Success user 2 step
                            if((movement(letterToBoardPosition(reStep))) == true)
                            {
                              order=0;
                              break;
                            }
                          }
                      
                    }

                    // Success user 2 step
                    ++livingCellUser2;
                    display();
                    user2OrComputerWin(); 
                    order=0;
                    if(gameEnded())
                         cout<<endl<<endl<<"Board Filled !"<<endl<<endl;
                    return ;
                  }
              } 
        }   
    } 
  }

  // Multiple mode computer step
  // If the any step is fail,it will make smart move in this way
  void ConnectFourAbstract::play()
  {
    // Random computer step
    int computerStep= (rand() % getCurrentWidth());
    order=1;

    if(movement(computerStep) == false) 
    {
      computerSmartMove();
      order=0;
      ++livingCellUser2;
      display();                     
      user2OrComputerWin(); 
    } 
    else 
    {
      order=0;
      ++livingCellUser2; 
      cout << endl << "Computer Step : " << static_cast<char>(computerStep+'A') << endl << endl;
      display();                    
      user2OrComputerWin(); 
    }                 
  }
  // Save the current game inputs to the given file
  void ConnectFourAbstract::save(string outputFileName, char* userInputs, int& numberOfUserInputs)
  {
      
      ofstream fout;

      fout.open(outputFileName);

      if(fout.fail()) {
              cerr << "Output file opening failed" << endl;
              exit(1);
      }
    
      // Write to file some input file parameters
      fout  << getObjectType() << endl;
      fout  << getCurrentWidth() << endl;
      fout  << getCurrentHeight() << endl;

      if(getGameSelection()=='P')
              fout <<'P'<<endl;
      else 
              fout <<'C'<< endl;
      
      // Write user inputs to given file
      for(int i=0; i<numberOfUserInputs; ++i)  
        fout << userInputs[i]<<endl;

      fout.close();  

      cout << endl << "> The current game status is written to "<< outputFileName << " file." <<endl<<endl;     
  }


  // When the given any input file, compute row and column number
  void ConnectFourAbstract::resizeBoard(string gameFile, int& rowNumber, int& columnNumber)
  {
    int characters=0; 
    ifstream fin;
    fin.open(gameFile);

    if(fin.fail()) {
      cerr << "Input file opening failed" << endl;
      exit(1);
   }

    char nextChar;
    int row=0,column=0;

    while(!fin.eof())
    {
      // COmpute the max column number
      if(nextChar != '\n' && fin.peek() != fin.eof())
      {
        ++characters;
      }
      if(characters > columnNumber)
        column = characters;

      // COmpute the Row number
      if(nextChar == '\n'){
        characters=0;
        ++row; 
      }
      nextChar = fin.get();
    }

    rowNumber = row;
    columnNumber = column;
     
    // Set current game parameters
    setCurrentHeight(rowNumber);               // Row Number
    setCurrentWidth(columnNumber);            // Column Number
        
    fin.close();
  }


// Get the game features
void ConnectFourAbstract::getData()
{  
    char playerOrComputer='\0';
    int width=0,height=0;

    cout << endl << "Enter Board Width : ";
    cin >> width;
    
    setCurrentWidth(width);

    cout << endl << "Enter Board Height: ";
    cin >> height;
    
    setCurrentHeight(height);

    cout <<endl << "Player(P) | Computer(C): ";
    cin >> playerOrComputer;
    
    setGameSelection(playerOrComputer);
    
}

  // Single step play function to users and computer
  void ConnectFourAbstract::playGame()
  {
   
      int lastPosition=0;
      char choice;
      
      string step="",command="";
      string alphabetOrder = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      // Get board width,height and game selection
      getData();

      cin.ignore(1000, '\n'); 
      cout<<endl;     

      initialBoard();
      
      // Collect the user inputs from the keyboard
      char *userInputs = new char [getCurrentHeight()*getCurrentWidth()];
      int  count =0;
        
      while(winner==false && winner2==false)
      {         
          cout << endl;
          display();
          cout << endl << "> Enter the 'LOAD yourTextFile' command to load the new game." << endl;
          cout << "> Enter the 'SAVE yourTextFile' command to save the current game." << endl;
          cout << "> Continue the game use positions such as ";
          
          printBoardStepRange();

          if(order==0)
            cout << endl << endl << "User 1 (X) Movement : ";
          else
            cout << endl << endl << "User 2 (O) Movement : ";
          
          getline(cin,step);  // Get the user step  
          
           if(step.length() == 0) 
           {
            cerr << endl<< "User Input Size = 0 . Exit the game !"<<endl;
            exit (EXIT_SUCCESS);
           }

          string outFile="";
          lastPosition=0;
          command = partition(step,lastPosition);
          
          // Save command
          if(command == "SAVE") 
          {
            outFile = partition(step,lastPosition);
            save(outFile,userInputs,count);
          }

          //Load command
          if(command == "LOAD")
          {  
            string newInputFile = partition(step,lastPosition);
            load(newInputFile);
            livingCellAll = livingCellInFile; 
            //livingCellAll = livingCellAll - livingCellInFile;               
          }

          // Put the player step
          else 
          {
                for(int i=0; i<26; ++i)
                {
                   if(alphabetOrder[i] == command[0])
                   {  
                      if(i<getCurrentWidth())
                      {   
                          if(order==0)   // Player 1
                          { 
                              userInputs[count] = command[0];   //Collect player movements
                              ++count;

                              if(movement(i) == false) {        // If the user movement is fail,repeat the step
                                order=0;
                                break;
                              }

                              ++livingCellUser1;                
                              user1Win();                       // Check user 1 game winning state
                              if(getGameSelection()=='P')
                              {
                                  order=1;  // Player 2   
                              }

                              //Computer will make random movement
                              if(getGameSelection()=='C' && winner==false) 
                              { 
                                  int computerStep= (rand() % getCurrentWidth());
                                  order=1;
                                  // Collect all game movements
                                  userInputs[count] = static_cast<char>(computerStep+'A');
                                  ++count;

                                  //If it is not smart,it will make smart movement
                                  if(movement(computerStep) == false) 
                                  {
                                    computerSmartMove();
                                    order=0;
                                    ++livingCellUser2;                     
                                    user2OrComputerWin(); // Check user 2 game winning state
                                    break;
                                  }
                                  cout << endl << "Computer Movement (O) : " << static_cast<char>(computerStep+'A') << endl << endl;
                                  order=0;
                                  ++livingCellUser2;                   
                                  user2OrComputerWin(); // Check user 2 game winning state
                                  break;
                              }
            
                           break;
                          }
                          // Collect user 2 movement and check winning state of the user 2
                          else if(order == 1 && getGameSelection() !='C')
                          {  
                            userInputs[count] = command[0];
                            ++count;
                            // If the user movement is fail,repeat the step
                            if(movement(i) == false){
                              order=1;
                              break;
                            }
                           order=0;
                           ++livingCellUser2;
                           user2OrComputerWin();
                           break;
                          }
                      }
                      // If the movement is out of game board and players write any invalid command
                      else 
                      {
                        if(i > getCurrentWidth()-1 && command !="SAVE" && command !="LOAD")
                        {
                            cerr << endl << "> Wrong character or Incomplete command.Invalid Step !" << endl << endl;   
                        }   
                      }
                   }
              }    
          }
              // When there is no any winner,the game will end.
                if(gameEnded() && winner==false && winner2==false)
                {
                   display();
                   cout<<endl<<"Board Filled.Start Again !"<<endl<<endl;
                   return ;
                } 

          } // END WHILE   
  }

  // If the game board is not full,return false.
  bool ConnectFourAbstract::gameEnded()
  {
    if(livingCellAll < getCurrentWidth()*getCurrentHeight())
        return false;   
    else
        return true;
  }
 

}//CelalTemiz