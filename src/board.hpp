#include "piece.hpp"
#pragma once
class Board {
public:
    int boardGrid[8][8];

    Board() {
        boardGrid[0][0] = Piece::WHITE | Piece::KING;
    }
};
