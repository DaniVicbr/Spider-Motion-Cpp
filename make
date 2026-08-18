#include "raylib.h"
#include "raymath.h"

//Defines

#define SPIDER_BASE_SIZE	20.0f
#define PLAYER_SPEED		5.0f

//Type and Structure

typedef struct Spider {
	Vector2 position;
	Vector2 speed;
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
    float turnSpeed = 4.0f;  // Velocidade de rotação (graus por frame)
    float moveSpeed = 4.0f;  // Velocidade de movimento
    // 1. Rotação (Girar para esquerda / direita)
    if (IsKeyDown(KEY_A)) spider.rotation -= turnSpeed;
    if (IsKeyDown(KEY_D)) spider.rotation += turnSpeed;
    // Converte o ângulo atual para radianos
    float rad = spider.rotation * DEG2RAD;
    // 2. Movimento para frente e para trás na direção do ângulo
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

        for (int i = 0; i < screenWidth; i += 50) DrawLine(i, 0, i, screenHeight, LIGHTGRAY);
		for (int i = 0; i < screenHeight; i += 50) DrawLine(0, i, screenWidth, i, LIGHTGRAY);
             	
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

       	
		DrawTriangle(v1, v2, v3, RED);

		// Show spider vertices 
		DrawCircleV(v1, 3, BLUE);
		DrawCircleV(v2, 3, GREEN);
		DrawCircleV(v3, 3, GREEN);

        ClearBackground(RAYWHITE);
        DrawText("Use W,A,S,D para movimentação", 10, 10, 20, DARKGRAY);

		

	EndDrawing();
}
