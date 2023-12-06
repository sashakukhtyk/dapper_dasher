#include "raylib.h"

int main (){
    
    //window dimensions
    int width {900};
    int height {500};
    InitWindow (width, height, "Oleksandr`s window");

    //circle coordinate
    int circle_x {175};
    int circle_y {100};

    //rectangle coordinates
    int axe_x {400};
    int axe_y {0};

    int direction {10};


    SetTargetFPS(60);
    while(WindowShouldClose() != true){
        BeginDrawing();
        ClearBackground (WHITE);

        // Game logic begins 

        DrawCircle (circle_x, circle_y, 25, BLUE);
        DrawRectangle (axe_x, axe_y, 50, 50, RED);

        //move the axe
        axe_y += direction;
        if (axe_y > 500 || axe_y < 0 )
        {
            direction = -direction;
        }

        //move circle
        if (IsKeyDown(KEY_D) && circle_x < 900)
        {
            circle_x += 10;
        }
        if (IsKeyDown(KEY_A) && circle_x > 0)
        {
            circle_x -= 10;
        }
        if (IsKeyDown(KEY_W) && circle_y > 0)
        {
            circle_y -= 10;
        }
        if (IsKeyDown(KEY_S) && circle_y <500)
        {
            circle_y += 10;
        }

        // Game logic ends
        EndDrawing ();
    }
}