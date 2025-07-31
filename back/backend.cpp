#include "backend.h"

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

void update_snake_coords(GameInfo_t* game_info) {

}
void updateCurrentState(GameInfo_t* game_info) {

    Snake snake;
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