#include "raylib.h"

int main (){
    const int wwidth {1000};
    const int wheight {500};
    
    InitWindow (wwidth, wheight, "Game window!");

    //acceleration due to gravity (pix/s)/s
    const int gravity {1'500};

    
    //nebula var
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0f, 0.0f, static_cast<float>(nebula.width)/8, static_cast<float>(nebula.height)/8};
    Vector2 nebulaPos{wwidth, wheight - nebulaRec.height};

    Rectangle neb2Rec {0.0f, 0.0f, static_cast<float>(nebula.width)/8, static_cast<float>(nebula.height)/8};
    Vector2 neb2Pos {wwidth + 500, wheight - nebulaRec.height};

    //neb animation frame
    int nebFrame {0};
    const float nebUpdateTime {1.0/12};
    float nebRunningTime {};

    int neb2Frame {};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime {};

    //nebula velocity pixels/s
    int nebVel {-200};

    //scarfy var
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = wwidth/2 - scarfyRec.width/2;
    scarfyPos.y = wheight - scarfyRec.height;

    //animation frame
    int frame {0};

    // animation speed
    const float updateTime {1.0/12.0};
    float runningTime {};

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

        //update neb pos
        nebulaPos.x += nebVel*dt;
        neb2Pos.x += nebVel*dt;

        //update posititon
        scarfyPos.y += velocity*dt;

        // update scarfy`s animation 
        if(!isInAir){
            //update running time
            runningTime +=dt;
            if(runningTime>=updateTime){
            runningTime = 0.0;
            //update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
                if(frame>5){
                frame=0;
                }
             }
        }

        //neb animation update
        nebRunningTime +=dt;
        if (nebRunningTime>= nebUpdateTime){
            nebRunningTime = 0.0;
            nebulaRec.x = nebFrame * nebulaRec.width;
            nebFrame++;
            if (nebFrame > 7){
                nebFrame = 0;
            }
        }
         neb2RunningTime +=dt;
        if (neb2RunningTime>= neb2UpdateTime){
            neb2RunningTime = 0.0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7){
                neb2Frame = 0;
            }
        }
        //neb tex
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        // neb2 texture 
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);
        
        //scarfy tex
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        
        
        //stop drawing
        EndDrawing ();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}