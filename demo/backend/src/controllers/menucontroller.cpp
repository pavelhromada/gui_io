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

    // with old style connect
    io_->on( "clickMeTooClicked", this, SLOT(onClickMeTooClicked(const QJsonValue&)) );

    // with new style connect
    io_->on( "logOutClicked", this, &MenuController::onLogOut );
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
