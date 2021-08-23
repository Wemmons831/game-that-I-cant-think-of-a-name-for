#include "include/raylib.h"
#include <iostream>
#include <string>
#include <stdlib.h>
const int screenWidth = 1280;
const int screenHeight = 720;
 int ball_speed = 10;
//  o = right , 1 = left
int ball_direction = 0;
Vector2 ball = {screenWidth/2 , screenHeight/2};
int ball_rad = 10;
int y_angle = 0;
Rectangle ball_hitbox = {ball.x, ball.y, ball_rad *2, ball_rad *2};
struct powerup{
    Texture2D texture;
    bool spawn = false;
    Vector2 pos;
    bool collison = false;
    std::string name;
};
void selection(powerup& selected)
    {
        if(selected.spawn == false){
            std::cout << "spawn";
            selected.spawn = true;
            selected.pos.x = rand () %screenWidth;
            if (selected.pos.x > screenWidth){
                selected.pos.x = screenWidth;
            }
            selected.pos.y = rand () %screenHeight;
            if (selected.pos.y > screenHeight){
                selected.pos.y = screenHeight;
            }
                std::cout << selected.pos.x << selected.pos.y;
                std::cout << selected.name;
                
            }
            
    }

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    Image icon = LoadImage("sprites/icon.png");
    //audio
    InitWindow(screenWidth, screenHeight, "GAME THAT I CANT THINK OF A NAME FOR");
    
    SetWindowIcon(icon);
    InitAudioDevice();              // Initialize audio device

    //Sound point1 = LoadSound("audio/point.wav");
    // start x , start y , width , hieght 
    int rec_player1_pos_y = screenHeight/2 - 100;
    int vertical_speed = 5;
    int rectangle_height = 200;
    bool wrapping = false;
    //ball
   
    //scores
    int score = 0;
  
    //ui
    int font_size = 50;
    //colisons
    bool collision1 = false;
    //rectangles
    Rectangle rec1 = {};
  
    //power ups
    int powerup_spawn;
    
    powerup speed;
    speed.texture = LoadTexture("sprites/speed.png");
    speed.name = "speed";
    powerup slow;
    slow.texture = LoadTexture("sprites/slow.png");
    slow.name = "slow";
    powerup paddle_up;
    paddle_up.texture = LoadTexture("sprites/paddle_up.png");
    paddle_up.name = "paddle_up";
    powerup paddle_down;
    paddle_down.texture = LoadTexture("sprites/paddle_down.png");
    paddle_down.name = "paddle_down";
    
    



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if(wrapping == false){

            if (IsKeyDown(KEY_UP)){
                if(rec_player1_pos_y <= 0){
                    
                }
                else{
                    rec_player1_pos_y -= vertical_speed;
                }  
            }

            if (IsKeyDown(KEY_DOWN)){
                if(rec_player1_pos_y + rectangle_height >= screenHeight){
                    
                }
                else{
                    rec_player1_pos_y += vertical_speed;
                }    
            }
        }
        //lose
        if (ball.x <= 0){
           ball = {screenWidth/2 , screenHeight/2};
           y_angle = 0;
           score = 0;
           ball_speed = 10;
           vertical_speed = 5;
           speed.spawn = false;
           slow.spawn = false;
           paddle_up.spawn = false;
           paddle_down.spawn = false;
           
        }
        rec1 = {25, rec_player1_pos_y , 50 ,rectangle_height};
        ball_hitbox = {ball.x - ball_rad, ball.y - ball_rad, ball_rad * 2,  ball_rad *2};
        if (ball.x >= screenWidth){
            ball_direction = 0;
            
            //PlaySound(point1);
        }
        if (ball.y <= 0){
            y_angle *= -1;
        }
        if (ball.y >= screenHeight){
            y_angle *= -1;
        }

        
        collision1 = CheckCollisionRecs(rec1, ball_hitbox);
        if (collision1){
            ball_direction = 1;
            y_angle = rand() %10 + 1;
            y_angle -= 5;
            score +=1;
            
           
        }
        //ball movment
        if(ball_direction == 0){
            ball.x -= ball_speed;
            ball.y += y_angle;

        }
        else{
            ball.x += ball_speed;
            ball.y += y_angle;
        }
        
        powerup_spawn = rand() %2000;
       switch (powerup_spawn)
        {
        case 53:
            std::cout << "called";
            selection(speed);
            
            break;
        case 785:
            selection(slow);
            std::cout << "called";
        case 892:
          selection(paddle_up);
          std::cout << "called";
           
        case 26:
            selection(paddle_down);
            std::cout << "called";
        default:
            break;
        }
        if(speed.spawn){
        speed.collison =  CheckCollisionRecs({speed.pos.x,speed.pos.y,50,50}, ball_hitbox);
        if(speed.collison){
            ball_speed +=3;
            std::cout << "hit";
            speed.spawn = false;
        }
        }
        if(slow.spawn){
        slow.collison = CheckCollisionRecs({slow.pos.x,slow.pos.y,50,50}, ball_hitbox);
        if(slow.collison){
            ball_speed -=3;
            std::cout << "hit";
            slow.spawn = false;
            }
        }
        
        if(paddle_up.collison){
            paddle_up.collison = CheckCollisionRecs({paddle_up.pos.x,paddle_up.pos.y,50,50}, ball_hitbox);
        if(paddle_up.collison){
            vertical_speed += 3;
            std::cout << "hit";
            paddle_up.spawn = false;
            }
        }

         if(paddle_down.spawn){
            paddle_down.collison = CheckCollisionRecs({paddle_down.pos.x,paddle_down.pos.y,50,50}, ball_hitbox);
        if(paddle_down.collison){
            vertical_speed -= 3;
            std::cout << "hit";
            paddle_down.spawn = false;
            }
        }
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY); 
        DrawRectangleRec(rec1, WHITE);
        //DrawRectangleRec(ball_hitbox,RED);
        DrawCircleV(ball, ball_rad , WHITE);
       
        //definatly better way 
        std::string s = std::to_string(score);
        char const *score1 = s.c_str();
        std::string t = std::to_string(ball_speed);
        char const *ball_speed2 = t.c_str();
        std::string z = std::to_string(vertical_speed);
        char const *vertical_speed2 = z.c_str();
        
        


        DrawText(score1, 200 ,50, font_size, WHITE);
        DrawText(ball_speed2, 50,50, font_size, WHITE);
        DrawText(vertical_speed2, 350,50, font_size, WHITE);
        

        if (speed.spawn){
            DrawTexture(speed.texture, speed.pos.x - speed.texture.width/2, speed.pos.y - speed.texture.height/2, WHITE);
        }
        if (slow.spawn){
            DrawTexture(slow.texture, slow.pos.x - slow.texture.width/2, slow.pos.y - slow.texture.height/2, WHITE);
        }
        if (paddle_up.spawn){
            DrawTexture(paddle_up.texture, paddle_up.pos.x - paddle_up.texture.width/2, paddle_up.pos.y - paddle_up.texture.height/2, WHITE);
        }
        if (paddle_down.spawn){
            DrawTexture(paddle_down.texture, paddle_down.pos.x - paddle_down.texture.width/2, paddle_down.pos.y - paddle_down.texture.height/2, WHITE);
        }
        
        EndDrawing();
       
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
