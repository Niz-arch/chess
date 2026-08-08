#pragma once
#include <raylib.h>
#include "constants.h"
#include <array>
#include <string>

class Square;
class Board;
class Piece;

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
        Texture2D texture;
        Square* place = nullptr;
        // functions
        Piece(std::string image_path, Square* square);
        void Draw();
};
