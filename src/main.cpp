#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "board.hpp"
#include "texture_manager.hpp"
#include <string>
#include <iostream>
#include <optional>
#include "drag_drop_controller.hpp"

void createBoardGraphic(sf::RenderWindow& window);
void preloadTextures(TextureManager& tm);
void displayPiecesOnBoard(Board& board, TextureManager& tm, sf::RenderWindow& window);
int getPlayerColor();
void handleInput(sf::RenderWindow& window, Board& board, DragDropController& ddc);

const sf::Color LIGHT_SQUARE_COLOR(220, 195, 141);
const sf::Color DARK_SQUARE_COLOR(75, 124, 87);
const int SQUARE_SIZE = 128;

int main()
{
    Board board(getPlayerColor());
    TextureManager tm;
    DragDropController ddc;
    preloadTextures(tm);

    auto window = sf::RenderWindow(sf::VideoMode({1024u, 1024u}), "Chess");
    window.setFramerateLimit(144);



    while (window.isOpen())
    {
        handleInput(window, board, ddc);

        window.clear(sf::Color::White);

        createBoardGraphic(window);
        displayPiecesOnBoard(board, tm, window);

        if (ddc.getDragging() == true && ddc.getDraggedPiece() != Piece::EMPTY) {
            
            sf::Sprite draggedPieceSprite(tm.getTexture(ddc.getDraggedPiece()));
            sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);

            sf::Vector2f mousePosFloat(
                static_cast<float>(mousePosInt.x + ddc.getDragOffsetX()),
                static_cast<float>(mousePosInt.y + ddc.getDragOffsetY())
            );



            draggedPieceSprite.setPosition(mousePosFloat);
            window.draw(draggedPieceSprite);
        }

        window.display();
    }
}

void createBoardGraphic(sf::RenderWindow& window) {

    using namespace sf;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {

            Color squareColor(0,0,0);
            Vector2f squarePosition(y * SQUARE_SIZE, x * SQUARE_SIZE);

            if ((y + x) % 2 == 0) {
                squareColor = LIGHT_SQUARE_COLOR;
            } else {
                squareColor = DARK_SQUARE_COLOR;
            }

            RectangleShape square(Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            square.setFillColor(squareColor);
            square.setPosition(squarePosition);

            window.draw(square);
        }
    }
}

void preloadTextures(TextureManager& tm) {
    // Piece Textures
    for (int pieceType = 1; pieceType < 7; pieceType++)
    {
        tm.loadPieceTexture(Piece::WHITE | pieceType);
        tm.loadPieceTexture(Piece::BLACK | pieceType);
    }
}

void displayPiecesOnBoard(Board& board, TextureManager& tm, sf::RenderWindow& window) {

    using namespace sf;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Vector2f piecePosition((x * SQUARE_SIZE), (y * SQUARE_SIZE));

            if (board.getPiece(x, y) != 0) {
                if (tm.has(board.getPiece(x, y))) {
                    Sprite pieceSprite(tm.getTexture(board.getPiece(x, y)));
                    pieceSprite.setPosition(piecePosition);
                    window.draw(pieceSprite);
                }
            }
        }
    }
}

int getPlayerColor() {

    using namespace std;
    int selection;
    int playerColor;
    do
    {
        cout << "Enter 1 to play as white or 2 to play as black: ";
        cin >> selection;

        if (cin.fail()) {
            cout << "\nInvalid Input! Try again." << endl;
            cin.clear(); // clears the failbit
            cin.ignore(1000, '\n'); // discards invalid input
            continue;
        }

        switch (selection)
        {
        case 1:
            return Piece::WHITE;
            break;
        case 2:
            return Piece::BLACK;
            break;
        default:
            cout << "\nInvalid Input! Try again." << endl;
            break;
        }

        
    } while (true);



}

void handleInput(sf::RenderWindow& window, Board& board, DragDropController& ddc) {
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {

                int clickX = mouseEvent->position.x;
                int clickY = mouseEvent->position.y;

                int boardX = clickX / SQUARE_SIZE;
                int boardY = clickY / SQUARE_SIZE;

                int spriteX = boardX * SQUARE_SIZE;
                int spriteY = boardY * SQUARE_SIZE;

                int dragOffsetX = spriteX - clickX;
                int dragOffsetY = spriteY - clickY;

                ddc.initiateDragDropOperation(boardX, boardY, dragOffsetX, dragOffsetY, board);
            }
        }

        if (const auto* mouseRelease = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseRelease->button == sf::Mouse::Button::Left) {
                int boardX = mouseRelease->position.x / SQUARE_SIZE;
                int boardY = mouseRelease->position.y / SQUARE_SIZE;

                ddc.endDragDropOperation(boardX, boardY, board);
            }
        }
    }
}