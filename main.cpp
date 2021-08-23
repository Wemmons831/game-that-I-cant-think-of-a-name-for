
#include "include/raylib.h"
#include <iostream>
#include <string>
#include <stdlib.h>
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
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
    int ball_speed = 10;
    //  o = right , 1 = left
    int ball_direction = 0;
     Vector2 ball = {screenWidth/2 , screenHeight/2};
     int ball_rad = 10;
    int y_angle = 0;
    //scores
    int score = 0;
  
    //ui
    int font_size = 50;
    //colisons
    bool collision1 = false;
    //rectangles
    Rectangle rec1 = {};
    Rectangle ball_hitbox = {ball.x, ball.y, ball_rad *2, ball_rad *2};
    //power ups
    int powerup_spawn;
        // speed increes
            Texture2D powerup_speed = LoadTexture("sprites/speed.png");
            bool spawn_speed = false;
            Vector2 speed_pos = {0,0};
        // speed decrease
            Texture2D powerup_slow = LoadTexture("sprites/slow.png");
            bool spawn_slow = false;
            Vector2 slow_pos = {0,0};
        // paddle up
            Texture2D powerup_paddle_up = LoadTexture("sprites/paddle_up.png");
            bool spawn_paddle_up = false;
            Vector2 paddle_up_pos = {0,0};
        // paddle down
            Texture2D powerup_paddle_down = LoadTexture("sprites/paddle_down.png");
            bool spawn_paddle_down = false;
            Vector2 paddle_down_pos = {0,0};
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
           spawn_speed = false;
           spawn_slow = false;
           spawn_paddle_up = false;
           spawn_paddle_down = false;
           
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
        
        powerup_spawn = rand() %3000;
        switch (powerup_spawn)
        {
        case 53:
            
            if(spawn_speed == false){
            std::cout << "spawn";
            spawn_speed = true;
            speed_pos.x = rand () %screenWidth;
            if (speed_pos.x > screenWidth){
                speed_pos.x = screenWidth;
            }
            speed_pos.y = rand () %screenHeight;
            if (speed_pos.y > screenHeight){
                speed_pos.y = screenHeight;
            }
                std::cout << speed_pos.x << speed_pos.y;
            }
            break;
        case 785:
            if(spawn_slow == false){
            std::cout << "spawn";
            spawn_slow = true;
            slow_pos.x = rand () %screenWidth;
            if (slow_pos.x > screenWidth){
                slow_pos.x = screenWidth;
            }
            slow_pos.y = rand () %screenHeight;
            if (slow_pos.y > screenHeight){
                slow_pos.y = screenHeight;
            }
                std::cout << slow_pos.x << slow_pos.y;
            }
        case 892:
            if(spawn_paddle_up == false){
            std::cout << "spawn";
            spawn_paddle_up = true;
            paddle_up_pos.x = rand () %screenWidth;
            if (paddle_up_pos.x > screenWidth){
                paddle_up_pos.x = screenWidth;
            }
            paddle_up_pos.y = rand () %screenHeight;
            if (paddle_up_pos.y > screenHeight){
                paddle_up_pos.y = screenHeight;
            }
                std::cout << paddle_up_pos.x << paddle_up_pos.y;
            }
        case 26:
            if(spawn_paddle_down == false){
            std::cout << "spawn";
            spawn_paddle_down = true;
            paddle_down_pos.x = rand () %screenWidth;
            if (paddle_down_pos.x > screenWidth){
                paddle_down_pos.x = screenWidth;
            }
            paddle_down_pos.y = rand () %screenHeight;
            if (paddle_down_pos.y > screenHeight){
                paddle_down_pos.y = screenHeight;
            }
                std::cout << paddle_down_pos.x << paddle_down_pos.y;
            }
        default:
            break;
        }
        if(spawn_speed){
        
        bool speed_collison = CheckCollisionRecs({speed_pos.x,speed_pos.y,50,50}, ball_hitbox);
        if(speed_collison){
            ball_speed +=3;
            std::cout << "hit";
            spawn_speed = false;
        }
        }
        if(spawn_slow){
        
        bool slow_collison = CheckCollisionRecs({slow_pos.x,slow_pos.y,50,50}, ball_hitbox);
        if(slow_collison){
            ball_speed -=3;
            std::cout << "hit";
            spawn_slow = false;
            }
        }
        
        if(spawn_paddle_up){
        
        bool paddle_up_collison = CheckCollisionRecs({paddle_up_pos.x,paddle_up_pos.y,50,50}, ball_hitbox);
        if(paddle_up_collison){
            vertical_speed += 3;
            std::cout << "hit";
            spawn_paddle_up = false;
            }
        }

         if(spawn_paddle_down){
        
        bool paddle_down_collison = CheckCollisionRecs({paddle_down_pos.x,paddle_down_pos.y,50,50}, ball_hitbox);
        if(paddle_down_collison){
            vertical_speed -= 3;
            std::cout << "hit";
            spawn_paddle_down = false;
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
        

        if (spawn_speed){
            DrawTexture(powerup_speed, speed_pos.x - powerup_speed.width/2, speed_pos.y - powerup_speed.height/2, WHITE);
        }
        if (spawn_slow){
            DrawTexture(powerup_slow, slow_pos.x - powerup_slow.width/2, slow_pos.y - powerup_slow.height/2, WHITE);
        }
        if (spawn_paddle_up){
            DrawTexture(powerup_paddle_up, paddle_up_pos.x - powerup_paddle_up.width/2, paddle_up_pos.y - powerup_paddle_up.height/2, WHITE);
        }
        if (spawn_paddle_down){
            DrawTexture(powerup_paddle_down, paddle_down_pos.x - powerup_paddle_down.width/2, paddle_down_pos.y - powerup_paddle_down.height/2, WHITE);
        }
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
