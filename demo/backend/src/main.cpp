#include <QCoreApplication>
#include <QDebug>
#include <guiioserver.h>
#include "controllers/menucontroller.h"
#include "controllers/logincontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GuiIOServer ioServer;

    LoginController loginController{ ioServer.ioOf( "view_login" )};
    MenuController menuController{ ioServer.ioOf( "view_menu" )};

    QObject::connect( &ioServer, &GuiIOServer::connected, []{
        qDebug() << "server connected";
    });

    QObject::connect( &ioServer, &GuiIOServer::disconnected, []{
        qDebug() << "server disconnected";
    });

    qDebug() << "server listening on port 9000 ...";
    ioServer.listen( 9000 );

    return a.exec();
}
