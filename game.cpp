#include <QApplication>
#include <QWidget>
#include <QPainter>

#include "back/backend.h"
#include "front/frontend.h"


int main(int argc, char *argv[])
{
    Game_state state = STATE_PLAY;
    while (state != STATE_GAME_OVER) {
        switch (state) {
            case STATE_PLAY:
                game_info.field = create_game_field();
                update_snake(&game_info);
                QApplication app(argc, argv);
                game_field widget(&game_info);
                widget.show();
                int result = app.exec(); // Запуск цикла событий
                free_game_field(game_info.field);
                return result;
        }
    }



}