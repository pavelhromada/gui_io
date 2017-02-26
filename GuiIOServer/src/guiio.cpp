#include "../include/guiio.h"
#include "guiio_p.h"

const impl::EventHandler* impl::EventHandler::get()
{
    return new EventHandler;
}

GuiIO::GuiIO( QObject* parent )
    : QObject( parent )
    , d_ptr( new GuiIOPrivate{ this } )
{}

GuiIO::GuiIO( GuiIOPrivate& d , QObject* parent )
    : QObject( parent )
    , d_ptr( &d )
{}

GuiIO::~GuiIO()
{
    d_ptr->cleanUp();
}

QString GuiIO::namespaceId() const
{
    return d_ptr->nsp_;
}

void GuiIO::on( const QString& event, const QObject* receiver, const char* slot )
{
    auto invoker = impl::EventHandler::get();
    connect( invoker, SIGNAL(invoked(const QJsonValue&)), receiver, slot );
    onImpl( event, invoker );
}

void GuiIO::invoke( const QString& event, const QJsonValue& data )
{
    d_ptr->invokeEvent( event, data);
}

GuiIOServer* GuiIO::server() const
{
    return d_ptr->server_;
}

void GuiIO::onImpl(const QString& event, const impl::EventHandler* invoker )
{
    if (d_ptr->invokers_.contains( event ))
        delete d_ptr->invokers_.value( event );

    d_ptr->invokers_[ event ] = invoker;
}
