/**
*ChessBoard.h
*@author Dillon Hatfield
**/
#ifndef CHESSBOARD_H
#define CHESSBOARD_H
class ChessBoard
{
	public:
		ChessBoard();
		ChessBoard(int size);
		~ChessBoard();
		void setSize(int size);
		int getSize();
		bool solve();
		void displayBoard();
	private:
		//pointer to pointer
		char** boardPtr;
		int boardSize;
		bool placed;
		bool placeQueens(int row, int column);
		bool checkPlacement(int row, int column);
		bool checkColumn(int column);
		bool checkRow(int row);
		bool checkDiagonalRight(int row, int column);
		bool checkDiagonalLeft(int row, int column);
		void deleteBoard();
};
#endif
