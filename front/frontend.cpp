// frontend.cpp
#include "frontend.h"
#include "../back/controller.h"
#include "../back/model.h"

game_field::game_field(QWidget* parent)
    : QWidget(parent)
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &game_field::update_paint);
    timer_->start(300);
}
void game_field::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
            userInput(Up, false);
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            userInput(Down, false);
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            userInput(Left, false);
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            userInput(Right, false);
            break;
        case Qt::Key_Space:
            userInput(Action, false);
            break;
        case Qt::Key_P:
            userInput(Pause, false);
            break;
        case Qt::Key_Escape:
            userInput(Terminate, false);
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            userInput(Start, false);
            break;
        default:
            QWidget::keyPressEvent(event);  // Передаем событие родителю по умолчанию
            return;
    }
}
void game_field::update_paint() {
    repaint();
}

void game_field::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(rect(), QBrush(Qt::blue));

    // Получаем состояние игры через контроллер
    GameInfo_t info = updateCurrentState();

    if (info.field == nullptr) {
        p.setPen(Qt::white);
        p.drawText(rect(), Qt::AlignCenter, "Press ENTER to start");
        return;
    }
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
                }else if (value == 3) {
                    QRect cellRect(x * cell_width, y * cell_height, cell_width, cell_height);
                    QPointF center(x * cell_width + cell_width / 2.0, y * cell_height + cell_height / 2.0);
                    qreal radius = qMin(cell_width, cell_height) * 0.4;

                    // Основное тело яблока
                    QRadialGradient gradient(center, radius);
                    gradient.setColorAt(0, Qt::red);
                    gradient.setColorAt(1, Qt::darkRed);

                    p.setBrush(QBrush(gradient));
                    p.setPen(Qt::NoPen);
                    p.drawEllipse(center, radius, radius);

                    // Блеск на яблоке
                    QPointF shineCenter(x * cell_width + cell_width * 0.35, y * cell_height + cell_height * 0.35);
                    qreal shineRadius = radius * 0.3;

                    p.setBrush(QBrush(Qt::white));
                    p.setOpacity(0.7);
                    p.drawEllipse(shineCenter, shineRadius, shineRadius);
                    p.setOpacity(1.0);

                    // Листик яблока
                    QPointF leafPoint(x * cell_width + cell_width * 0.7, y * cell_height + cell_height * 0.25);
                    p.setBrush(QBrush(Qt::green));
                    p.drawEllipse(leafPoint, cell_width * 0.15, cell_height * 0.15);
                }
                }
            }
        }
    }
