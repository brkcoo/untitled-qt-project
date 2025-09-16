#include "gamewindow.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    GameWindow window;
    window.show();

    QObject::connect(&app, &QApplication::aboutToQuit,
                     [&window] { window.onExit(); });

    return app.exec();
}
