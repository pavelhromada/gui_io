#include "menucontroller.h"
#include <QDebug>
#include <guiioserver.h>

MenuController::MenuController( const QPointer<GuiIO> &io )
    : io_( io )
{
    if (!io_)
        return;

    // with lambda
    io_->on( "clickMeClicked", [](const QJsonValue&) {
        qDebug() << "clickMeClicked event received";
    });

    // with new style connect
    io_->on( "logOutClicked", this, &MenuController::onLogOut );
    io_->on( "clickMeTooClicked", this, &MenuController::onClickMeTooClicked );
}

void MenuController::onClickMeTooClicked( const QJsonValue& )
{
    qDebug() << "clickMeTooClicked event received";
}

void MenuController::onLogOut( const QJsonValue& )
{
    qDebug() << "logOutClicked event received";
    if (io_)
        io_->server()->invoke( "showView", "ViewLogin" );
}
