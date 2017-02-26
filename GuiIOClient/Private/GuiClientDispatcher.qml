import QtQuick 2.4
import QtWebSockets 1.0

pragma Singleton

Object {
    function run() {
        if (!_client)
            return;

        socket.url = _client.url;
        //socket.active = true;
    }

    function attachIO( io ) {
        var idx = _io.indexOf( io );
        if (idx != -1)
            _io[ idx ] = io;
        else
            _io.push( io );
    }

    function detachIO( io ) {
        var idx = _io.indexOf( io );
        if (idx != -1)
            return _io.splice( idx, 1 );
    }

    function init( client ) {
        _client = client;
    }

    function send( namespace, evt, data ) {
        if (socket.status === WebSocket.Open) {
            socket.sendTextMessage( JSON.stringify( {
                "nsp": namespace,
                "evt": evt,
                "data": data ? data : null
            } ));
        } else {
            console.log( "Event wont be emmited. Client is not connected !!!" )
        }
    }

    function reconnect() {
        console.log("GuiIOClient reconnecting...");
        socket.active = false;
        reconnectTimer.start();
    }

    property var _io: []
    property var _client

    Timer {
        id: reconnectTimer
        repeat: false
        interval: 1000
        onTriggered: socket.active = true
    }

    WebSocket {
        id: socket

        onStatusChanged: {
            if (status === WebSocket.Error)
                console.log( "Connection error:", socket.errorString );

            if (!_client)
                return;

            if (status === WebSocket.Open)
                _client.connected();
            else if (status === WebSocket.Closed) {
                _client.disconnected();
                reconnect();
            } else if (status === WebSocket.Error) {
                _client.error();
                reconnect();
            }
        }

        onErrorStringChanged: {
            if (!_client)
                return;

            _client.errorString = errorString;
        }

        onTextMessageReceived: {
            var msg = JSON.parse( message );

            if (!msg.hasOwnProperty( "nsp" ) ||
                !msg.hasOwnProperty( "evt" ) ||
                !msg.hasOwnProperty( "data" )) {
                console.log( "Invalid format of incomming event !!!" );
                return;
            }

            _io.forEach( function (io) {
                if (io.hasOwnProperty( "namespace" ) && io.namespace === msg.nsp)
                    _callEvent( io, msg );
            });
        }

        function _callEvent( io, msg ) {
            if (!io.hasOwnProperty( "_events" )) {
                console.log( "Invalid GuiIO" );
                return;
            }

            for (var e in io._events) {
                if (e === msg.evt) {
                    io._events[e]( msg.data );
                    return;
                }
            }
        }
    }
}
