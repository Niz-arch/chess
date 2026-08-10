#include "constants.h"
#include "structures.h"

Board::Board(){
    Color color_of_choice;
    all_textures = TextureLoader();
    // board initialization
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            color_of_choice = (i + j)%2 == 0 ? WHITE : GRAY;
            squares[i][j] = Square(i*square_size, j*square_size, color_of_choice);
        }
    }
    // piece initialization
    std::string temp = "temp";
    for (int i = 0; i < 8; i++){
        if (i == 0 || i == 7)       temp = "rook";
        else if (i == 1 || i == 6)  temp = "knight";
        else if (i == 2 || i == 5)  temp = "bishop";
        else if (i == 3)            temp = "queen";
        else                        temp = "king";
        black_pieces.push_back(new Piece(temp, "black", &squares[i][0], this));
        white_pieces.push_back(new Piece(temp, "white", &squares[i][7], this));
    }

    for (int i = 0; i < 8; i++){
        black_pieces.push_back(new Piece("pawn", "black", &squares[i][1], this));
        white_pieces.push_back(new Piece("pawn", "white", &squares[i][6], this));
    }

}

void Board::Draw(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            squares[i][j].Draw();
        }
    }
}

Square* Board::mouseSquare(){
    return &squares[GetMouseX()/square_size][GetMouseY()/square_size];
}

void Board::Update(){
    CleanDeadPieces();
    ClearValid();
    LegalMoves();
    PieceMovement();
}

void Board::CleanDeadPieces(){
    for (int i = 0; i < white_pieces.size(); i++){
            if (!white_pieces[i]->alive){
                delete white_pieces[i];
                std::swap(white_pieces[i], white_pieces.back());
                white_pieces.pop_back();
                i--;
            };
        }
        for (int i = 0; i < black_pieces.size(); i++){
            if (!black_pieces[i]->alive){
                delete black_pieces[i];
                std::swap(black_pieces[i], black_pieces.back());
                black_pieces.pop_back();
                i--;
            };
        }
}

void Board::PieceMovement(){
    if (IsMouseButtonPressed(0)){
        Square* square = mouseSquare();

        if (selected == nullptr && !(mouseSquare()->empty())){
            selected = square->piece;
        }
        else if (selected != nullptr){
            if (selected->isMoveLegal(*square)){
                if (!square->empty()){
                    square->piece->alive = false;
                }
                selected->place->piece = nullptr;
                selected->place = square;
                square->piece = selected;
            }
            selected = nullptr;
        }
    }
}

void Board::LegalMoves(){
  if (selected != nullptr) {
      selected->MoveValidator();
  }
}

void Board::ClearValid(){
    if (selected == nullptr){
        for (std::array<Square, 8>& list: squares){
            for (Square& square: list){
                square.validMove = false;
            }
        }
    }
}
