// common.h
#ifndef COMMON_H
#define COMMON_H

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

typedef enum {
    STATE_START,
    STATE_PLAY,
    STATE_PAUSE,
    STATE_GAME_OVER
} Game_state;

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