#include "behaviour.h"

void behaviour_init(void) {
  behaviour_map = malloc(sizeof(struct _behaviour_t*) * MAX_ENTITIES);
  for (int i = 0; i < MAX_ENTITIES; i++) {
    behaviour_map[i] = NULL;
  }
  nBehaviours = 0;
}

void behaviour_register(bool (*conditional)(void*), void* conditionalArgs,
                        void (*action)(void*), void* actionArgs) {
  Behaviour* beh = malloc(sizeof(struct _behaviour_t));
  beh->conditional = conditional;
  beh->conditionalArgs = conditionalArgs;
  beh->action = action;
  beh->actionArgs = actionArgs;
  behaviour_map[nBehaviours] = beh;
  nBehaviours++;
}

void behaviour_process(void) {
  Behaviour beh;
  for (int i = 0; i < MAX_ENTITIES; i++) {
    if (behaviour_map[i] == NULL) {
      return;
    }
    beh = *behaviour_map[i];
    if (beh.conditional(beh.conditionalArgs)) {
      beh.action(beh.actionArgs);
    }
  }
}
