// frontend.h
#ifndef FRONTEND_H
#define FRONTEND_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include "../common.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800

class game_field : public QWidget
{
    Q_OBJECT
public:
    explicit game_field(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    
private:
    QTimer *timer_;
    
private slots:
    void update_paint();
};

#endif //FRONTEND_H