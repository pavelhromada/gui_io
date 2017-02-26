#ifndef GUIIO_H
#define GUIIO_H

#include <QObject>
#include <QString>
#include <QJsonValue>
#include <QScopedPointer>

namespace impl {

class EventHandler : public QObject
{
    Q_OBJECT
public:
    static const EventHandler* get();

Q_SIGNALS:
    void invoked( const QJsonValue& data ) const;
};

} // namespace impl

class GuiIOPrivate;
class GuiIOServer;

class GuiIO : public QObject
{
    Q_OBJECT
public:
    explicit GuiIO( QObject* parent = nullptr );
    ~GuiIO();

    QString namespaceId() const;

    void on( const QString& event, const QObject* receiver, const char* slot );
#ifdef Q_QDOC
    void on( const QString& event, const QObject* receiver, PointerToMemberFunction method );
    void on( const QString& event, Functor functor );
#else
    template <typename Handler>
    void on( const QString& event, Handler handler ) {
        auto invoker = impl::EventHandler::get();
        QObject::connect( invoker, &impl::EventHandler::invoked, handler );
        onImpl( event, invoker );
    }

    template <typename Class>
    void on( const QString& event, const Class* receiver, void(Class::*member)(const QJsonValue&) ) {
        auto invoker = impl::EventHandler::get();
        QObject::connect( invoker, &impl::EventHandler::invoked, receiver, member );
        onImpl( event, invoker );
    }
#endif // Q_QDOC

    void invoke( const QString& event, const QJsonValue& data = QJsonValue() );
    GuiIOServer* server() const;

protected:
    friend class GuiIOServer;
    GuiIO( GuiIOPrivate& d, QObject* parent );
    QScopedPointer<GuiIOPrivate> d_ptr;

private:
    Q_DISABLE_COPY(GuiIO)
    void onImpl( const QString& event, const impl::EventHandler* invoker );
};

#endif // GUIIO_H
