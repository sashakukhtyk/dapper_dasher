#include "raylib.h"


struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main (){
    float windowDimensions[2];
    windowDimensions[0]= 1000;
    windowDimensions[1]= 500;

    InitWindow (windowDimensions[0],  windowDimensions[1], "Game window!");

    //acceleration due to gravity (pix/s)/s
    const int gravity {1'500};

    
    //nebula var
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfnebulae {10};
    //Anim neb 
    AnimData nebulae[sizeOfnebulae] = {};

    for ( int i = 0; i < sizeOfnebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 1.0/16.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }

    //nebula velocity pixels/s
    int nebVel {-200};

    //scarfy var
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y =  windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.runningTime = 0;
    scarfyData.updateTime = 1.0/12.0;

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
        if(scarfyData.pos.y >= (windowDimensions[1] - scarfyData.rec.height)){
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

        for (int i = 0; i < sizeOfnebulae; i++)
        {
            //update the position of each nebula
            nebulae[i].pos.x += nebVel*dt;
        }

        //update posititon
        scarfyData.pos.y += velocity*dt;

        // update scarfy`s animation 
        if(!isInAir){
            //update running time
            scarfyData.runningTime +=dt;
            if(scarfyData.runningTime>=scarfyData.updateTime){
            scarfyData.runningTime = 0.0;
            //update animation frame
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame++;
                if(scarfyData.frame>5){
                scarfyData.frame=0;
                }
             }
        }

        for(int i = 0; i < sizeOfnebulae; i++)
        {
            nebulae[i].runningTime +=dt;
            if (nebulae[i].runningTime>= nebulae[i].updateTime){
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7){
                    nebulae[i].frame = 0;
                } 
            }
        }

        for(int i = 0; i < sizeOfnebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        //scarfy tex
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        
        
        //stop drawing
        EndDrawing ();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}