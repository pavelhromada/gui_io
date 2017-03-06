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

#include <QJsonDocument>
#include <QJsonObject>
#include "guiio_p.h"

GuiIOPrivate::GuiIOPrivate( GuiIO* qptr )
    : q_ptr( qptr )
{}

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
    if (!eventCallbacks_.contains( evt[ EVT_NAME ].toString() ))
        return;

    auto callback = eventCallbacks_[ evt[ EVT_NAME ].toString() ];
    emit callback->onEvent( evt[ EVT_DATA ] );
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
