#include "constants.h"
#include "structures.h"
#include <vector>

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

std::vector<Square*> Piece::MoveValidator(){
    Square* temp = nullptr;
    boardSquares& squares = board->squares;
    int piece_i = place->x / square_size;
    int piece_j = place->y / square_size;
    if (type == "pawn" && color == "white"){
        if (piece_j == 0) return {};
        else return WhitePawnValidator(temp, squares, piece_i, piece_j);
    }
    else if (type == "pawn" && color == "black"){
        if (piece_j == 7) return {};
        else return BlackPawnValidator(temp, squares, piece_i, piece_j);
    }
    else if (type == "knight"){
        return KnightValidator(temp, squares, piece_i, piece_j);
    }
    else if (type == "bishop"){
        return BishopValidator(temp, squares, piece_i, piece_j);
    }
    else if (type == "rook"){
        return RookValidator(temp, squares, piece_i, piece_j);
    }
    else if (type == "queen"){
        return QueenValidator(temp, squares, piece_i, piece_j);
    }
    else {
        return KingValidator(temp, squares, piece_i, piece_j);
    }
}


std::vector<Square*> Piece::KnightValidator(Square* temp, boardSquares& squares, int piece_i, int piece_j){
    std::vector<Square*> validPositions;
    if (piece_i + 1 < 8){
        if (piece_j + 2 < 8 && emptyOrEnemy(color, squares[piece_i + 1][piece_j + 2])) validPositions.push_back(&squares[piece_i + 1][piece_j + 2]);
        if (piece_j - 2 >= 0 && emptyOrEnemy(color, squares[piece_i + 1][piece_j - 2])) validPositions.push_back(&squares[piece_i + 1][piece_j - 2]);
    }
    if (piece_i - 1 >= 0){
        if (piece_j + 2 < 8 && emptyOrEnemy(color, squares[piece_i - 1][piece_j + 2])) validPositions.push_back(&squares[piece_i - 1][piece_j + 2]);
        if (piece_j - 2 >= 0 && emptyOrEnemy(color, squares[piece_i - 1][piece_j - 2])) validPositions.push_back(&squares[piece_i - 1][piece_j - 2]);
    }
    if (piece_i + 2 < 8){
        if (piece_j + 1 < 8 && emptyOrEnemy(color, squares[piece_i + 2][piece_j + 1])) validPositions.push_back(&squares[piece_i + 2][piece_j + 1]);
        if (piece_j - 1 >= 0 && emptyOrEnemy(color, squares[piece_i + 2][piece_j - 1])) validPositions.push_back(&squares[piece_i + 2][piece_j - 1]);
    }
    if (piece_i - 2 >= 0){
        if (piece_j + 1 < 8 && emptyOrEnemy(color, squares[piece_i - 2][piece_j + 1])) validPositions.push_back(&squares[piece_i - 2][piece_j + 1]);
        if (piece_j - 1 >= 0 && emptyOrEnemy(color, squares[piece_i - 2][piece_j - 1])) validPositions.push_back(&squares[piece_i - 2][piece_j - 1]);
    }
    return validPositions;
}

std::vector<Square*> Piece::BlackPawnValidator(Square* temp, boardSquares& squares, int piece_i, int piece_j){
    std::vector<Square*> validPositions;
    temp = &squares[piece_i][piece_j + 1];
    if (temp->empty()) validPositions.push_back(temp);
    if (piece_j == 1) {
        temp = &squares[piece_i][3];
        if (temp->empty()) validPositions.push_back(temp);
    }

    if (piece_i > 0) {
        temp = &squares[piece_i - 1][piece_j + 1];
        if (!temp->empty() && temp->piece->color == "white") validPositions.push_back(temp);
    }

    if (piece_i < 7) {
        temp = &squares[piece_i + 1][piece_j + 1];
        if (!temp->empty() && temp->piece->color == "white") validPositions.push_back(temp);
    }
    return validPositions;
}

std::vector<Square*> Piece::WhitePawnValidator(Square* temp, boardSquares& squares, int piece_i, int piece_j){
    std::vector<Square*> validPositions;
    temp = &squares[piece_i][piece_j - 1];
    if (temp->empty()) validPositions.push_back(temp);
    if (piece_j == 6) {
        temp = &squares[piece_i][4];
        if (temp->empty()) validPositions.push_back(temp);
    }

    if (piece_i > 0) {
        temp = &squares[piece_i - 1][piece_j - 1];
        if (!temp->empty() && temp->piece->color == "black") validPositions.push_back(temp);
    }

    if (piece_i < 7) {
        temp = &squares[piece_i + 1][piece_j - 1];
        if (!temp->empty() && temp->piece->color == "black") validPositions.push_back(temp);
    }
    return validPositions;
}

std::vector<Square*> Piece::BishopValidator(Square* temp, boardSquares& squares, int piece_i, int piece_j){
    std::vector<Square*> validPositions;
    for (int i = 1; piece_i + i < 8 && piece_j + i < 8; i++){
        temp = &squares[piece_i + i][piece_j + i];
        if (emptyOrEnemy(color, *temp)){
            validPositions.push_back(temp);
            if (!temp->empty()) break;
        }
        else break;
    }
    for (int i = 1; piece_i + i < 8 && piece_j - i >= 0; i++){
        temp = &squares[piece_i + i][piece_j - i];
        if (emptyOrEnemy(color, *temp)){
            validPositions.push_back(temp);
            if (!temp->empty()) break;
        }
        else break;
    }
    for (int i = 1; piece_i - i >= 0 && piece_j + i < 8; i++){
        temp = &squares[piece_i - i][piece_j + i];
        if (emptyOrEnemy(color, *temp)){
            validPositions.push_back(temp);
            if (!temp->empty()) break;
        }
        else break;
    }
    for (int i = 1; piece_i - i >= 0 && piece_j - i >= 0; i++){
        temp = &squares[piece_i - i][piece_j - i];
        if (emptyOrEnemy(color, *temp)){
            validPositions.push_back(temp);
            if (!temp->empty()) break;
        }
        else break;
    }
    return validPositions;
}

