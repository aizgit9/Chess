#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "piece.hpp"
#pragma once

class DragDropController {
private:
	bool isDragging;
	int startX;
	int startY;
	int draggedPiece;
	int dragOffsetX;
	int dragOffsetY;

public:
	DragDropController() {
		isDragging = false;
		startX = -1;
		startY = -1;
		draggedPiece = Piece::EMPTY;
		dragOffsetX = 0;
		dragOffsetY = 0;
	}

	void setDragging(bool isDragging) {
		this->isDragging = isDragging;
	}

	bool getDragging() {
		return isDragging;
	}

	int getDraggedPiece() {
		return draggedPiece;
	}

	int getDragOffsetX() {
		return dragOffsetX;
	}

	int getDragOffsetY() {
		return dragOffsetY;
	}

	void initiateDragDropOperation(int& startX, int& startY, int& dragOffsetX, int& dragOffsetY, Board& board) {
		setDragging(true);
		this->startX = startX;
		this->startY = startY;

		this->dragOffsetX = dragOffsetX;
		this->dragOffsetY = dragOffsetY;

		draggedPiece = board.getPiece(startX, startY);
		board.setPiece(startX, startY, Piece::EMPTY);
	}

	void endDragDropOperation(int& newX, int& newY, Board& board) {
		setDragging(false);

		board.setPiece(newX, newY, draggedPiece);



		draggedPiece = Piece::EMPTY;
		startX = -1;
		startY = -1;
		dragOffsetX = 0;
		dragOffsetY = 0;
		
	}
};