#include <raylib.h>
#include "constants.h"
#include "structures.h"

Board board;

int main(){
    InitWindow(screen_width, screen_height, "chess");
    SetTargetFPS(165);

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);

        // Updating
        // Drawing
        board.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
