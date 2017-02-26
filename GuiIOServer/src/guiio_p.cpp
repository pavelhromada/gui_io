#include <QJsonDocument>
#include <QJsonObject>
#include "guiio_p.h"

GuiIOPrivate::GuiIOPrivate( GuiIO* qptr )
    : q_ptr( qptr )
{}

void GuiIOPrivate::cleanUp()
{
    foreach( const impl::EventHandler* i, invokers_)
        delete i;
    invokers_.clear();
}

void GuiIOPrivate::init( const QString& nsp, GuiIOServer* ioServer )
{
    nsp_ = nsp;
    server_ = ioServer;
}

void GuiIOPrivate::useSocket( QWebSocket* socket )
{
    wsSocket_ = socket;
}

void GuiIOPrivate::handleEvent( const QJsonObject& evt )
{
    if (!invokers_.contains( evt[ EVT_NAME ].toString() ))
        return;

    auto invoker = invokers_[ evt[ EVT_NAME ].toString() ];
    emit invoker->invoked( evt[ EVT_DATA ] );
}

void GuiIOPrivate::invokeEvent( const QString& event, const QJsonValue& data )
{
    if (!wsSocket_ || !wsSocket_->isValid())
        return;

    QJsonDocument eventMsg{ QJsonObject{
            { EVT_NSP, nsp_ },
            { EVT_NAME, event },
            { EVT_DATA, data }}};

    wsSocket_->sendTextMessage( eventMsg.toJson() );
}

