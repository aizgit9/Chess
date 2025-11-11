#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "board.hpp"
#include "texture_manager.hpp"
#include <string>
#include <iostream>
#include <optional>

void createBoardGraphic(sf::RenderWindow& window);
void preloadTextures(TextureManager& tm);
void displayPiecesOnBoard(Board& board, TextureManager& tm, sf::RenderWindow& window);

const sf::Color LIGHT_SQUARE_COLOR(220, 195, 141);
const sf::Color DARK_SQUARE_COLOR(75, 124, 87);
const int SQUARE_SIZE = 120;

int main()
{
    Board board(Piece::BLACK);
    TextureManager tm;
    preloadTextures(tm);

    auto window = sf::RenderWindow(sf::VideoMode({1080u, 1080u}), "Chess");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        createBoardGraphic(window);
        displayPiecesOnBoard(board, tm, window);
        window.display();
    }
}

void createBoardGraphic(sf::RenderWindow& window) {

    using namespace sf;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {

            Color squareColor(0,0,0);
            Vector2f squarePosition(x * SQUARE_SIZE, y * SQUARE_SIZE);

            if ((x + y) % 2 == 0) {
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
        std::cout << (Piece::WHITE | pieceType) << std::endl;
        std::cout << (Piece::BLACK | pieceType) << std::endl;
        tm.loadPieceTexture(Piece::WHITE | pieceType);
        tm.loadPieceTexture(Piece::BLACK | pieceType);
    }
}

void displayPiecesOnBoard(Board& board, TextureManager& tm, sf::RenderWindow& window) {

    using namespace sf;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Vector2f piecePosition((x * SQUARE_SIZE), (y * SQUARE_SIZE));

            if (board.getPiece(x, y) != 0) {
                if (tm.has(board.getPiece(x, y))) {
                    Sprite pieceSprite(tm.getTexture(board.getPiece(x, y)));
                    pieceSprite.setPosition(piecePosition);
                    pieceSprite.setScale(Vector2f(.022 * SQUARE_SIZE, .022 * SQUARE_SIZE));
                    window.draw(pieceSprite);
                }
            }
        }
    }
}