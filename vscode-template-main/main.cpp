#include "raylib.h"

int main (){
    int width;
    width = 350;
    
    InitWindow (width, 200, "Oleksandr`s window");

    while(true){
        BeginDrawing();
        ClearBackground (GREEN);
        EndDrawing ();
    }
}