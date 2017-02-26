#include <QCoreApplication>
#include <guiioserver.h>
#include "controllers/menucontroller.h"
#include "controllers/logincontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GuiIOServer ioServer;

    LoginController loginController{ ioServer.ioOf( "view_login" )};
    MenuController menuController{ ioServer.ioOf( "view_menu" )};

    ioServer.listen( 9000 );

    return a.exec();
}
