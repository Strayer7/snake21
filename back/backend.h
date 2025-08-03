#ifndef BACKEND_H
#define BACKEND_H

#define SNAKE_START_POINT_X 5
#define SNAKE_START_POINT_Y 12
#define WIDTH 10
#define HEIGHT 20

#include "../common.h"
#include <vector>

struct Coords {
    int x;
    int y;
};
enum class Direction {
    Up,
    Down,
    Left,
    Right
};
class Snake {
    private:
    static std::vector<Coords> body;
    static Direction snake_direction;
    static Snake snake_;

    public:
    Snake();
    const std::vector<Coords>& get_body() const;
    int get_size() const;
    Direction get_direction() const;
    void set_direction(Direction new_direction);
    static Snake& get_instance();
    void move();
};


typedef enum {
    STATE_START,
    STATE_PLAY,
    STATE_PAUSE,
    STATE_GAME_OVER
} Game_state;



void userInput(UserAction_t action, bool hold);

void update_snake(GameInfo_t* game_info);

int **create_game_field();
void free_game_field(int **field);

void clear_game_field(GameInfo_t game_info);

GameInfo_t updateCurrentState();


#endif //BACKEND_H
