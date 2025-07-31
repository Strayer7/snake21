#include <QApplication>
#include <QWidget>
#include <QPainter>

#include "back/backend.h"
#include "front/frontend.h"


int main(int argc, char *argv[])
{
    GameInfo_t game_info = {0};
    game_info.field = create_game_field();
    updateCurrentState(&game_info);
    QApplication app(argc, argv);
    game_field widget(&game_info);
    widget.show();
    int result = app.exec(); // Запуск цикла событий

    free_game_field(game_info.field);

    return result;

}