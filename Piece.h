#pragma once

enum PieceType {
	EMPTY,
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

enum PieceColor {
	NONE,
	WHITE,
	BLACK
};

struct Piece {
	PieceType type;
	PieceColor color;
};