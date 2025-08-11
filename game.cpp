#include <QApplication>
#include "front/frontend.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    srand(time(nullptr));

    game_field widget;
    widget.show();

    int result = app.exec();

    // Очистка ресурсов (если нужно)
    // cleanup_game_controller();

    return result;
}