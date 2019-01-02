#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "engine.h"
#include "entity.h"
#include "logging.h"
#include "collision.h"
#include "position_c.h"

#include "component.h"

void moveUp(void* entity) {
  Entity e = *((Entity*) entity);
  Position* position = position_get(e);
  position->y -= 2.1f;
}

void moveDown(void* entity) {
  Entity e = *((Entity*) entity);
  Position* position = position_get(e);
  position->y += 2.1f;
}

void probanding(void* arg) {
  logging_log(DEBUG, "main", "WOW");
}

float ballSpeed = 2.0f;
float ballDirectionX = 1.0f;
float ballDirectionY = 1.0f;

void bounceBallPaddle(void* arg) {
  ballDirectionX *= -1;
  ballSpeed *= 1.1f;
}
void bounceBallWall(void* arg) {
  ballDirectionY *= -1;
}

void scorePointPlayer1(void* uselessArg) {
  Position* pos = position_get(entity_getNamed("ball"));
  pos->x = 400;
  pos->y = 300;
}

void scorePointPlayer2(void* thisArgumentNeverActuallyGetsUtilizedButNeedsToExistSoTheFunctionSignatureMatches) {
  Position* pos = position_get(entity_getNamed("ball"));
  pos->x = 400;
  pos->y = 300;
}

int main(void) {
  init();

  sprite_loadImage("ball.png");

  Entity leftPaddle = entity_newNamed("leftPaddle");
  component_register(POSITION, leftPaddle, 10.0, 10.0);
  component_register(SPRITE, leftPaddle, "ball.png");
  component_register(INPUT, SDL_SCANCODE_W, &moveUp, &leftPaddle);
  component_register(INPUT, SDL_SCANCODE_S, &moveDown, &leftPaddle);

  Entity rightPaddle = entity_newNamed("rightPaddle");
  component_register(POSITION, rightPaddle, 800-10.0, 600-10.0);
  component_register(SPRITE, rightPaddle, "ball.png");

  Entity ball = entity_newNamed("ball");
  component_register(POSITION, ball, 20.0, 20.0);
  component_register(SPRITE, ball, "ball.png");

  CTagId bounceTag = collision_addNewTag("bounce", &bounceBallPaddle, NULL);
  GPU_Rect box = {0.0f, 0.0f, 8.0f, 8.0f};
  collision_register(bounceTag, &leftPaddle, box);
  collision_register(bounceTag, &rightPaddle, box);
  collision_register(bounceTag, &ball, box);

  CTagId bounceWallTag = collision_addNewTag("wall", &bounceBallWall, NULL);
  GPU_Rect upperWall = {0.0f, -10.0f, 800.0f, 15.0f};
  GPU_Rect lowerWall = {0.0f, 600.0f, 800.0f, 15.0f};
  collision_register(bounceWallTag, &ball, box);
  collision_register(bounceWallTag, NULL, upperWall);
  collision_register(bounceWallTag, NULL, lowerWall);

  CTagId player1PointTag = collision_addNewTag("player1Point", &scorePointPlayer1, NULL);
  GPU_Rect rightWall = {820.0f, 0.0f, 5.0f, 600.0f};
  collision_register(player1PointTag, &ball, rightWall);
  collision_register(player1PointTag, NULL, rightWall);

  CTagId player2PointTag = collision_addNewTag("player2Point", &scorePointPlayer2, NULL);
  GPU_Rect leftWall = {-20.0f, 0.0f, 5.0f, 600.0f};
  collision_register(player2PointTag, &ball, leftWall);
  collision_register(player2PointTag, NULL, leftWall);

  bool open = true;

  while (open) {
    frameStart();
    open = handleEvents();
    sprite_draw(entity_getNamed("leftPaddle"));
    sprite_draw(entity_getNamed("rightPaddle"));
    sprite_draw(entity_getNamed("ball"));
    // game logic
    // to be abstracted some time
    Position* bPos = position_get(ball);
    bPos->x += ballSpeed * ballDirectionX;
    bPos->y += ballSpeed * ballDirectionY;

    Position* rPos = position_get(rightPaddle);
    rPos->y += bPos->y < rPos->y ? -(ballSpeed - 0.01) : (ballSpeed - 0.01);
    // -----------------------------------------
    collision_process();
    graphics3D_start();
    graphics3D_end();
    frameEnd();
  }

  return EXIT_SUCCESS;
}
