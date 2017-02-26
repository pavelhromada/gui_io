#ifndef VIEWLOGINCONTROLLER_H
#define VIEWLOGINCONTROLLER_H

#include <QObject>
#include <QPointer>
#include <guiio.h>

class LoginController : public QObject
{
    Q_OBJECT
public:
    LoginController( const QPointer<GuiIO>& io );

private:
    void onLogin( const QJsonValue& data );

private:
    QPointer<GuiIO> io_;
};

#endif // VIEWLOGINCONTROLLER_H
