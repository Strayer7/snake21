// frontend.cpp
#include "frontend.h"
#include "../back/controller.h"
#include "../back/model.h"

game_field::game_field(QWidget* parent)
    : QWidget(parent)
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &game_field::update_paint);
    timer_->start(300);
}

void game_field::update_paint() {
    repaint();
}

void game_field::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(rect(), QBrush(Qt::blue));

    // Получаем состояние игры через контроллер
    GameInfo_t info = updateCurrentState();
    int cell_width = this->width() / WIDTH;
    int cell_height = this->height() / HEIGHT;

    if (info.field != nullptr) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                int value = info.field[y][x];

                if (value == 1 || value == 2) {
                    QRect segmentRect(x * cell_width, y * cell_height, cell_width, cell_height);
                    p.fillRect(segmentRect, QBrush(Qt::green));

                    if (value == 2) {
                        qreal eyeRadius = qMin(cell_width, cell_height) * 0.15;
                        qreal eyeOffsetX = cell_width * 0.25;
                        qreal eyeOffsetY = cell_height * 0.25;
                        qreal centerX = x * cell_width + cell_width / 2.0;
                        qreal centerY = y * cell_height + cell_height / 2.0;

                        QBrush oldBrush = p.brush();
                        p.setBrush(Qt::black);
                        p.setPen(Qt::NoPen);

                        p.drawEllipse(QPointF(centerX - eyeOffsetX, centerY - eyeOffsetY), eyeRadius, eyeRadius);
                        p.drawEllipse(QPointF(centerX + eyeOffsetX, centerY - eyeOffsetY), eyeRadius, eyeRadius);

                        p.setBrush(oldBrush);
                    }
                }
            }
        }
    }
}