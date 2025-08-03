#include "backend.h"

Snake Snake::snake_;
Snake& Snake::get_instance() {
    return snake_;
}

Snake::Snake() {
    // Инициализация тела змеи
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+1});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+2});
    body.push_back(Coords{SNAKE_START_POINT_X, SNAKE_START_POINT_Y+3});
    // Инициализация начального направления
    snake_direction = Direction::Down;
}

void Snake::move() {
    // 1. Получить текущее направление
    Direction current_dir = this->get_direction(); // или просто current_direction_

    // 2. Получить текущую голову
    Coords old_head = this->body[0]; // Предполагаем, что тело не пустое

    // 3. Вычислить новую голову
    Coords new_head = old_head;
    switch (current_dir) {
        case Direction::Up:    new_head.y--; break;
        case Direction::Down:  new_head.y++; break;
        case Direction::Left:  new_head.x--; break;
        case Direction::Right: new_head.x++; break;
    }

    // 4. Обновить вектор body
    // Вставляем новую голову в начало
    this->body.insert(this->body.begin(), new_head);
    // Удаляем последний элемент (хвост), чтобы змея "двигалась"
    // Позже здесь будет логика: если съела еду, хвост не удаляем
    this->body.pop_back();
}

const std::vector<Coords>& Snake::get_body() const {
    return body;
}


int Snake::get_size() const {
    return static_cast<int>(body.size());
}

Direction Snake::get_direction() const {
    return snake_direction;
}

void Snake::set_direction(Direction new_direction) {
    // (Опционально) Добавьте проверку на 180-градусный поворот
    snake_direction = new_direction;
}


static GameInfo_t game_info = {0};

GameInfo_t updateCurrentState() {
    Snake& snake = Snake::get_instance();
    snake.move();
    update_snake(&game_info);
    return game_info;
}



int **create_game_field() {
    int** field = new int*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        field[i] = new int[WIDTH]();
    }
    return field;
}

void free_game_field(int **field) {
    if (field != nullptr) {
        for (int i = 0; i < HEIGHT; i++) {
            delete[] field[i];
        }
        delete[] field;
    }
}

void clear_game_field(GameInfo_t* game_info) {
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            game_info->field[row][col] = 0;
        }
    }
}


void update_snake(GameInfo_t* game_info) {
    Snake& snake = Snake::get_instance();
    if (game_info->field != nullptr) {
        clear_game_field(game_info);
    }
    for (int i = 0; i < snake.get_size(); i++) {
        Coords snake_coords = snake.get_body()[i];
        if (snake_coords.x >= 0 && snake_coords.x < WIDTH && snake_coords.y >= 0 && snake_coords.y < HEIGHT) {
            if (i == 0) {
                // Голова змеи
                game_info->field[snake_coords.y][snake_coords.x] = 2; // 2 обозначает голову
            } else {
                // Тело змеи
                game_info->field[snake_coords.y][snake_coords.x] = 1; // 1 обозначает тело
            }
        }
    }

}