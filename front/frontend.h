    #ifndef FRONTEND_H
    #define FRONTEND_H


    #include <QApplication>
    #include <QWidget>
    #include <QPainter>
    #include "../back/backend.h"

    #define WINDOW_WIDTH 400
    #define WINDOW_HEIGHT 800

    class Snake;

    class game_field : public QWidget
    {

    public:
        explicit game_field(GameInfo_t* game_data, QWidget* parent = nullptr);

        void paintEvent(QPaintEvent *event);
    private:
        GameInfo_t* game_data_;
    };

    #endif //FRONTEND_H
