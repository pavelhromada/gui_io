/**
 * MIT License
 *
 * Copyright (c) 2016-2017 Pavel Hromada
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef GUIIO_H
#define GUIIO_H

#include <functional>
#include <QObject>
#include <QString>
#include <QJsonValue>
#include <QScopedPointer>
#include <QSharedPointer>

namespace detail {

class AbstractEvent {
public:
    virtual ~AbstractEvent() = default;
    virtual void onEvent( const QJsonValue& data ) = 0;
};

class Event : public AbstractEvent {
public:
    Event( std::function<void(const QJsonValue&)>&& f ) : f_(f) {}
    ~Event() override = default;
    void onEvent( const QJsonValue& data ) override { f_( data ); }
private:
    std::function<void(const QJsonValue&)> f_;
};

} // namespace detail

class GuiIOServer;
class GuiIOPrivate;

class GuiIO : public QObject
{
    Q_OBJECT
public:
    explicit GuiIO( QObject* parent = nullptr );
    ~GuiIO();

    QString namespaceId() const;

#ifdef Q_QDOC
    void on( const QString& event, const QObject* receiver, PointerToMemberFunction method );
    void on( const QString& event, Functor functor );
#else
    template <typename Handler>
    void on( const QString& event, Handler handler ) {
        onImpl( event, QSharedPointer<detail::Event>::create( handler ));
    }

    template <typename Class>
    void on( const QString& event, Class* receiver, void(Class::*member)(const QJsonValue&) ) {
        using std::placeholders::_1;
        onImpl( event, QSharedPointer<detail::Event>::create( std::bind( member, receiver, _1 )));
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
    void onImpl( const QString& event, const QSharedPointer<detail::AbstractEvent>& callback );
};

#endif // GUIIO_H
