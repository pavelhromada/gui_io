#ifndef GUIIOPRIVATE_H
#define GUIIOPRIVATE_H

#include <QHash>
#include <QString>
#include <QWebSocket>
#include "../include/guiio.h"

const QString EVT_NSP  = "nsp";
const QString EVT_NAME = "evt";
const QString EVT_DATA = "data";

class GuiIOPrivate
{
public:
    GuiIOPrivate( GuiIO* qptr );
    void cleanUp();
    void init( const QString& nsp, GuiIOServer* ioServer );
    void useSocket( QWebSocket* socket );
    void handleEvent( const QJsonObject& evt );
    void invokeEvent( const QString& event, const QJsonValue& data );

    Q_DECLARE_PUBLIC( GuiIO )

    GuiIO* const q_ptr = nullptr;
    QString nsp_;
    QHash<QString, const impl::EventHandler*> invokers_;
    GuiIOServer* server_ = nullptr;
    QWebSocket* wsSocket_ = nullptr;
};

#endif // GUIIOPRIVATE_H
