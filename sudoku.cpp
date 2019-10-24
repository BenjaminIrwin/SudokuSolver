#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */
    
    /*Function to solve a board*/
bool solve_board(char board [][9])
{
    /*Recursive call counter*/
    int counter = 0;

    /*Flag to choose if Sudoku is assessed backwards (for question 5)*/
    bool backwards = false;
    int start_row = 0, start_column = 0;

    if(recursive_search(board, counter, backwards, start_row, start_column))
    {
        return true;
    } else return false;
}

    /* Function to verify moves and fill board spaces if possible */
bool recursive_search (char board[][9], int& counter, bool backwards, int row, 
int column)
{

    /* Counter to keep track of number of recursive calls */
    counter++;

    /* Stopping case: if the board is full */
    if(is_complete(board))
        return true;

    /* Look for a '.' */
    
    if (backwards == true)
    {
        while (board[row][column] != '.' && row >= 0)
        {
            column--; 
            if(column < 0)
            {
                row--;
                column = 8;
            }
        }
    } 
    else
    {
        while (board[row][column] != '.' && column < 9)
        {
            row++;
            if(row > 8)
            {
                column++;
                row = 0;
            }
        }
    }


        /* Test out different values in sudoku position */
    for (int i = 1; i < 10; i++)
    {
        const char digit = static_cast<char>(i + 48);
        if (change_value(board, digit, row, column) &&
        recursive_search(board, counter, backwards, row, column))//Recursive call 
        {
            return true;           
        } 
    }

    /* If no value has been found */
    board[row][column] = '.';
    return false;
}

    /* Function to check if the board is complete */
bool is_complete(char board [][9]) 
{
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {    
            
           if (board[r][c] == '.')
                return false;

           int v = ((static_cast<int>(board[r][c]) - 48));
           
           if (v > 9 || v < 1) 
            {
                return false;
            }    
        }
    }        

    return true;
}

    /* Function to verify if a move is valid, and execute a move */
bool make_move(const char position [], char digit, char board [][9])
{

    /* Check if input digit is valid (1-9) */
    if (digit < 49 || digit > 57)
    {
        return false;
    }
    
    /* Check if coordinates are two chars */
    if (position[2] != '\0')
    {
        return false;
    }

    /* Separate position into two ints (range 0-8) and checking validity */
    int column = (static_cast<int>(position[1])-49);
    if (column > 8 || column < 0)
    {
        return false;
    }

    /* If row letter is uppercase or lowercase */
    int r = static_cast<int>(position[0]), row;
    if (r > 64 && r < 74)

    {    
        row = r - 65;
    }
    else if (r > 96 && r < 106)
    {
        row = r - 97;
    } 
    else 
    {
        return false;
    }

    /* Check if move overwrites pre-filled space */
    if (board[row][column] != '.') 
    {
        return false;
    } 

    /* Change value and end function */
    if (change_value(board, digit, row, column))
    {
        return true;
    }    
    else 
    {
        return false;
    }
}
    /* Function to change the value of a board position */
bool change_value(char board[][9], const char digit, int row, int column)
{
    if ((check_rc(board, digit, row, column)) && (check_square(board, digit, row, column)))
    {
        board[row][column] = digit;
        return true;
    } else return false;

}

    /*Function to check for copies on the row and column*/
bool check_rc(char board[][9], const char digit, int row, int column)
{
    
    for (int i = 0; i < 9; i++)
    {
        if (board[row][i] == digit || board[i][column] == digit)
        {
            return false;
        } 
    }
    
    return true;
}

    /*Function to check 3x3 square*/
bool check_square(char board[][9], const char digit, int row, int column)
{
    int third_column = column/3, third_row = row/3;
    for (int c = third_column*3; c < third_column*3 + 3; c++)
    {
        for (int r = third_row*3; r < third_row*3 + 3; r++)
        {
            if (board[r][c] == digit)
                return false;
         }
    }
    return true;
}

    /*Function to save board*/
bool save_board(const char filename[], char board[][9])
{
    char a;

    ofstream save;
    save.open(filename);
    
    if(save.fail())
        return false;
        else
        {
            for (int r = 0; r < 9; r++)
            {    
                for (int c = 0; c < 9; c++)
                {
                    a = board[r][c];
                    save.put(a);
                }

                save << endl;

            }
        }

    save.close();

    return true;

}
    
    /* Function to test mystery boards*/
void solve_mystery_board(const char* filename)
{
    
    cout << "RECURSION CHECK: " << endl << endl;

    char board_copy1[9][9];
    char board_copy2[9][9];

    cout << "Loading board for two tests:" << endl;
    load_board(filename, board_copy1);
    load_board(filename, board_copy2);
    cout << endl; 

    int counter = 0;

    /*Solve board forwards*/
    bool backwards = false;
    int start_row = 0, start_column = 0;

    if(recursive_search(board_copy1, counter, backwards, start_row, start_column))
    {
        cout << "Result: " << endl << filename << " requires " << counter 
        << " calls when solving forwards." << endl;
    }            
    
    counter = 0;

    /*Solve board backwards*/
    backwards = true;
    start_row = 8, start_column = 8;
    if(recursive_search(board_copy2, counter, backwards, start_row, start_column))
    {
        cout << filename << " requires " << counter 
        << " calls when solving backwards." << endl << endl;
    }
    
}

