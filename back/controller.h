// game_controller.h
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "../common.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif //GAME_CONTROLLER_H