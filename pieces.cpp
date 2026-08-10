#include "constants.h"
#include "structures.h"

Piece::Piece(std::string type_in, std::string color_in, Square* square, Board* board_in): type(type_in), color(color_in), place(square), board(board_in){
    square->piece = this;
    if (color == "white")    texture = board->all_textures.first[type];
    else                     texture = board->all_textures.second[type];
}

void Piece::Draw(){
    DrawTexture(texture, place->x, place->y, WHITE);
}

bool Piece::isMoveLegal(Square& go_square){
    // pawn
    return go_square.validMove;
}

void Piece::MoveValidator(){
    Square* temp = nullptr;
    boardSquares& squares = board->squares;
    int piece_i = place->x / square_size;
    int piece_j = place->y / square_size;
    if (type == "pawn" && color == "white" && piece_j > 0){
        temp = &squares[piece_i][piece_j - 1];
        if (temp->empty()) temp->validMove = true;

        if (piece_j == 6) {
            temp = &squares[piece_i][4];
            if (temp->empty()) temp->validMove = true;
        }

        if (piece_i > 0) {
            temp = &squares[piece_i - 1][piece_j - 1];
            if (!temp->empty() && temp->piece->color == "black") temp->validMove = true;
        }

        if (piece_i < 7) {
            temp = &squares[piece_i + 1][piece_j - 1];
            if (!temp->empty() && temp->piece->color == "black") temp->validMove = true;
        }
    }
    if (type == "pawn" && color == "black" && piece_j < 7){
        temp = &squares[piece_i][piece_j + 1];
        if (temp->empty()) temp->validMove = true;

        if (piece_j == 1) {
            temp = &squares[piece_i][3];
            if (temp->empty()) temp->validMove = true;
        }

        if (piece_i > 0) {
            temp = &squares[piece_i - 1][piece_j + 1];
            if (!temp->empty() && temp->piece->color == "white") temp->validMove = true;
        }

        if (piece_i < 7) {
            temp = &squares[piece_i + 1][piece_j + 1];
            if (!temp->empty() && temp->piece->color == "white") temp->validMove = true;
        }
    }
    if (type == "knight"){
        int x = 0, y = 0;
        if (piece_i + 1 < 8){
            if (piece_j + 2 < 8 && emptyOrEnemy(color, squares[piece_i + 1][piece_j + 2])) squares[piece_i + 1][piece_j + 2].validMove = true;
            if (piece_j - 2 > 0 && emptyOrEnemy(color, squares[piece_i + 1][piece_j - 2])) squares[piece_i + 1][piece_j - 2].validMove = true;
        }
        if (piece_i - 1 > 0){
            if (piece_j + 2 < 8 && emptyOrEnemy(color, squares[piece_i - 1][piece_j + 2])) squares[piece_i - 1][piece_j + 2].validMove = true;
            if (piece_j - 2 > 0 && emptyOrEnemy(color, squares[piece_i - 1][piece_j - 2])) squares[piece_i - 1][piece_j - 2].validMove = true;
        }
        if (piece_i + 2 < 8){
            if (piece_j + 1 < 8 && emptyOrEnemy(color, squares[piece_i + 2][piece_j + 1])) squares[piece_i + 2][piece_j + 1].validMove = true;
            if (piece_j - 1 > 0 && emptyOrEnemy(color, squares[piece_i + 2][piece_j - 1])) squares[piece_i + 2][piece_j - 1].validMove = true;
        }
        if (piece_i - 2 > 0){
            if (piece_j + 1 < 8 && emptyOrEnemy(color, squares[piece_i - 2][piece_j + 1])) squares[piece_i - 2][piece_j + 1].validMove = true;
            if (piece_j - 1 > 0 && emptyOrEnemy(color, squares[piece_i - 2][piece_j - 1])) squares[piece_i - 2][piece_j - 1].validMove = true;
        }
    }
}
