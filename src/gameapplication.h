/**
 * \class GameApplication
 *
 * \brief Qml context creation and type registering
 *
 * This class is meant as the main application object. It
 * encapsulates the Qml context creation and registers all
 * types available from Qml code. Further on its the starting
 * point for the main window showup.
 *
 */

#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <QObject>


class GameApplication : public QObject
{
    Q_OBJECT

public:
    GameApplication(QObject* parent = nullptr);

    bool showQmlWindow(); ///< Show main window

private:
    bool registerTypes(); ///< Register all Qml types
};


#endif // GAMEAPPLICATION_H
