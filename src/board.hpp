#include "piece.hpp"
#pragma once
class Board {

    
public:
    int boardGrid[8][8];

    Board(int playerColor) {
        int enemyColor = 16;
        if (playerColor == Piece::WHITE) {
            enemyColor = 16;
        }
        else if(playerColor == Piece::BLACK) {
            enemyColor = 8;
        }
            setPiece(0, 0, enemyColor | Piece::ROOK);
            setPiece(1, 0, enemyColor | Piece::KNIGHT);
            setPiece(2, 0, enemyColor | Piece::BISHOP);
            setPiece(3, 0, enemyColor | Piece::QUEEN);
            setPiece(4, 0, enemyColor | Piece::KING);
            setPiece(5, 0, enemyColor | Piece::BISHOP);
            setPiece(6, 0, enemyColor | Piece::KNIGHT);
            setPiece(7, 0, enemyColor | Piece::ROOK);

            for (int i = 0; i < 8; i++)
            {
                setPiece(i, 1, enemyColor | Piece::PAWN);
            }

            for (int i = 0; i < 8; i++)
            {
                setPiece(i, 6, playerColor | Piece::PAWN);
            }

            setPiece(0, 7, playerColor | Piece::ROOK);
            setPiece(1, 7, playerColor | Piece::KNIGHT);
            setPiece(2, 7, playerColor | Piece::BISHOP);
            setPiece(3, 7, playerColor | Piece::QUEEN);
            setPiece(4, 7, playerColor | Piece::KING);
            setPiece(5, 7, playerColor | Piece::BISHOP);
            setPiece(6, 7, playerColor | Piece::KNIGHT);
            setPiece(7, 7, playerColor | Piece::ROOK);
    }

    const int(&getGrid() const)[8][8] {
        return boardGrid; 
    }

    int getPiece(int row, int col) const {
        return boardGrid[row][col]; 
    }
    void setPiece(int row, int col, int piece) {
        boardGrid[row][col] = piece; 
    }
};
