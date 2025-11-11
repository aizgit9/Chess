#include "piece.hpp"
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once

class TextureManager {


private:

    std::unordered_map<int, std::unique_ptr<sf::Texture>> textures;

public:

    bool loadPieceTexture(int pieceIndentity) {

        using namespace sf;

        int color = pieceIndentity & 0b11000;
        int type = pieceIndentity & 0b00111;

        std::string colorStr;
        std::string typeStr;

        if (color == Piece::WHITE) {
            colorStr = "white";
        }
        else if (color == Piece::BLACK) {
            colorStr = "black";
        }
        else {  
            std::cerr << "Invalid argument received in color selection: " << color << std::endl;
            return false;
        }

        switch (type)
        {
        case Piece::PAWN:
            typeStr = "pawn";
            break;
        case Piece::KNIGHT:
            typeStr = "knight";
            break;
        case Piece::BISHOP:
            typeStr = "bishop";
            break;
        case Piece::ROOK:
            typeStr = "rook";
            break;
        case Piece::QUEEN:
            typeStr = "queen";
            break;
        case Piece::KING:
            typeStr = "king";
            break;
        default:
            std::cerr << "Invalid argument received in piece selection: " << type << std::endl;
            return false;
        }

        std::string filename = "assets/" + colorStr + "_" + typeStr + ".png";

        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

        if (!texture->loadFromFile(filename)) {
            std::cerr << "Failed to load texture: " << filename << std::endl;
            return false;
        }

        textures[pieceIndentity] = std::move(texture);

        return true;
    }

    const sf::Texture& getTexture(int identity) const {
        return *textures.at(identity); // throws if not found
    }

    bool has(int identity) const {
        return textures.count(identity) > 0;
    }
};