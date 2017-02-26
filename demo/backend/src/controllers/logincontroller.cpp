#include "logincontroller.h"
#include <QDebug>
#include <QJsonObject>
#include <guiioserver.h>

LoginController::LoginController( const QPointer<GuiIO> &io )
    : io_( io )
{
    if (!io_)
        return;

    io_->on( "validateLogin", this, &LoginController::onLogin );
}

void LoginController::onLogin( const QJsonValue& data )
{
    auto usr = data.toObject()["usr"].toString();
    auto pwd = data.toObject()["pwd"].toString();

    if (usr == "hallo" && pwd == "4711" && io_) {
        qDebug() << "user" << usr << "logged in";
        io_->server()->invoke( "showView", "ViewMenu" );
    } else {
        qDebug() << "wrong login";
    }
}
