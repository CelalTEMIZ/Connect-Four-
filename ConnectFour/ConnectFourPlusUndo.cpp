#include <iostream>
#include <fstream>
#include "ConnectFourPlusUndo.h"
#include "ConnectFourPlus.h"

using std::cout;
using std::endl;

namespace CelalTemiz
{
  int ConnectFourPlusUndo::fileFlag=0;
  int ConnectFourPlusUndo::secondFileFlag=0; 

   // No parameter constructor
  ConnectFourPlusUndo::ConnectFourPlusUndo():ConnectFourPlus()
  {
       // Body Intentionally Empty
  }
   
  ConnectFourPlusUndo::ConnectFourPlusUndo(int newWidth, int newHeight, char newGameSelect)
  :ConnectFourPlus(newWidth,newHeight,newGameSelect)
  {  
       // Body Intentionally Empty
  }

  // Load command function
  void ConnectFourPlusUndo::load(string  inputFileName)
  {
    int  flag=1;
    ifstream fin;
    ofstream undoFile;
    fin.open(inputFileName,ios::in | ios::binary);

    if(fin.fail())
    {
      cerr << "Input file opening failed." << endl;
      exit(1);
    }

    // If the user makes load command, create a temporary file
    if(fileFlag==1)
    { 
      undoFile.open("undoChangeFile.txt");
      if(undoFile.fail()) 
      {
        cerr << "undoChangeFile file opening failed." << endl;
        exit(1);
      }  
    }
    // Read object type P, D or U from the saved file
      char nextInputChar;
      while(flag==1)
      {
        fin.get(nextInputChar);
        if(nextInputChar == 'P' || nextInputChar == 'D' || nextInputChar == 'U')
        {
          setObjectType(nextInputChar);
          flag=0;
        }
      }

      // Read new board width and heightfrom the saved file
      int boardWidth=0,boardHeight=0;
      fin >> boardWidth >> boardHeight;

      livingCellInFile=0;

      // Set the new board parameters and resize new game
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
      
      // If the user makes load command
      // Write to new board parameters temporary file
      if(fileFlag==1)
      {
        undoFile<<getObjectType()<<endl;
        undoFile<<getCurrentWidth()<<endl;
        undoFile<<getCurrentHeight()<<endl;
        undoFile<<getGameSelection()<<endl;
      }
     // Read user inputs to load command and save the array
      int i=0,availableInputNumber=0;

      while(!fin.eof()) 
      {
        nextInputChar = fin.get();       
        // Check available characters in text file
        if(nextInputChar != '\n' && nextInputChar !='\0' && nextInputChar >='A' && nextInputChar<='Z')
        {     
          if(nextInputChar >='A' && nextInputChar<(getCurrentWidth()+'A'))
          { 
            if(fileFlag==1) undoFile<<nextInputChar<<endl;
            charArray[i] = nextInputChar;  
            ++i;
            ++availableInputNumber;
            ++livingCellInFile;
          }
        }      
      }                    

    // If the user makes load command,last element will remove from the file inputs
     static int addRate=1;
     if(secondFileFlag==1)
     {
        livingCellAll=1;
        availableInputNumber-=addRate;
        ++addRate;   
     }
     
     // If the command is UNDO,not change player order
     int tempOrder = order;


     // Put available chars to game board 
      if(availableInputNumber != 0)  
      {
        for(int i=0; i<availableInputNumber; ++i)
        {
          if(i%2==0)
          {
            order = 0;  // Put the player 1 inputs
            movement(letterToBoardPosition(charArray[i]));
          }
          else
          {
            order = 1;  // Put the player 2 or Computer inputs
            movement(letterToBoardPosition(charArray[i]));
          }
         }   
      }
   
      order = tempOrder;

      fin.close(); 
      undoFile.close();  
  }

// Single step play function to users and computer
  void ConnectFourPlusUndo::playGame()
  {
      int lastPosition=0,loadFileFlag=0;
      char choice;
      string step="", alphabetOrder = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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
           
          // Get the user step from the keyboard 
          getline(cin,step);  
          
          // If the user input size is equal to zero, the game will end
          if(step.length() == 0)
          {
            cerr << endl<< "User Input Size = 0 . Exit the game !"<<endl;
            exit (EXIT_SUCCESS);
          }

          string command="", outFile="";
          lastPosition=0;
          command = partition(step,lastPosition);
          
          // SAVE command
          if(command == "SAVE") 
          {
            // Parse user command and select the fileName from the user command
            // And the call the save function and write all user inputs
            outFile = partition(step,lastPosition);
            save(outFile,userInputs,count);
          }

          //LOAD command
          if(command == "LOAD")
          {  
            // Parse user command and select the fileName from the user command
            // And then call the load function to start the new game
            string newInputFile = partition(step,lastPosition);
            fileFlag=1;
            secondFileFlag=0;
            livingCellAll = 0;
            load(newInputFile);
            secondFileFlag=1;
            livingCellAll = livingCellInFile;              
          }

          // UNDO Command
          if(command == "UNDO")
          {
            if(fileFlag==0 && secondFileFlag==0)
            {
                // If game selection is PvP,take size of user inputs minus one and save these inputs to undoFile.txt
                // Otherwise take size of inputs minus two
                // Then load this file and continue the previous game
                if(getGameSelection()=='P') count = count-1;
                if(getGameSelection()=='C') count = count-2; 
                // If the user doesn't make load commad
                // Create temporary file and read its inputs            
                save("undoFile.txt",userInputs,count);
                livingCellInFile = 0;
                load("undoFile.txt");

                if(getGameSelection()=='P') livingCellAll = livingCellAll - 1;  // Remove last one movement (P)
                if(getGameSelection()=='C') livingCellAll = livingCellAll - 2;  // Remove last two movements (P and C)            
                livingCellAll = livingCellAll - livingCellInFile; // Remove temp file input number
            }

            if(fileFlag==1)
            {
                fileFlag=0;
                secondFileFlag=1;
                // If the user makes the load command, function will create temporary files
                // and then will read this file inputs
                load("undoChangeFile.txt");
                fileFlag=1;
                livingCellAll = livingCellAll - 1;
            }
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
                          userInputs[count] = command[0];   // Keep all user 1 movements
                          ++count;
                          if(movement(i) == false) {        // If the user movement is fail,repeat the step
                            order=0;
                            break;
                          }
                          ++livingCellUser1;                
                          user1Win();                       // Check user 1 game state

                          if(getGameSelection()=='P') order=1;  // Player 2   
                          
                          if(getGameSelection()=='C' && winner==false)       // Create random step 
                          { 
                            int computerStep= (rand() % getCurrentWidth());
                            order=1;
                            userInputs[count] = static_cast<char>(computerStep+'A');  // Keep all computer movements
                            ++count;
                            // If random number is not intelligent,computer will make smart move
                            if(movement(computerStep) == false) 
                            {
                              computerSmartMove();  // Smart Computer Move
                              order=0;
                              ++livingCellUser2;                     
                              user2OrComputerWin(); // Check computer winning state
                              break;
                            }
                            cout << endl << "Computer Movement (O) : " << static_cast<char>(computerStep+'A') << endl << endl;
                            order=0;
                            ++livingCellUser2;                                                     
                            user2OrComputerWin(); // Check computer winning state
                            break;
                          }
                       
                       break;
                      }
                      
                      else if(order == 1 && getGameSelection() !='C')
                      {  
                       userInputs[count] = command[0];  // Keep all user 2 inputs
                       ++count;

                       if(movement(i) == false) 
                       { // If the user movement is fail,repeat the step
                          order=1;
                          break;
                       }
                       order=0; 
                       ++livingCellUser2;
                       user2OrComputerWin(); // Check the user 2 winning state
                       break;
                      }
                  }

                  else // Prompt the players about their movements
                  {
                    if(i > getCurrentWidth()-1 && command !="SAVE" && command !="LOAD")
                    {
                        cerr << endl << "> Wrong character or Incomplete command.Invalid Step !" << endl << endl;   
                    }    
                  }
               }
          }    
        }       // If the board is full,the game will end
                if(gameEnded() && winner==false && winner2==false)
                {
                   display();
                   cout<<endl<<"Board Filled.Start Again !"<<endl<<endl;
                   return ;
                }            
          } // end while
      
  }

}//CelalTemiz
