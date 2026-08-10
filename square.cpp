#include "structures.h"

void Square::Draw(){
    if (piece != nullptr && piece == piece->board->selected)  DrawRectangle(x, y, square_size, square_size, PINK);
    else                                                      DrawRectangle(x, y, square_size, square_size, color);
    if (piece != nullptr)                                     piece->Draw();
}

Square::Square(int x_coo, int y_coo, Color color_choice): x(x_coo), y(y_coo), color(color_choice){}

bool Square::empty(){
    return piece == nullptr;
}
