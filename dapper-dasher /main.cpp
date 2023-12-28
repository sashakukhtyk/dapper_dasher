#include "raylib.h"


struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData (AnimData data, float deltaTime, int maxFrame)
{
    //update running time
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main (){
    float windowDimensions[2];
    windowDimensions[0]= 1024;
    windowDimensions[1]= 760;

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
        nebulae[i].pos.x = windowDimensions[0] + i * 500;
    }
    
    //creation of the finish line
    float finishLine {nebulae[sizeOfnebulae - 1].pos.x };

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
    const int jumpVel {-800};
    
    int velocity {0};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX {};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX {};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX {};

    bool collision{};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        //Delta time
        const float dt {GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground (WHITE);

        //update background
        bgX -= 20*dt;
        if(bgX <= -background.width*2)
        {
            bgX = 0.0;
        }
        
        mgX -= 40*dt;
        if(mgX <= -midground.width*2)
        {
            mgX = 0.0;
        }
        
        fgX -= 80*dt;
        if(fgX <= -midground.width*2)
        {
            fgX = 0.0;
        }

        //draw the background
        Vector2 bg1Pos {bgX,0.0};
        DrawTextureEx(background,bg1Pos, 0.0, 4.0, WHITE);
        Vector2 bg2Pos {bgX + background.width*2, 0.0};
        DrawTextureEx(background,bg2Pos, 0.0, 4.0, WHITE);
        
        Vector2 mg1Pos {mgX,0.0};
        DrawTextureEx(midground,mg1Pos, 0.0, 4.0, WHITE);
        Vector2 mg2Pos {mgX + midground.width*2, 0.0};
        DrawTextureEx(midground,mg2Pos, 0.0, 4.0, WHITE);

        Vector2 fg1Pos {fgX,0.0};
        DrawTextureEx(foreground,fg1Pos, 0.0, 4.0, WHITE);
        Vector2 fg2Pos {fgX + foreground.width*2, 0.0};
        DrawTextureEx(foreground,fg2Pos, 0.0, 4.0, WHITE);

        //ground check
        if(isOnGround(scarfyData, windowDimensions[1])){
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

        //update finish line position 
        finishLine += nebVel*dt;

        //update posititon
        scarfyData.pos.y += velocity*dt;

        // update scarfy`s animation 
        if(!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dt, 5);
        }

        for(int i = 0; i < sizeOfnebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i],dt,7);
        }

        // collision detection
        for(AnimData nebula : nebulae)
        {
            float pad {50};
            Rectangle nebRec
            {
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height -2*pad
            };
            Rectangle scarfyRec
            {
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if(CheckCollisionRecs(nebRec,scarfyRec))
            {
                collision = true;
            }
        }
        if(collision)
        {
            //lose the game
            DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2, 40,RED);
        }

        else if(scarfyData.pos.x >= finishLine)
        {
            // win the game
            DrawText("You win!", windowDimensions[0]/4, windowDimensions[1]/2, 40,GREEN);
        }

        else
        {
            for(int i = 0; i < sizeOfnebulae; i++)
            {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            //scarfy tex
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }
        
        //stop drawing
        EndDrawing ();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}