#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "settings.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<Settings>("com.hsa.qtbattleship", 1, 0, "Settings", &Settings::qmlInstance);

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("qrc:/src/qml/components/"));
    engine.load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));

    return app.exec();
}

