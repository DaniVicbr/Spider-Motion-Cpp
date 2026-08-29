#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector> 


//Defines
#define SPIDER_BASE_SIZE	15.0f
#define SPIDER_SPEED		5.0f

//Type and Structure
typedef struct Spider {
	Vector2 position;
	Vector2 speed;
    Vector2 spiderCenter;
	float acceleration;
	float rotation; 
	Vector3 collider;
} Spider;

//Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 600;
static Spider spider = {};
static float spiderHeight = 0.0f;
/*static float spiderBase = 30.0f;*/
static std::vector<Vector2> rastrov1;

//Module Functions Declaration (local)
static void UpdateGame(void);
static void InitGame(void);
static void DrawGame(void);

//Main entry point
int main(void) {
	InitWindow(screenWidth, screenHeight, "Spider Simulator");
	SetTargetFPS(60);

	InitGame();
	
	while (!WindowShouldClose()) {
		UpdateGame();
		DrawGame();
	}

	CloseWindow();
	return 0;
}

void InitGame(void) 
{
	spider.position = (Vector2){(float)screenWidth/2, (float)screenHeight/2};
	spider.speed = (Vector2){4.0f, 4.0f};
	spider.rotation = 0.0f;
	spiderHeight = (SPIDER_BASE_SIZE/2)/tanf(20*DEG2RAD); 
}

void UpdateGame(void)
{
    float turnSpeed = 5.0f;  
    float moveSpeed = 3.0f;
    float rad = spider.rotation * DEG2RAD;

    if (IsKeyDown(KEY_A)) spider.rotation -= turnSpeed;
    if (IsKeyDown(KEY_D)) spider.rotation += turnSpeed;
     
    if (IsKeyDown(KEY_W)) {
        spider.position.x += sinf(rad) * moveSpeed;
        spider.position.y -= cosf(rad) * moveSpeed;
        
    }
    if (IsKeyDown(KEY_S)) {
        spider.position.x -= sinf(rad) * moveSpeed;
        spider.position.y += cosf(rad) * moveSpeed;
    }
}

void DrawGame(void) 
{
	BeginDrawing();

        ClearBackground(BLACK);

        /*for (int i = 0; i < screenWidth; i += 50) DrawLine(i, 0, i, screenHeight, LIGHTGRAY);
		for (int i = 0; i < screenHeight; i += 50) DrawLine(0, i, screenWidth, i, LIGHTGRAY);*/
             	
        float rad = spider.rotation * DEG2RAD;
        float sinRot = sinf(rad);
        float cosRot = cosf(rad);

        Vector2 v1 = {
            spider.position.x + sinRot * spiderHeight,
            spider.position.y - cosRot * spiderHeight
        };

         Vector2 v2 = {
            spider.position.x - cosRot * (SPIDER_BASE_SIZE / 2.0f),
            spider.position.y - sinRot * (SPIDER_BASE_SIZE / 2.0f)
        };

        Vector2 v3 = {
            spider.position.x + cosRot * (SPIDER_BASE_SIZE / 2.0f),
            spider.position.y + sinRot * (SPIDER_BASE_SIZE / 2.0f) 
        };

        Vector2 spiderCephalothorax {
            spider.position.x - sinRot * 16.0f,
            spider.position.y + cosRot * 16.0f
        };

        Vector2 spiderAbdomen {
            spider.position.x - sinRot * 45.0f,
            spider.position.y + cosRot * 45.0f
        };

        Vector2 centerSpider {
            spider.position.x - sinRot * 33.0f,
            spider.position.y + cosRot * 33.0f
        };

        Vector2 webPoint {
            spider.position.x - sinRot * 63.0f,
            spider.position.y + cosRot * 63.0f
        };

          //Vector Tracking: 
        rastrov1.emplace_back(webPoint);
        if (rastrov1.size() > 250) {
           rastrov1.erase(rastrov1.begin()); 
        };

        for(int i = 0; i < rastrov1.size(); i++) {
            DrawCircleV(rastrov1[i], 4, WHITE);
        }

	
		DrawTriangle(v1, v2, v3, BROWN);
        DrawPoly(spiderCephalothorax, 6, 20, spider.rotation, BROWN);

        DrawCircleV(spiderAbdomen, 25, BROWN);
 
		DrawCircleV(v1, 3, BLUE);
		DrawCircleV(v2, 3, GREEN);
		DrawCircleV(v3, 3, GREEN);

        //Central Point starting from v1:
        
        DrawCircleV(centerSpider, 10, BLUE);

        DrawLineV(centerSpider, Vector2{(spider.position.x + cosRot) , (spider.position.y - sinRot)}, RED); 
       
        //std::cout << "v1.x: "<<v1.x <<" | v2.y:"<<v1.y<< "\n";
        
      
        DrawText("Use W,A,S,D para movimentação", 10, 10, 20, WHITE);

	EndDrawing();
}


