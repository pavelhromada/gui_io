#ifndef GUIIOSERVER_H
#define GUIIOSERVER_H

#include <QPointer>
#include "guiio.h"

class GuiIOServerPrivate;

class GuiIOServer : public GuiIO
{
    Q_OBJECT
public:
    explicit GuiIOServer( QObject *parent = nullptr );
    ~GuiIOServer();

    void listen( quint16 port = 0 );

    // creates new object with 'this' as parent
    QPointer<GuiIO> ioOf( const QString& nameSpace );

Q_SIGNALS:
    void connected();
    void disconnected();

private:
    Q_DISABLE_COPY(GuiIOServer)
    Q_DECLARE_PRIVATE(GuiIOServer)
};

#endif // GUIIOSERVER_H
