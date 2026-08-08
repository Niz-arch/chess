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
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            color_of_choice = (i + j)%2 == 0 ? WHITE : BLACK;
            squares[i][j] = Square(i*square_size, j*square_size, color_of_choice);
        }
    }
}

void Board::Draw(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            squares[i][j].Draw();
        }
    }
}

// pieces implementations
Piece::Piece(Texture2D texture_in, Square* square):texture(texture_in), place(square){
    square->piece = this;
}

void Piece::Draw(){
    DrawTexture(texture, place->x, place->y, WHITE);
}

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
