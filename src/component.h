#ifndef COMPONENT_H
#define COMPONENT_H

#include <stdarg.h>
#include <stdio.h>

#include <SDL.h>

#include "entity.h"
#include "sprite.h"
#include "position_component.h"
#include "input.h"

enum component_type {POSITION, INPUT, SPRITE};

void component_register(enum component_type, ...);

#endif
