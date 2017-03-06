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
    void init( const QString& nsp, GuiIOServer* ioServer );
    void useSocket( QWebSocket* socket );
    void handleEvent( const QJsonObject& evt );
    void invokeEvent( const QString& event, const QJsonValue& data );

    Q_DECLARE_PUBLIC( GuiIO )

    GuiIO* const q_ptr = nullptr;
    QString nsp_;
    QHash<QString, QSharedPointer<detail::AbstractEvent>> eventCallbacks_;
    GuiIOServer* server_ = nullptr;
    QWebSocket* wsSocket_ = nullptr;
};

#endif // GUIIOPRIVATE_H
