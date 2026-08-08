#include "constants.h"
#include "structures.h"
#include <raylib.h>

int main(){
    InitWindow(screen_width, screen_height, "chess");
    SetTargetFPS(165);

    Board board;

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
