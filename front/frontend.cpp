#include "frontend.h"

game_field::game_field(GameInfo_t* game_data, QWidget* parent)
    : QWidget(parent), // Вызов конструктора базового класса QWidget
      game_data_(game_data) // Инициализация приватного члена game_data_
{
    setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
}

void game_field::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(rect(), QBrush(Qt::blue));
    int cell_width = this->width() / WIDTH;
    int cell_height = this->height() / HEIGHT;
    for (int y = 0; y < HEIGHT; y++) {
        // y < HEIGHT (включая последнюю строку)
        for (int x = 0; x < WIDTH; x++) { // x < WIDTH (включая последний столбец)
            // Проверка game_data_ обязательна!
            if (game_data_ && game_data_->field) {
                int value = game_data_->field[y][x]; // y, x
                if (value == 1 || value == 2) {
                    p.fillRect(x*cell_width, y*cell_height, cell_width, cell_height, QBrush(Qt::green));
                }
            }

        }
    }
}