#ifndef COMMON_H
#define COMMON_H

#include "back/backend.h"
#include "front/frontend.h"

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;


typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

#endif //COMMON_H
