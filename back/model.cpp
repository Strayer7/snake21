// game_model.cpp
#include "model.h"

SnakeModel::SnakeModel() {
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+1});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+2});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+3});
    snake_direction = Direction::Down;
}

const std::vector<Coords>& SnakeModel::get_body() const {
    return body;
}

int SnakeModel::get_size() const {
    return static_cast<int>(body.size());
}

Direction SnakeModel::get_direction() const {
    return snake_direction;
}

void SnakeModel::set_direction(Direction new_direction) {
    // Проверка на 180-градусный поворот
    switch (snake_direction) {
        case Direction::Up:
            if (new_direction != Direction::Down) snake_direction = new_direction;
            break;
        case Direction::Down:
            if (new_direction != Direction::Up) snake_direction = new_direction;
            break;
        case Direction::Left:
            if (new_direction != Direction::Right) snake_direction = new_direction;
            break;
        case Direction::Right:
            if (new_direction != Direction::Left) snake_direction = new_direction;
            break;
    }
}

void SnakeModel::move() {
    Direction current_dir = this->get_direction();
    Coords old_head = this->body[0];
    Coords new_head = old_head;

    switch (current_dir) {
        case Direction::Up:    new_head.y--; break;
        case Direction::Down:  new_head.y++; break;
        case Direction::Left:  new_head.x--; break;
        case Direction::Right: new_head.x++; break;
    }

    this->body.insert(this->body.begin(), new_head);
    this->body.pop_back();
}

void SnakeModel::reset() {
    body.clear();
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+1});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+2});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+3});
    snake_direction = Direction::Down;
}

// GameModel implementation
GameModel::GameModel() : state(STATE_START) {
    game_info.field = nullptr;
    game_info.next = nullptr;
    game_info.score = 0;
    game_info.high_score = 0;
    game_info.level = 1;
    game_info.speed = 1;
    game_info.pause = 0;
    initialize_game();
}

GameModel::~GameModel() {
    free_field();
}

void GameModel::initialize_game() {
    create_field();
    update_game_field();
}

GameInfo_t* GameModel::get_game_info() {
    return &game_info;
}

const GameInfo_t* GameModel::get_game_info() const {
    return &game_info;
}

void GameModel::create_field() {
    game_info.field = new int*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        game_info.field[i] = new int[WIDTH]();
    }
}

void GameModel::free_field() {
    if (game_info.field != nullptr) {
        for (int i = 0; i < HEIGHT; i++) {
            delete[] game_info.field[i];
        }
        delete[] game_info.field;
        game_info.field = nullptr;
    }
}

void GameModel::clear_game_field() {
    if (game_info.field != nullptr) {
        for (int row = 0; row < HEIGHT; ++row) {
            for (int col = 0; col < WIDTH; ++col) {
                game_info.field[row][col] = 0;
            }
        }
    }
}

void GameModel::update_game_field() {
    clear_game_field();
    update_snake_on_field();
}

void GameModel::update_snake_on_field() {
    const std::vector<Coords>& snake_body = snake.get_body();
    for (size_t i = 0; i < snake_body.size(); i++) {
        Coords snake_coords = snake_body[i];
        if (snake_coords.x >= 0 && snake_coords.x < WIDTH &&
            snake_coords.y >= 0 && snake_coords.y < HEIGHT) {
            if (i == 0) {
                game_info.field[snake_coords.y][snake_coords.x] = 2;
            } else {
                game_info.field[snake_coords.y][snake_coords.x] = 1;
            }
        }
    }
}

void GameModel::handle_user_input(UserAction_t action, bool hold) {
    switch (action) {
        case Start:
            if (state == STATE_START || state == STATE_GAME_OVER) {
                state = STATE_PLAY;
                snake.reset();
                initialize_game();
            }
            break;
        case Pause:
            game_info.pause = !game_info.pause;
            break;
        case Terminate:
            state = STATE_GAME_OVER;
            break;
        case Up:
            if (!game_info.pause) snake.set_direction(Direction::Up);
            break;
        case Down:
            if (!game_info.pause) snake.set_direction(Direction::Down);
            break;
        case Left:
            if (!game_info.pause) snake.set_direction(Direction::Left);
            break;
        case Right:
            if (!game_info.pause) snake.set_direction(Direction::Right);
            break;
        case Action:
            // Дополнительные действия
            break;
    }
}

void GameModel::update_game_state() {
    if (state == STATE_PLAY && !game_info.pause) {
        snake.move();
        update_game_field();
    }
}

Game_state GameModel::get_state() const {
    return state;
}

void GameModel::set_state(Game_state new_state) {
    state = new_state;
}