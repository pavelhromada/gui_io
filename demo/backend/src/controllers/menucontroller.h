#ifndef VIEWMENUCONTROLLER_H
#define VIEWMENUCONTROLLER_H

#include <QObject>
#include <QPointer>
#include <guiio.h>

class MenuController : public QObject
{
    Q_OBJECT
public:
    MenuController( const QPointer<GuiIO>& io );

private slots:
    void onClickMeTooClicked( const QJsonValue& );
    void onLogOut( const QJsonValue& );

private:
    QPointer<GuiIO> io_;
};

#endif // VIEWMENUCONTROLLER_H
