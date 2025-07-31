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
    // Вычисления eyeMarginX, eyeMarginY, eyeRadius можно оставить здесь,
    // так как они зависят только от cell_width/cell_height

    int eyeMarginX = cell_width * 0.2;
    int eyeMarginY = cell_height * 0.2;
    int eyeRadius = qMin(cell_width, cell_height) * 0.15;
    // int tongueLength = cell_width * 0.3; // Аналогично для язычка

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (game_data_ && game_data_->field) {
                int value = game_data_->field[y][x];

                if (value == 1 || value == 2) { // Если это часть змеи
                    // 1. Нарисовать основу сегмента (тело или голова)
                    QRect segmentRect(x * cell_width, y * cell_height, cell_width, cell_height);
                    p.fillRect(segmentRect, QBrush(Qt::green));

                    // 2. Если это голова, добавить детали
                    if (value == 2) {
                        qreal eyeRadius = qMin(cell_width, cell_height) * 0.15;
                        qreal eyeOffsetX = cell_width * 0.25; // Смещение глаз от центра по X
                        qreal eyeOffsetY = cell_height * 0.25;
                        qreal centerX = x * cell_width + cell_width / 2.0;
                        qreal centerY = y * cell_height + cell_height / 2.0;

                        QBrush oldBrush = p.brush();

                        // Устанавливаем черную кисть для глаз
                        p.setBrush(Qt::black);
                        p.setPen(Qt::NoPen); // Нет контура у глаз

                        // Рисуем глаза
                        p.drawEllipse(QPointF(centerX - eyeOffsetX, centerY - eyeOffsetY), eyeRadius, eyeRadius); // Верхний левый
                        p.drawEllipse(QPointF(centerX + eyeOffsetX, centerY - eyeOffsetY), eyeRadius, eyeRadius); // Верхний правый

                        // Восстанавливаем старую кисть
                        p.setBrush(oldBrush);


                    }
                }
            }
        }
    }
}