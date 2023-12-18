#include "raylib.h"

int main (){
    const int wwidth {1000};
    const int wheight {500};
    
    InitWindow (wwidth, wheight, "Game window!");

    //acceleration due to gravity (pix/s)/s
    const int gravity {1'500};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = wwidth/2 - scarfyRec.width/2;
    scarfyPos.y = wheight - scarfyRec.height;

    // air jump
    bool isInAir {};
    
    // jump velocity(pixels/s)
    const int jumpVel {-700};
    
    int velocity {0};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        //Delta time
        const float dt {GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground (WHITE);

        //ground check
        if(scarfyPos.y >= (wheight - scarfyRec.height)){
            //rectangle on the ground
            velocity = 0;
            isInAir = false;
        }
        else{
            //apply gravity
            velocity += gravity*dt;
            isInAir = true;
        }
       
       //Jump check
        if(IsKeyDown(KEY_SPACE) && !isInAir){
            velocity += jumpVel;
        } 

        // update posititon
        scarfyPos.y += velocity*dt;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        
        
        //stop drawing
        EndDrawing ();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}