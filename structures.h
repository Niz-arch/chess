#pragma once
#include <raylib.h>
#include "constants.h"
#include <array>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Square;
class Board;
class Piece;

using textureMap = std::unordered_map<std::string, Texture2D>;
// enum class pieces {PAWN1, PAWN2, PAWN3, PAWN4, PAWN5, PAWN6, PAWN7, PAWN8,
//                   ROOK1, KNIGHT1, BISHOP1, QUEEN, KING, BISHOP2, KNIGHT2, ROOK2
// };
// probably wont use them


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
        std::vector<Piece*> white_pieces;
        std::vector<Piece*> black_pieces;
        std::pair<textureMap, textureMap> all_textures;
        // functions
        Board();
        void Draw();
        Square* mouseSquare();
        void Update();
};

class Piece{
    public:
        // attributes
        Texture2D texture;
        Board* board;
        Square* place = nullptr;
        bool isSelected = false;
        std::string type;
        std::string color;
        bool alive = true;
        // functions
        Piece(std::string type_in, std::string color_in, Square* square, Board* board_in);
        void Draw();
        void Update();
};


std::pair<textureMap, textureMap> TextureLoader();

Texture2D GetTexture(const std::string& path);

bool isMoveLegale(Square& piece_square, Square& go_square);
