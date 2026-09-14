#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector> 

//Defines
#define SPIDER_BASE_SIZE	15.0f
#define SPIDER_SPEED		10.0f

//Type and Structure

typedef struct SpiderLeg {
    Vector2 footPoint;
    Vector2 kneePoint;  
    Vector2 rootPoint;
    Vector2 targetFootPoint;
    Vector2 oldFootPoint;
    Vector2 currentFoot;
    float legAngle; 
    float stepProgress;
    bool isStepping;
    bool isMoving;
    float footToTargetPoint;
       
} SpiderLeg;

typedef struct Spider {
	Vector2 position;
	Vector2 speed;
    Vector2 spiderCenter;
	float acceleration;
	float rotation; 
	Vector3 collider;
    SpiderLeg legs[8];
} Spider;

//Global Variables Declaration
static const int screenWidth = 1280;
static const int screenHeight = 720;
static Spider spider = {};
static float spiderHeight = 0.0f;
/*static float spiderBase = 30.0f;*/
static std::vector<Vector2> rastrov1;

//Module Functions Declaration (local)
static void UpdateGame(void);
static void InitGame(void);
static void DrawGame(void);

bool isWeb = false;

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

    //Spider legs angle:

    spider.legs[0].legAngle = 30.0f;
    spider.legs[1].legAngle = 70.0f;
    spider.legs[2].legAngle = 110.0f;
    spider.legs[3].legAngle = 150.0f;

    spider.legs[4].legAngle = 330.0f;
    spider.legs[5].legAngle = 290.0f;
    spider.legs[6].legAngle = 250.0f;
    spider.legs[7].legAngle = 210.0f;
 }

void UpdateGame(void)
{
    float turnSpeed = 4.0f;  
    float moveSpeed = 7.0f;
    float rad = spider.rotation * DEG2RAD;
    //float spiderLeg.legAngle; 
   
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

    isWeb = IsKeyDown(KEY_SPACE); 
}

void DrawGame(void) 
{
	BeginDrawing();

        ClearBackground(BLACK);

        //for (int i = 0; i < screenWidth; i += 50) DrawLine(i, 0, i, screenHeight, LIGHTGRAY);
		//for (int i = 0; i < screenHeight; i += 50) DrawLine(0, i, screenWidth, i, LIGHTGRAY);

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

        //----------------------------------------------------------------------------------
        // Spider Legs Drawing
        //----------------------------------------------------------------------------------
        
        for (int i = 0; i < 8; i++) {

            SpiderLeg& currentFoot = spider.legs[i]; 
                       
            float angleOffset = currentFoot.legAngle * DEG2RAD; 
            float finalAngle = rad + angleOffset; 
            float defaultRadius = 120.0f;
                 
            //currentFoot.kneePoint.x = centerSpider.x + sinf(finalAngle) * 60.0f;
            //currentFoot.kneePoint.y = centerSpider.y - cosf(finalAngle) * 60.0f;

            //currentFoot.footPoint.x = spiderCephalothorax.x + sinf(finalAngle) * 150.0f;
            //currentFoot.footPoint.y = spiderCephalothorax.y - cosf(finalAngle) * 150.0f;

            Vector2 midPoint = {
                (spiderCephalothorax.x + currentFoot.footPoint.x) / 2.0f,
                (spiderCephalothorax.y + currentFoot.footPoint.y) / 2.0f
            };
            
            currentFoot.kneePoint.x = midPoint.x + sinf(finalAngle) * 20.0f;
            currentFoot.kneePoint.y = midPoint.y - cosf(finalAngle) * 20.0f;

            currentFoot.targetFootPoint.x = centerSpider.x + sinf(finalAngle) * defaultRadius;
            currentFoot.targetFootPoint.y = centerSpider.y - cosf(finalAngle) * defaultRadius;

            //DrawCircleV(currentFoot.kneePoint, 2, GREEN);
            //DrawCircleV(currentFoot.targetFootPoint, 2, RED);

            DrawLineV(spiderCephalothorax, currentFoot.kneePoint, BROWN);
            DrawLineV(currentFoot.kneePoint, currentFoot.footPoint, BROWN);

            if (currentFoot.isStepping == false) {
                float distance = Vector2Distance(currentFoot.footPoint, currentFoot.targetFootPoint);

                if (distance > 80.0f) {
                    currentFoot.isStepping = true;

                    currentFoot.oldFootPoint = currentFoot.footPoint;
                    currentFoot.stepProgress = 0.0f;
                }
            }

            if (currentFoot.isStepping == true) {
                currentFoot.stepProgress += 0.1f;
                
                currentFoot.footPoint = Vector2Lerp(currentFoot.oldFootPoint, currentFoot.targetFootPoint, currentFoot.stepProgress);

                 if (currentFoot.stepProgress >= 1.0) {
                currentFoot.isStepping = false;
                currentFoot.stepProgress = 1.0f;
                 }
            }
 
            // TODO: Knee point trigonometric relations do find ideal kneePoint
            
            /*currentFoot.kneePoint.x =   
            currentFoot.kneePoint.y = */ 

        }
        
        //----------------------------------------------------------------------------------
        //Web tracking: 
        //----------------------------------------------------------------------------------
 
        if (isWeb) {
            rastrov1.emplace_back(webPoint);
            if (rastrov1.size() > 60000) {
                rastrov1.erase(rastrov1.begin());  
            }
        }
        
        if (rastrov1.size() > 1) {
            for(int i = 0; i < (int)rastrov1.size() - 1; i++) {
                //DrawCircleV(rastrov1[i], 4, WHITE);
                DrawLineV(rastrov1[i], rastrov1[i+1], WHITE);
            }
        }
	
		DrawTriangle(v1, v2, v3, BROWN);
        DrawPoly(spiderCephalothorax, 6, 20, spider.rotation, BROWN);

        DrawCircleV(spiderAbdomen, 25, BROWN);

        //DrawCircleV(spiderCephalothorax, 3, BLUE);

 
		/*DrawCircleV(v1, 3, BLUE);
		DrawCircleV(v2, 3, GREEN);
		DrawCircleV(v3, 3, GREEN);*/

        //Central Point starting from v1: 
        //DrawCircleV(centerSpider, 10, BLUE);
       
        //std::cout << "v1.x: "<<v1.x <<" | v2.y:"<<v1.y<< "\n";
        
        //std::cout << "Web 37500/" << rastrov1.size() << "\n";
      
        DrawText("[W,A,S,D]: motion | [SPACE]: shoot webs", 10, 10, 20, WHITE);

	EndDrawing();
}


