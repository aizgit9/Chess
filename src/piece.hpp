#pragma once
namespace Piece {

	// Perform bitwise OR (|) to combine piece type and color into one identity
	enum Color { NONE = 0, WHITE = 8, BLACK = 16 };
	enum PieceType { EMPTY = 0, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

};
