#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "gameapplication.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    GameApplication game;
    if(!game.showQmlWindow())
        return 0;

    return app.exec();
}

