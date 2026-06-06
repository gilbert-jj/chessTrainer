#pragma once
#include "Piece.h"
#include "Position.h"
#include <string>


class Board
{
public:
	Piece board[8][8];
	Board();
	void printBoard();

	void movePiece(Position from, Position to);

	Position parsePosition(std::string square);

	bool isValidPawnMove(Position from, Position to);

	bool isValidRookMove(Position from, Position to);

	bool isValidKnightMove(Position from, Position to);

	bool isValidBishopMove(Position from, Position to);

	bool isValidQueenMove(Position from, Position to);

	bool isValidKingMove(Position from, Position to);

	Position findKing(PieceColor color);
	
	bool isKingInCheck(PieceColor color);

	bool wouldMoveLeaveKingInCheck(Position from, Position to);

	bool isPawnAttacking(Position from, Position target);

	bool isCheckmate(PieceColor color);

	bool hasLegalMove(PieceColor color);

	bool isValidMove(Position from, Position to);

	private:

		Position whiteKingPos;
		Position blackKingPos;
};
