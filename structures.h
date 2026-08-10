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
using boardSquares = std::array<std::array<Square, 8>, 8>;

class Square{
    public:
        // attributes
        int x = 0;
        int y = 0;
        Color color = WHITE;
        Piece* piece = nullptr;
        bool validMove = false;
        // functions
        void Draw();
        Square(int x_coo, int y_coo, Color color_choice);
        Square() = default;
        bool empty();
};

class Board{
    public:
        // attributes
        boardSquares squares;
        std::vector<Piece*> white_pieces;
        std::vector<Piece*> black_pieces;
        std::pair<textureMap, textureMap> all_textures;
        Piece* selected = nullptr;
        // functions
        Board();
        void Draw();
        Square* mouseSquare();
        void Update();
        void CleanDeadPieces();
        void PieceMovement();
        void LegalMoves();
        void ClearValid();
};

class Piece{
    public:
        // attributes
        Texture2D texture;
        Board* board;
        Square* place = nullptr;
        std::string type;
        std::string color;
        bool alive = true;
        // functions
        Piece(std::string type_in, std::string color_in, Square* square, Board* board_in);
        void Draw();
        bool isMoveLegal(Square& to_square);
        void MoveValidator();
};


std::pair<textureMap, textureMap> TextureLoader();

Texture2D GetTexture(const std::string& path);

bool emptyOrEnemy(std::string color, Square square);
