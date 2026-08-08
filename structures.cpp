#include "structures.h"
#include "constants.h"
#include <raylib.h>

// square class implementations
void Square::Draw(){
    DrawRectangle(x, y, square_size, square_size, color);
}

Square::Square(int x_coo, int y_coo, Color color_choice): x(x_coo), y(y_coo), color(color_choice){}


// board implementations
Board::Board(){
    Color color_of_choice;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            color_of_choice = (i + j)%2 == 0 ? WHITE : BLACK;
            this->squares[i][j] = Square(i*square_size, j*square_size, color_of_choice);
        }
    }
}

void Board::Draw(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            this->squares[i][j].Draw();
        }
    }
}
