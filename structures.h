#pragma once
#include <raylib.h>
#include "constants.h"
#include <array>
#include <string>
#include <unordered_map>
#include <utility>

class Square;
class Board;
class Piece;


using textureMap = std::unordered_map<std::string, Texture2D>;

class Square{
    public:
        // attributes
        int x = 0;
        int y = 0;
        Color color = WHITE;
        Piece* piece = nullptr;
        // functions
        void Draw();
        Square(int x_coo, int y_coo, Color color_choice);
        Square() = default;
};

class Board{
    public:
        // attributes
        std::array<std::array<Square, 8>, 8> squares;
        // functions
        Board();
        void Draw();
};

class Piece{
    public:
        // attributes
        Texture2D texture = {};
        Square* place = nullptr;
        // functions
        Piece(Texture2D texture_in, Square* square);
        void Draw();
};

std::pair<textureMap, textureMap> TextureLoader();
Texture2D GetTexture(const std::string& path);
