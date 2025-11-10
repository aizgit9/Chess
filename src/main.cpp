#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "board.hpp"
#include <string>
#include <iostream>

void createBoardGraphic(sf::RenderWindow& window);
sf::Texture loadTexture(int piece);


const sf::Color LIGHT_SQUARE_COLOR(220, 195, 141);
const sf::Color DARK_SQUARE_COLOR(75, 124, 87);
const int SQUARE_SIZE = 100;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        createBoardGraphic(window);

        window.display();
    }
}

void createBoardGraphic(sf::RenderWindow& window) {

    using namespace sf;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {

            Color squareColor(0,0,0);
            Vector2f squarePosition(x * SQUARE_SIZE, y * SQUARE_SIZE);

            // Light Squares
            if ((x + y) % 2 == 0) {
                squareColor = LIGHT_SQUARE_COLOR;
            }

            // Dark Squares
            if ((x + y) % 2 == 1) {
                squareColor = DARK_SQUARE_COLOR;
            }

            RectangleShape square(Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            square.setFillColor(squareColor);
            square.setPosition(squarePosition);

            window.draw(square);
        }
    }
}

sf::Texture loadTexture(int piece) {

    using namespace sf;

    int color = piece & 0b11000;
    int type = piece & 0b00111;

    std::string colorStr;
    std::string typeStr;

    if (color == 8) {
        colorStr = "white";
    }
    else if (color ==  16) {
        colorStr = "black";
    }

    switch (type)
    {
    case 1:
        typeStr = "pawn";
        break;
    case 2:
        typeStr = "knight";
        break;
    case 3:
        typeStr = "bishop";
        break;
    case 4:
        typeStr = "rook";
        break;
    case 5:
        typeStr = "queen";
        break;
    case 6:
        typeStr = "king";
        break;
    default:
        // Error
        break;
    }

    std::string filename = "assets/" + colorStr + "_" + typeStr + ".png";

    Texture texture;

    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }

    return texture;
}