std::vector<Square*> Piece::RookValidator(Square* temp, boardSquares& squares, int piece_i, int piece_j){
    std::vector<Square*> validPositions;
    for (int i = 1; piece_i + i < 8; i++){
        temp = &squares[piece_i + i][piece_j];
        if (emptyOrEnemy(color, *temp)){
            validPositions.push_back(temp);
            if (!temp->empty()) break;
        }
        else break;
    }
    for (int i = 1; piece_i - i >= 0; i++){
        temp = &squares[piece_i - i][piece_j];
        if (emptyOrEnemy(color, *temp)){
            validPositions.push_back(temp);
            if (!temp->empty()) break;
        }
        else break;
    }
    for (int i = 1; piece_j + i < 8; i++){
        temp = &squares[piece_i][piece_j + i];
        if (emptyOrEnemy(color, *temp)){
            validPositions.push_back(temp);
            if (!temp->empty()) break;
        }
        else break;
    }
    for (int i = 1; piece_j - i >= 0; i++){
        temp = &squares[piece_i][piece_j - i];
        if (emptyOrEnemy(color, *temp)){
            validPositions.push_back(temp);
            if (!temp->empty()) break;
        }
        else break;
    }
    return validPositions;
}

std::vector<Square*> Piece::QueenValidator(Square* temp, boardSquares& squares, int piece_i, int piece_j){
    std::vector<Square*> v1 = BishopValidator(temp, squares, piece_i, piece_j);
    std::vector<Square*> v2 = RookValidator(temp, squares, piece_i, piece_j);

    // Insert all items of v2 at the end of v1
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

std::vector<Square*> Piece::KingValidator(Square* temp, boardSquares& squares, int piece_i, int piece_j){
    std::vector<Square*> validPieces;
    // pushing all possible moves to valide Pieces
    if (piece_i + 1 < 8){
        temp = &squares[piece_i + 1][piece_j];
        if (emptyOrEnemy(color, *temp)) validPieces.push_back(temp);
        if (piece_j + 1 < 8){
            temp = &squares[piece_i + 1][piece_j + 1];
            if (emptyOrEnemy(color, *temp)) validPieces.push_back(temp);
        }
        if (piece_j - 1 >= 0){
            temp = &squares[piece_i + 1][piece_j - 1];
            if (emptyOrEnemy(color, *temp)) validPieces.push_back(temp);
        }
    }
    if (piece_i - 1 >= 0){
        temp = &squares[piece_i - 1][piece_j];
        if (emptyOrEnemy(color, *temp)) validPieces.push_back(temp);
        if (piece_j + 1 < 8){
            temp = &squares[piece_i - 1][piece_j + 1];
            if (emptyOrEnemy(color, *temp)) validPieces.push_back(temp);
        }
        if (piece_j - 1 >= 0){
            temp = &squares[piece_i - 1][piece_j - 1];
            if (emptyOrEnemy(color, *temp)) validPieces.push_back(temp);
        }
    }
    if (piece_j + 1 < 8){
        temp = &squares[piece_i][piece_j + 1];
        if (emptyOrEnemy(color, *temp)) validPieces.push_back(temp);
    }
    if (piece_j - 1 >= 0){
        temp = &squares[piece_i][piece_j - 1];
        if (emptyOrEnemy(color, *temp)) validPieces.push_back(temp);
    }
    if (color == "white"){
        for (Piece* piece: board->black_pieces){
            // special treat for pawns
            if (piece->type == "pawn"){
                int piece_i = piece->place->x / square_size;
                int piece_j = piece->place->y / square_size;
                if (piece_i > 0 && piece_j < 7) {
                    IfExistDelete(&squares[piece_i - 1][piece_j + 1], validPieces);
                }
                if (piece_i < 7 && piece_j < 7) {
                    IfExistDelete(&squares[piece_i + 1][piece_j + 1], validPieces);
                }
            }
            else if (piece->type == "king"){}
            else{
                for (Square* square: piece->MoveValidator()){
                    // find if the element in danger already existes in validPieces and removes it
                    IfExistDelete(square, validPieces);
                }
            }
        }
    }
    else{
        for (Piece* piece: board->white_pieces){
            // special treat for pawns
            if (piece->type == "pawn"){
                int piece_i = piece->place->x / square_size;
                int piece_j = piece->place->y / square_size;
                if (piece_i > 0 && piece_j > 0) {
                    IfExistDelete(&squares[piece_i - 1][piece_j - 1], validPieces);
                }
                if (piece_i < 7 && piece_j > 0) {
                    IfExistDelete(&squares[piece_i + 1][piece_j - 1], validPieces);
                }
            }
            else if (piece->type == "king"){}
            else{
                for (Square* square: piece->MoveValidator()){
                    // find if the element in danger already existes in validPieces and removes it
                    IfExistDelete(square, validPieces);
                }
            }
        }
    }
    return validPieces;
}
