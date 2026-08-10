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
    if (type == "pawn" && color == "white"){
        if (go_square.x == place->x && go_square.y + square_size == place->y && go_square.piece == nullptr)                          return true;
        else if (abs(go_square.x - place->x) == square_size && go_square.y + square_size == place->y && go_square.piece != nullptr)  return true;
        else if (go_square.y == square_size*3 && go_square.x == place->x && place->y == square_size*6 && go_square.piece == nullptr) return true;
        else                                                                                                                         return false;
    }
    else return true;
}
