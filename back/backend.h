#ifndef BACKEND_H
#define BACKEND_H

#define SNAKE_START_POINT_X 5
#define SNAKE_START_POINT_Y 5
#define WIDTH 10
#define HEIGHT 20


#include <vector>


struct Coords {
    int x;
    int y;
};

class Snake {
    private:
    std::vector<Coords> body;
    public:

    const std::vector<Coords>& get_body() const {
        return body;
    }

    int get_size() const {
        return static_cast<int>(body.size());
    }
    Snake() {
        body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y});
        body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+1});
        body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+2});
        body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+3});
    }
};

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


void userInput(UserAction_t action, bool hold);

void updateCurrentState(GameInfo_t* game_info);

int **create_game_field();
void free_game_field(int **field);

void clear_game_field(GameInfo_t game_info);


#endif //BACKEND_H
