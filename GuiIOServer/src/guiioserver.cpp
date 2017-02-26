#include "../include/guiioserver.h"
#include <QWebSocketServer>
#include <QWebSocket>
#include <QMultiHash>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "guiio_p.h"

class GuiIOServerPrivate : public GuiIOPrivate
{
    GuiIOServerPrivate( GuiIO* qptr );
    Q_DECLARE_PUBLIC( GuiIOServer )

    void onNewConnection();
    void onClosed();
    void onTextMessage( const QString& msg );
    QJsonObject toEventObject( const QString& msg ) const;
    void listen( quint16 port );

    QMultiHash<QString, GuiIOPrivate*> guiIos_;
    QWebSocketServer wsServer_;
};

GuiIOServerPrivate::GuiIOServerPrivate( GuiIO* q )
    : GuiIOPrivate( q )
    , wsServer_( QStringLiteral("GUIIO_SERVER"), QWebSocketServer::NonSecureMode )
{}

void GuiIOServerPrivate::listen( quint16 port )
{
    if (wsServer_.listen( QHostAddress::Any, port ))
        QObject::connect( &wsServer_, &QWebSocketServer::newConnection, &wsServer_, [this]() {
            onNewConnection();
        });
}

void GuiIOServerPrivate::onNewConnection()
{
    auto socket = wsServer_.nextPendingConnection();
    if (!socket)
        return;

    wsSocket_ = socket;

    for (auto& io : guiIos_)
        io->useSocket( socket );

    QObject::connect( wsSocket_, &QWebSocket::textMessageReceived, q_ptr, [this](const QString& msg){
        onTextMessage( msg );
    });

    QObject::connect( wsSocket_, &QWebSocket::disconnected, q_ptr, [this](){
        onClosed();
    });

    Q_Q( GuiIOServer );
    emit q->connected();
}

void GuiIOServerPrivate::onClosed()
{
    for (auto& io : guiIos_)
        io->useSocket( nullptr );

    if (wsSocket_)
        wsSocket_->deleteLater();
    wsSocket_ = nullptr;

    Q_Q( GuiIOServer );
    emit q->disconnected();
}

void GuiIOServerPrivate::onTextMessage( const QString& msg )
{
    auto evt = toEventObject( msg );
    if (evt.isEmpty())
        return;

    auto nsp = evt[ EVT_NSP ].toString();
    if (nsp == QStringLiteral("/")) {
        handleEvent( evt );
        return;
    }

    auto i = guiIos_.find( nsp );
    while (i != guiIos_.end() && i.key() == nsp) {
        i.value()->handleEvent( evt );
        ++i;
    }
}

QJsonObject GuiIOServerPrivate::toEventObject( const QString& msg ) const
{
    if (msg.isEmpty())
        return QJsonObject{};

    QJsonParseError err;
    auto jsonDoc = QJsonDocument::fromJson( msg.toUtf8(), &err );

    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
        return QJsonObject{};

    auto evtObj = jsonDoc.object();
    auto keys = evtObj.keys();

    if (!keys.contains( EVT_NSP ) || !keys.contains( EVT_NAME ) || !keys.contains( EVT_DATA ))
        return QJsonObject{};

    return evtObj;
}

GuiIOServer::GuiIOServer( QObject* parent )
    : GuiIO( *new GuiIOServerPrivate( this ),  parent )
{
    Q_D( GuiIOServer );
    d->init( "/", this );
    connect( &(d->wsServer_), &QWebSocketServer::closed, this, [this](){
        Q_D( GuiIOServer );
        d->onClosed();
    });
}

GuiIOServer::~GuiIOServer()
{
    // TODO: remove all guiIO clients
}

void GuiIOServer::listen( quint16 port )
{
    Q_D(GuiIOServer);
    d->listen( port );
}

QPointer<GuiIO> GuiIOServer::ioOf( const QString& nameSpace )
{
    Q_D( GuiIOServer );
    auto io = new GuiIO( this );
    io->d_ptr->init( nameSpace, this );
    d->guiIos_.insert( nameSpace, io->d_ptr.data() );

    connect( io, &GuiIO::destroyed, this, [this]() {
        auto dyingIo = qobject_cast<GuiIO*>( sender() );
        if (!dyingIo)
            return;

       // TODO connect to destroy signal and remove destroyed io from hash
    });

    return io;
}
