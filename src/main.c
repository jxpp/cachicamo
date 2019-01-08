#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "engine.h"
//#include "entity.h"
//#include "logging.h"
//#include "collision.h"
//#include "position_c.h"
//#include "behaviour.h"

#define UNUSED __attribute__((unused))

float ballSpeed = 3.0f;

float ballDirectionX = 1.0f;
float ballDirectionY = 1.0f;

void moveUp(void* entity) {
  Entity e = *((Entity*) entity);
  Position* position = position_get(e);
  position->y -= ballSpeed+0.1f;
}

void moveDown(void* entity) {
  Entity e = *((Entity*) entity);
  Position* position = position_get(e);
  position->y += ballSpeed+0.1f;
}

void bounceBallPaddle(void* _ UNUSED ) {
  ballDirectionX *= -1;
  ballSpeed *= 1.025f;
}

void bounceBallWall(void* _ UNUSED) {
  ballDirectionY *= -1;
  ballSpeed *= 1.025f;
}

bool tru(void* _ UNUSED) {
  static Position* ballPos = NULL;
  if (ballPos == NULL) {
    ballPos = position_get(entity_getNamed("ball"));
  }
  return ballPos->x > 250;
}

void rPaddleWalk(void* args UNUSED) {
  float* rPaddleY_ptr = &position_get(entity_getNamed("rightPaddle"))->y;
  float ballY = position_get(entity_getNamed("ball"))->y;
  float dist = fabs(*rPaddleY_ptr - ballY);
  *rPaddleY_ptr += ballY < *rPaddleY_ptr ? -fmin(2.5f, dist) : fmin(2.5f, dist);
}

void scorePointPlayer1(void* _ UNUSED ) {
  Position* pos = position_get(entity_getNamed("ball"));
  pos->x = 400;
  pos->y = 300;
  ballSpeed = 2.0f;
  ballDirectionX *= -1;
  ballDirectionY *= -1;
}

void scorePointPlayer2(void* _ UNUSED) {
  Position* pos = position_get(entity_getNamed("ball"));
  pos->x = 400;
  pos->y = 300;
  ballSpeed = 2.0f;
  ballDirectionX = 1;
  ballDirectionY = 1;
}

bool veldad(void* _ UNUSED) {
  return true;
}

void ballProcess(void* ball) {
    Position* bPos = position_get(*((Entity*) ball));
    printf("%f %f\n", bPos->x, bPos->y);
    bPos->x += ballSpeed * ballDirectionX;
    bPos->y += ballSpeed * ballDirectionY;
}

int main(void) {
  init();

  sprite_loadImage("ball.png");

  Entity leftPaddle = entity_newNamed("leftPaddle");
  position_register(leftPaddle, 40, 40);
  sprite_register(leftPaddle, "ball.png", 0, 0, 10, 50);
  input_register(SDL_SCANCODE_W, &moveUp, &leftPaddle);
  input_register(SDL_SCANCODE_S, &moveDown, &leftPaddle);

  Entity rightPaddle = entity_newNamed("rightPaddle");
  position_register(rightPaddle, 800-40.0, 600-40.0);
  sprite_register(rightPaddle, "ball.png", 40, 40, 10, 50);

  Entity ball = entity_newNamed("ball");
  position_register(ball, 400.0, 300.0);
  sprite_register(ball, "ball.png", 26, 48, 16, 16);

  CTagId bounceTag = collision_addNewTag("bounce", &bounceBallPaddle, NULL);
  GPU_Rect paddleBox = {-5.0f, -25.0f, 10.0f, 50.0f};
  collision_register(bounceTag, &leftPaddle, paddleBox);
  collision_register(bounceTag, &rightPaddle, paddleBox);
  GPU_Rect box = {-8, -8, 16, 16};
  collision_register(bounceTag, &ball, box);

  CTagId bounceWallTag = collision_addNewTag("wall", &bounceBallWall, NULL);
  GPU_Rect upperWall = {0.0f, -20.0f, 800.0f, 20.0f};
  GPU_Rect lowerWall = {0.0f, 600.0f, 800.0f, 15.0f};
  collision_register(bounceWallTag, &ball, box);
  collision_register(bounceWallTag, NULL, upperWall);
  collision_register(bounceWallTag, NULL, lowerWall);

  CTagId player1PointTag = collision_addNewTag("player1Point", &scorePointPlayer1, NULL);
  GPU_Rect rightWall = {800.0f, -10.0f, 5.0f, 620.0f};
  collision_register(player1PointTag, &ball, box);
  collision_register(player1PointTag, NULL, rightWall);

  CTagId player2PointTag = collision_addNewTag("player2Point", &scorePointPlayer2, NULL);
  GPU_Rect leftWall = {-10.0f, 0.0f, 5.0f, 600.0f};
  collision_register(player2PointTag, &ball, box);
  collision_register(player2PointTag, NULL, leftWall);

  behaviour_init();
  behaviour_register(&tru, NULL, &rPaddleWalk, NULL);
  behaviour_register(&veldad, NULL, &ballProcess, &ball);

  bool open = true;

  while (open) {
    frameStart();
    open = handleEvents();
    cachicamo_processFrame();
    frameEnd();
  }

  return EXIT_SUCCESS;
}
