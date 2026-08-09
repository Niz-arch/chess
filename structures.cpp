#include "structures.h"
#include "constants.h"
#include <raylib.h>

// square class implementations
void Square::Draw(){
    DrawRectangle(x, y, square_size, square_size, color);
    if (piece != nullptr){
        piece->Draw();
    }
}

Square::Square(int x_coo, int y_coo, Color color_choice): x(x_coo), y(y_coo), color(color_choice){}


// board implementations
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

}

// pieces implementations
Piece::Piece(std::string type_in, std::string color_in, Square* square, Board* board_in): type(type_in), color(color_in), place(square), board(board_in){
    square->piece = this;
    if (color == "white")    texture = board->all_textures.first[type];
    else                     texture = board->all_textures.second[type];
}

void Piece::Draw(){
    DrawTexture(texture, place->x, place->y, WHITE);
}

void Piece::Update(){

}

// other functions
std::pair<textureMap, textureMap> TextureLoader(){
    textureMap white_pieces, black_pieces;
    white_pieces["pawn"] = GetTexture("pictures/white-pawn.png");
    white_pieces["knight"] = GetTexture("pictures/white-knight.png");
    white_pieces["bishop"] = GetTexture("pictures/white-bishop.png");
    white_pieces["rook"] = GetTexture("pictures/white-rook.png");
    white_pieces["queen"] = GetTexture("pictures/white-queen.png");
    white_pieces["king"] = GetTexture("pictures/white-king.png");
    black_pieces["pawn"] = GetTexture("pictures/black-pawn.png");
    black_pieces["knight"] = GetTexture("pictures/black-knight.png");
    black_pieces["bishop"] = GetTexture("pictures/black-bishop.png");
    black_pieces["rook"] = GetTexture("pictures/black-rook.png");
    black_pieces["queen"] = GetTexture("pictures/black-queen.png");
    black_pieces["king"] = GetTexture("pictures/black-king.png");
    return {white_pieces, black_pieces};
}

Texture2D GetTexture(const std::string& path){
    Image image = LoadImage(path.c_str());
    ImageResize(&image, square_size, square_size);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}
