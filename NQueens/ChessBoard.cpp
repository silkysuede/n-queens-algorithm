/**
*ChessBoard.cpp
*@author Dillon Hatfield
**/
#include "ChessBoard.h"
#include <iostream>
using namespace std;

//default constructor
ChessBoard::ChessBoard() :
	placed(false)
{
	/*
	Call setSize() to allocate memory
	for the 2d array. 8 is the default size.
	*/
	setSize(8);
}//end ChessBoard()

/**
*Parameterized ChessBoard constructor.
*@param SIZE: the size of the board.
**/
ChessBoard::ChessBoard(int size) :
	placed(false)
{
	/*
	Call setSize() to allocate memory
	for the 2d array. The size of the array
	is decided by the value passed in.
	*/
	setSize(size);
}//end ChessBoard(int size)

/**
*Deallocate memory on the heap.
*@pre boardPtr must be on the heap.
**/
void ChessBoard::deleteBoard()
{
	//loop through 2D array and delete the arrays inside of it
	for (int i = 0; i < boardSize; ++i)
	{
		delete[] boardPtr[i];
	}//end for
	//delete the 2d array
	delete[] boardPtr;
}

//deconstructor
ChessBoard::~ChessBoard()
{
	//deallocate memory on heap
	deleteBoard();
}//end ~ChessBoard()

/**
*Set the size of the Chessboard.
*@param SIZE: the size of the board.
**/
void ChessBoard::setSize(int size)
{
	if (size > 12)
	{
		boardSize = 12;
	}//end if
	else if (size < 4)
	{
		boardSize = 4;
	}//end if
	//set boardSize to the size passed in.
	else { boardSize = size; }//end else

	/*
	allocate memory for array of pointers 
	that will store pointers to arrays.
	*/
	boardPtr = new char* [boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		//allocate memory for each row of 2d array
		boardPtr[i] = new char[boardSize];
	}//end for
}//end setSize()

/**
*Get the size of the Chessboard.
*@return the size of the board.
**/
int ChessBoard::getSize()
{
	return boardSize;
}//end getSize()

/**
*Call placeQueens() and fill the empty
*spaces in the board.
*@return true if successful.
**/
bool ChessBoard::solve()
{
	//if all the queens get placed
	if (placeQueens(0, 0) == true)
	{
		//nested for loop to fill the empty spaces
		for (int j = 0; j < getSize(); j++)
		{
			for (int i = 0; i < getSize(); i++)
			{
				if (boardPtr[i][j] != 'Q')
				{
					boardPtr[i][j] = '*';
				}//end if

			}//end for

		}//end for
		return true;
	}//end if
	//return false if queens aren't able to be placed.
	return false;
}//end solve()

/**
*Print the solution for the board to the console.
**/
void ChessBoard::displayBoard()
{
	//nested for loop that prints each square
	for (int i = 0; i < getSize(); i++)
	{
		for (int k = 0; k < getSize(); k++)
		{
			cout << boardPtr[i][k] << " ";
		}//end for
		cout << '\n';
	}//end for

}//end displayBoard()

/**
*Recursively checks the board and attempts to place
*a queen at the row and column intersection.
*@param ROW: the row the queen will be placed in.
*@return true if the queen can be placed at the desired
*location and all columns to the right of the specified
*column.
*@param COLUMN: the column the queen will be placed in.
*@pre row and column must have values higher than 0.
*@pre boardPtr must already be defined and on the heap. 
**/
bool ChessBoard::placeQueens(int row, int column)
{
	/*row needs to be zero so 
	the search begins at the top 
	of each column for every interation
	*/
	row = 0;
	//return true when the board is filled
	if (column >= boardSize)
	{
		return true;
	}//end if
	else
	{
		while (row != getSize())
		{
			//determines if the queen was put down
			placed = false;
			/*
			check if the square we want to place the
			queen in is under attack
			*/
			if (checkPlacement(row, column) == true)
			{
				//if not, put down a queen
				boardPtr[row][column] = 'Q';
				placed = true;
			}//end if
			else
			{
				//placed is false if the queen was not placed down
				placed = false;
			}//end else

			if (placed != true)
			{
				//increment column so the search can continue
				row++;
				continue;
			}//end if

			if (placeQueens(row, column + 1) == false)
			{
				//remove the last queen put down
				boardPtr[row][column] = 'f';
				//increment row so search can continue
				row++;
			}//end if
			else
			{
				//return true if queen was placed down
				return true;
			}//end else
		}//end while

		/*
		All rows have been considered without a
		successful placement. return false and backtrack.
		*/
		return false;
	}//end else

}//end placeQueens()

