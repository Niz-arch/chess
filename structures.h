#pragma once
#include <raylib.h>
#include "constants.h"
#include <array>

class Square{
    public:
        int x = 0;
        int y = 0;
        Color color = WHITE;
        void Draw();
        Square(int x_coo, int y_coo, Color color_choice);
        Square() = default;
};

class Board{
    public:
        std::array<std::array<Square, 8>, 8> squares;
        Board();
        void Draw();
};

class Piece{
    public:
        Image image;
};
