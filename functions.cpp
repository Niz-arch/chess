#include "structures.h"

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
