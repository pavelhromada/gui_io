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

#include "../include/guiio.h"
#include "../include/guiioserver.h"
#include "guiio_p.h"

GuiIO::GuiIO( QObject* parent )
    : QObject( parent )
    , d_ptr( new GuiIOPrivate{ this } )
{}

GuiIO::GuiIO( GuiIOPrivate& d , QObject* parent )
    : QObject( parent )
    , d_ptr( &d )
{}

GuiIO::~GuiIO()
{}

QString GuiIO::namespaceId() const
{
    return d_ptr->nsp_;
}

void GuiIO::invoke( const QString& event, const QJsonValue& data )
{
    d_ptr->invokeEvent( event, data);
}

GuiIOServer *GuiIO::server() const
{
    return d_ptr->server_;
}

void GuiIO::onImpl( const QString& event, const QSharedPointer<detail::AbstractEvent>& callback )
{
    d_ptr->eventCallbacks_[event] = callback;
}
