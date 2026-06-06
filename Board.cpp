#include "Board.h"
#include <iostream>
#include <algorithm>
using namespace std;

int row = 0;
int col = 0;

Board::Board() {
	for (row = 0; row < 8; row++) {
		for (col = 0; col < 8; col++) {
			board[row][col] = { EMPTY, NONE };
			board[1][col] = { PAWN, BLACK };
			board[6][col] = { PAWN, WHITE };

			board[0][0] = { ROOK, BLACK };
			board[0][7] = { ROOK, BLACK };
			board[7][0] = { ROOK, WHITE };
			board[7][7] = { ROOK, WHITE };

			board[0][1] = { KNIGHT, BLACK };
			board[0][6] = { KNIGHT, BLACK };

			board[7][1] = { KNIGHT, WHITE };
			board[7][6] = { KNIGHT, WHITE };

			board[0][2] = { BISHOP, BLACK };
			board[0][5] = { BISHOP, BLACK };

			board[7][2] = { BISHOP, WHITE };
			board[7][5] = { BISHOP, WHITE };

			board[0][3] = { QUEEN, BLACK };
			board[0][4] = { KING, BLACK };

			board[7][3] = { QUEEN, WHITE };
			board[7][4] = { KING, WHITE };

			blackKingPos = { 0, 4 };
			whiteKingPos = { 7, 4 };
		}
	}

}

