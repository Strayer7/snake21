#ifndef MODEL_H
#define MODEL_H

#include "../common.h"
#include <vector>

#define SNAKE_START_POINT_X 5
#define SNAKE_START_POINT_Y 12
#define WIDTH 10
#define HEIGHT 20

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

class SnakeModel {
private:
    std::vector<Coords> body;
    Direction snake_direction;

public:
    SnakeModel();
    const std::vector<Coords>& get_body() const;
    int get_size() const;
    Direction get_direction() const;
    void set_direction(Direction new_direction);
    void move();
    void reset();
};

class GameModel {
private:
    SnakeModel snake;
    GameInfo_t game_info;
    Game_state state;

public:
    GameModel();
    ~GameModel();
    
    GameInfo_t* get_game_info();
    const GameInfo_t* get_game_info() const;
    
    void update_game_field();
    void clear_game_field();
    void create_field();
    void free_field();
    
    void handle_user_input(UserAction_t action, bool hold);
    void update_game_state();
    
    Game_state get_state() const;
    void set_state(Game_state new_state);
    
private:
    void initialize_game();
    void update_snake_on_field();
};

#endif