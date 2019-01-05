#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "engine.h"
#include "entity.h"
#include "logging.h"
#include "collision.h"
#include "position_c.h"

#include "behaviour.h"

#define UNUSED __attribute__((unused))

float ballSpeed = 2.0f;

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
  ballSpeed *= 1.05f;
}

void bounceBallWall(void* _ UNUSED) {
  ballDirectionY *= -1;
}

bool tru(void* _ UNUSED) {
  static Position* ballPos = NULL;
  if (ballPos == NULL) {
    ballPos = position_get(entity_getNamed("ball"));
  }
  return ballPos->x > 250;
}

void rPaddleWalk(void* args UNUSED) {
  Entity rPaddle = entity_getNamed("rightPaddle");
  Entity ball = entity_getNamed("ball");
  position_get(rPaddle)->y += position_get(ball)->y < position_get(rPaddle)->y ? -2.5f : 2.5f;
}

void scorePointPlayer1(void* _ UNUSED ) {
  Position* pos = position_get(entity_getNamed("ball"));
  pos->x = 400;
  pos->y = 300;
  ballSpeed = 2.0f;
}

void scorePointPlayer2(void* _ UNUSED) {
  Position* pos = position_get(entity_getNamed("ball"));
  pos->x = 400;
  pos->y = 300;
  ballSpeed = 2.0f;
}

bool veldad(void* _ UNUSED) {
  return true;
}

void ballProcess(void* ball) {
    Position* bPos = position_get(*((Entity*) ball));
    bPos->x += ballSpeed * ballDirectionX;
    bPos->y += ballSpeed * ballDirectionY;
}

int main(void) {
  init();

  sprite_loadImage("ball.png");

  Entity leftPaddle = entity_newNamed("leftPaddle");
  position_register(leftPaddle, 10.0, 10.0);
  sprite_register(leftPaddle, "ball.png", 0, 0, 10, 50);
  input_register(SDL_SCANCODE_W, &moveUp, &leftPaddle);
  input_register(SDL_SCANCODE_S, &moveDown, &leftPaddle);

  Entity rightPaddle = entity_newNamed("rightPaddle");
  position_register(rightPaddle, 800-10.0, 600-10.0);
  sprite_register(rightPaddle, "ball.png", 40, 40, 10, 50);

  Entity ball = entity_newNamed("ball");
  position_register(ball, 400.0, 300.0);
  sprite_register(ball, "ball.png", 26, 48, 16, 16);

  CTagId bounceTag = collision_addNewTag("bounce", &bounceBallPaddle, NULL);
  GPU_Rect paddleBox = {-5.0f, -25.0f, 10.0f, 50.0f};
  collision_register(bounceTag, &leftPaddle, paddleBox);
  collision_register(bounceTag, &rightPaddle, paddleBox);
  GPU_Rect box = {-8.0f, -8.0f, 16.0f, 16.0f};
  collision_register(bounceTag, &ball, box);

  CTagId bounceWallTag = collision_addNewTag("wall", &bounceBallWall, NULL);
  GPU_Rect upperWall = {0.0f, -10.0f, 800.0f, 15.0f};
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
    sprite_draw(entity_getNamed("leftPaddle"));
    sprite_draw(entity_getNamed("rightPaddle"));
    sprite_draw(entity_getNamed("ball"));
    behaviour_process();
    collision_process();
    graphics3D_start();
    graphics3D_end();
    frameEnd();
    open = handleEvents();
  }

  return EXIT_SUCCESS;
}