void Board::printBoard() {
	cout << "    a b c d e f g h\n";
	cout << "   -----------------\n";

	for (row = 0; row < 8; row++) {
		cout << 8 - row << " | ";
		for (col = 0; col < 8; col++) {
			Piece piece = board[row][col];
			if (piece.type == EMPTY) {
				cout << ". ";
			}
			else if (piece.type == PAWN) {
				cout << (piece.color == WHITE ? "P " : "p ");
			}
			else if (piece.type == ROOK) {
				cout << (piece.color == WHITE ? "R " : "r ");
			}
			else if (piece.type == KNIGHT) {
				cout << (piece.color == WHITE ? "N " : "n ");
			}
			else if (piece.type == BISHOP) {
				cout << (piece.color == WHITE ? "B " : "b ");
			}
			else if (piece.type == QUEEN) {
				cout << (piece.color == WHITE ? "Q " : "q ");
			}
			else if (piece.type == KING) {
				cout << (piece.color == WHITE ? "K " : "k ");
			}
			else {
				cout << ". ";
			}
		}
		cout << "|\n";
	}
	cout << "   -----------------\n";
	cout << "    a b c d e f g h\n";
}
	
	Position Board::parsePosition(string square) {
		Position pos;
		pos.col = square[0] - 'a';
		pos.row = 8 - (square[1] - '0');
		return pos;
	}
	
	void Board::movePiece(Position from, Position to) {
		Piece movingPiece = board[from.row][from.col];

		board[to.row][to.col] = movingPiece;
		board[from.row][from.col] = { EMPTY, NONE };

		if (movingPiece.type == KING) {
			if (movingPiece.color == WHITE) {
				whiteKingPos = to;
			}
			else {
				blackKingPos = to;
			}
		}
	}
	
	bool Board::isValidPawnMove(Position from, Position to) {
		Piece piece = board[from.row][from.col];
		Piece target = board[to.row][to.col];

		if (piece.type != PAWN) {
			return false;
		}
		if (piece.color == WHITE) {
			bool oneSquare =
				(to.row == from.row - 1 &&
					to.col == from.col &&
					target.type == EMPTY);
			bool twoSquares =
				(from.row == 6 &&
					to.row == 4 &&
					to.col == from.col &&
					board[5][from.col].type == EMPTY &&
					target.type == EMPTY);
			bool captureMove =
				(to.row == from.row - 1 &&
					(to.col == from.col - 1 ||
						to.col == from.col + 1)
					&&
					target.color == BLACK);

			return oneSquare || twoSquares || captureMove;
		}
		if (piece.color == BLACK) {
			bool oneSquare =
				(to.row == from.row + 1 &&
					to.col == from.col &&
					target.type == EMPTY);
			bool twoSquares =
				(from.row == 1 &&
					to.row == 3 &&
					to.col == from.col &&
					board[2][from.col].type == EMPTY &&
					target.type == EMPTY);
			bool captureMoves =
				(to.row == from.row + 1 &&
					(to.col == from.col - 1 ||
						to.col == from.col + 1)
					&&
					target.color == WHITE);
			return oneSquare || twoSquares || captureMoves;
		}
		return false;
	}
	bool Board::isValidRookMove(Position from, Position to) {
		Piece piece = board[from.row][from.col];
		if (piece.type != ROOK) {
			return false;
		}
		if (from.row != to.row && from.col != to.col) {
			return false;
		}
		if (from.row == to.row) {
			int startCol = min(from.col, to.col);
			int endCol = max(from.col, to.col);
			for (int col = startCol + 1; col < endCol; col++) {
				if (board[from.row][col].type != EMPTY) {
					return false;
				}
			}
		}
		if (from.col == to.col) {
			int startRow = min(from.row, to.row);
			int endRow = max(from.row, to.row);
			for (int row = startRow + 1; row < endRow; row++) {
				if (board[row][from.col].type != EMPTY) {
					return false;
				}
			}
		}
		Piece target = board[to.row][to.col];
		if (target.color == piece.color) {
			return false;
		}
		return true;
	}
	bool Board::isValidKnightMove(Position from, Position to) {
		Piece piece = board[from.row][from.col];
		if (piece.type != KNIGHT) {
			return false;
		}
		int rowDiff = abs(from.row - to.row);
		int colDiff = abs(from.col - to.col);

		bool knightMove =
			(rowDiff == 2 && colDiff == 1) ||
			(rowDiff == 1 && colDiff == 2);
		if (!knightMove) {
			return false;
		}
		Piece target = board[to.row][to.col];
		if (target.color == piece.color) {
			return false;
		}
		return true;
	}
	bool Board::isValidBishopMove(Position from, Position to) {
		Piece piece = board[from.row][from.col];
		if (piece.type != BISHOP) {
			return false;
		}
		int rowDiff = abs(from.row - to.row);
		int colDiff = abs(from.col - to.col);

		if (rowDiff != colDiff) {
			return false;
		}
		int rowStep;
		if (to.row > from.row) {
			rowStep = 1;
		}
		else {
			rowStep = -1;
		}
		int colStep;
		if (to.col > from.col) {
			colStep = 1;
		}
		else {
			colStep = -1;
		}

		int currentRow = from.row + rowStep;
		int currentCol = from.col + colStep;
		while (currentRow != to.row) {
			if (board[currentRow][currentCol].type != EMPTY) {
				return false;
			}
			currentRow += rowStep;
			currentCol += colStep;
		}
		Piece target = board[to.row][to.col];
		if (target.color == piece.color) {
			return false;
		}
		return true;
	}
	bool Board::isValidQueenMove(Position from, Position to)
	{
		Piece piece = board[from.row][from.col];

		if (piece.type != QUEEN)
		{
			return false;
		}

		Piece target = board[to.row][to.col];

		if (target.color == piece.color)
		{
			return false;
		}

		int rowDiff = abs(from.row - to.row);
		int colDiff = abs(from.col - to.col);

		// Bishop movement
		if (rowDiff == colDiff)
		{
			int rowStep = (to.row > from.row) ? 1 : -1;
			int colStep = (to.col > from.col) ? 1 : -1;

			int currentRow = from.row + rowStep;
			int currentCol = from.col + colStep;

			while (currentRow != to.row)
			{
				if (board[currentRow][currentCol].type != EMPTY)
				{
					return false;
				}

				currentRow += rowStep;
				currentCol += colStep;
			}

			return true;
		}

		// Rook movement
		if (from.row == to.row || from.col == to.col)
		{
			if (from.row == to.row)
			{
				int startCol = min(from.col, to.col);
				int endCol = max(from.col, to.col);

				for (int col = startCol + 1; col < endCol; col++)
				{
					if (board[from.row][col].type != EMPTY)
					{
						return false;
					}
				}
			}

			if (from.col == to.col)
			{
				int startRow = min(from.row, to.row);
				int endRow = max(from.row, to.row);

				for (int row = startRow + 1; row < endRow; row++)
				{
					if (board[row][from.col].type != EMPTY)
					{
						return false;
					}
				}
			}

			return true;
		}

		return false;
	}
	bool Board::isValidKingMove(Position from, Position to) {
		Piece piece = board[from.row][from.col];
		if (piece.type != KING) {
			return false;
		}
		int rowDiff = abs(from.row - to.row);
		int colDiff = abs(from.col - to.col);

		if (rowDiff > 1 || colDiff > 1) {
			return false;
		}
		Piece target = board[to.row][to.col];
		if (target.color == piece.color) {
			return false;
		}
		return true;
	}
	Position Board::findKing(PieceColor color) {
		if (color == WHITE) {
			return whiteKingPos;
		}
		return blackKingPos;
	}
	bool Board::isKingInCheck(PieceColor color) {
		Position kingPos = findKing(color);
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				Piece piece = board[row][col];
				if (piece.color == NONE) {
					continue;
				}
				if (piece.color == color) {
					continue;
				}
				Position from;
				from.row = row;
				from.col = col;

				if (piece.type == PAWN &&
					isPawnAttacking(from, kingPos)) {
					return true;
				}
				if (piece.type == ROOK &&
					isValidRookMove(from, kingPos)) {
					return true;
				}
				if (piece.type == KNIGHT &&
					isValidKnightMove(from, kingPos)) {
					return true;
				}
				if (piece.type == BISHOP &&
					isValidBishopMove(from, kingPos)) {
					return true;
				}
				if (piece.type == QUEEN &&
					isValidQueenMove(from, kingPos)) {
					return true;
				}
				if (piece.type == KING &&
					isValidKingMove(from, kingPos)) {
					return true;
				}
			}
		}
			return false;
		}

	bool Board::wouldMoveLeaveKingInCheck(Position from, Position to) {
		Piece movingPiece = board[from.row][from.col];
		Piece capturedPiece = board[to.row][to.col];
		Position oldWhiteKingPos = whiteKingPos;
		Position oldBlackKingPos = blackKingPos;


		board[to.row][to.col] = movingPiece;
		board[from.row][from.col] = { EMPTY, NONE };
		if (movingPiece.type == KING) {
			if (movingPiece.color == WHITE)
				whiteKingPos = to;
			else
				blackKingPos = to;
		}

		bool kingInCheck = isKingInCheck(movingPiece.color);
		cout << "Move tested: "
			<< from.row << "," << from.col
			<< " -> "
			<< to.row << "," << to.col
			<< "   kingInCheck=" << kingInCheck
			<< endl;
		board[from.row][from.col] = movingPiece;
		board[to.row][to.col] = capturedPiece;

		whiteKingPos = oldWhiteKingPos;
		blackKingPos = oldBlackKingPos;
		return kingInCheck;
	}
	bool Board::isPawnAttacking(Position from, Position target) {
		Piece piece = board[from.row][from.col];
		if (piece.type != PAWN) {
			return false;
		}
		if (piece.color == WHITE) {
			return target.row == from.row - 1 &&
				(target.col == from.col - 1 ||
					target.col == from.col + 1);
		}
		if (piece.color == BLACK) {
			return target.row == from.row + 1 &&
				(target.col == from.col - 1 ||
					target.col == from.col + 1);
		}
		return false;
	}
	bool Board::isCheckmate(PieceColor color) {
		if (!isKingInCheck(color)) {
			return false;
		}
		return !hasLegalMove(color);
	}
	bool Board::hasLegalMove(PieceColor color) {
		for (int fromRow = 0; fromRow < 8; fromRow++) {
			for (int fromCol = 0; fromCol < 8; fromCol++) {
				Piece piece = board[fromRow][fromCol];
				if (piece.color != color) {
					continue;
				}
				Position from;
				from.row = fromRow;
				from.col = fromCol;

				for (int toRow = 0; toRow < 8; toRow++) {
					for (int toCol = 0; toCol < 8; toCol++) {
						Position to;
						to.row = toRow;
						to.col = toCol;
						if (!isValidMove(from, to)) {
							continue;
						}
						if (!wouldMoveLeaveKingInCheck(from, to)) {
							cout << "Legal move found: "
								<< from.row << "," << from.col
								<< " -> "
								<< to.row << "," << to.col
								<< endl;
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	bool Board::isValidMove(Position from, Position to) {
		Piece piece = board[from.row][from.col];
		switch (piece.type) {

		case PAWN:
			return isValidPawnMove(from, to);
		case ROOK:
			return isValidRookMove(from, to);
		case KNIGHT:
			return isValidKnightMove(from, to);
		case BISHOP:
			return isValidBishopMove(from, to);
		case QUEEN:
			return isValidQueenMove(from, to);
		case KING:
			return isValidKingMove(from, to);
		default:
			return false;
		}
	}
	