/**
*Check the square we want to place the queen in and
*see if it is under attack from another queen.
*@param ROW: the row we want to place a queen in.
*@return true if the queen can be placed at the desired
*location.
*@param COLUMN: the column we want to place a queen in.
*@pre row and column must have values higher than 0.
*@pre space on the heap for boardPtr must be allocated.
*
**/
bool ChessBoard::checkPlacement(int row, int column)
{

	if (checkColumn(column) == true)
	{
		if (checkRow(row) == true)
		{
			if (checkDiagonalRight(row, column) == true)
			{
				if (checkDiagonalLeft(row, column) == true)
				{
					/*
					if the queen is not able to
					attack the square, return true.
					*/
					return true;
				}//end if

			}//end if

		}//end if

	}//end if

	/*
	if the queen is able to
	attack the square, return false.
	*/
	return false;
}//end checkPlacement()

/**
*Checks the entire column for a queen.
*@param COLUMN: the column we want to check.
*@return true if no queen is found.
*@pre column must have a value higher than 0.
**/
bool ChessBoard::checkColumn(int column)
{
	/*
	loop through all the squares in the column
	and see if there is a queen in them.
	*/
	for (int i = 0; i < getSize(); i++)
	{
		//if a queen is found, return false.
		if (boardPtr[i][column] == 'Q')
		{
			return false;
		}//end if
	}//end for

	/*
	if no queens are found in the same column as
	the desired placement, return true.
	*/
	return true;
}//end checkColumn()

/**
*Checks the entire row for a queen.
*@param ROW: the row we want to check.
*@return true if no queen is found.
*@pre row must have a value higher than 0.
**/
bool ChessBoard::checkRow(int row)
{
	/*
	loop through all the squares in the row
	and see if there is a queen in them.
	*/
	for (int i = 0; i < getSize(); ++i)
	{
		//if a queen is found, return false.
		if (boardPtr[row][i] == 'Q')
		{
			return false;

		}//end if
	}//end for

	/*
	if no queens are found in the same row as
	the desired placement, return true.
	*/
	return true;
}//end checkRow()

/**
*Checks the diagonals to the right of the square
*we want to place a queen in.
*@param ROW: the row we want to check.
*@return true if no queen is found.
*@param COLUMN: the column we want to check.
*@pre row and column must have a value higher than 0.
**/
bool ChessBoard::checkDiagonalRight(int row, int column)
{
	//copies of row and column
	int rows = row;
	int columns = column;
	/*
	loop through all the squares diagonal
	and to the right of the desired placement
	and see if there is a queen in them.
	*/
	if (column == (getSize() - 1))
	{
		return true;
	}//end if

	//top right search
	while ((column != (getSize() - 1)) && (row != 0))
	{
		++column;
		--row;
		//if a queen is found, return false.
		if (boardPtr[row][column] == 'Q')
		{
			return false;
		}//end if	
	}//end while

	//bottom right search
	while ((columns != (getSize() - 1)) && (rows != (getSize() - 1)))
	{
		++columns;
		++rows;
		if (boardPtr[rows][columns] == 'Q')
		{
			return false;
		}//end if
	}//end while

	/*
	if no queens are found in any of the diagonals
	to the right of the desired placement, return true.
	*/
	return true;
}//end checkDiagonalRight()

/**
*Checks the diagonals to the left of the square
*we want to place a queen in.
*@param ROW: the row we want to check.
*@return true if no queen is found.
*@param COLUMN: the column we want to check.
*@pre row and column must have a value higher than 0.
**/
bool ChessBoard::checkDiagonalLeft(int row, int column)
{
	//copies of row and column
	int rows = row;
	int columns = column;
	/*
	loop through all the squares diagonal
	and to the left of the desired placement
	and see if there is a queen in them.
	*/
	if (column == 0)
	{
		return true;
	}//end if

	//top left search
	while ((column != 0) && (row != 0))
	{
		--column;
		--row;
		//if a queen is found, return false.
		if (boardPtr[row][column] == 'Q')
		{
			return false;
		}//end if

	}//end while

	//bottom left search
	while ((columns != 0) && (rows != (getSize() - 1)))
	{
		--columns;
		++rows;
		//if a queen is found, return false.
		if (boardPtr[rows][columns] == 'Q')
		{
			return false;
		}//end if
	}//end while

	/*
	if no queens are found in any of the diagonals
	to the left of the desired placement, return true.
	*/
	return true;
}