#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QDebug>

#include "gameapplication.h"
#include "gameengine.h"
#include "settings.h"


GameApplication::GameApplication(QObject *parent)
    : QObject(parent)
{
}

bool GameApplication::showQmlWindow()
{
    if(!registerTypes())
    {
        qCritical() << "Qml types failed to initialize!";
        return false;
    }

    QQmlApplicationEngine* appengine = new QQmlApplicationEngine(this);
    QQmlContext* qmlcontext = appengine->rootContext();
    if(qmlcontext == nullptr)
    {
        qCritical() << "Can not get QML context!";
        return false;
    }

    GameEngine* engine = new GameEngine(this);
    qmlcontext->setContextProperty("engine", engine); // Global 'engine' object to access in Qml

    appengine->addImportPath(QStringLiteral("qrc:/src/qml/components/"));
    appengine->load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));

    return true;
}

bool GameApplication::registerTypes()
{
    qmlRegisterSingletonType<Settings>("QtBattleship", 1, 0, "Settings", &Settings::qmlInstance);

    return true;
}
