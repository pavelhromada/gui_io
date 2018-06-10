# GuiIO

GuiIO is a simple client/server library written in Qt and inspired by socket.io.
Websocket is used for communication. Server side is implemented as C++ library
and for client QML module is available.

## Hello World


#### Setup a server
```C++
GuiIOServer s;

s.on( "hello world", [](const QJsonValue&) {
    qDebug() << "hello world event received";
});

s.listen( 3000 ); // choose port
```

#### Setup a client
```qml
ApplicationWindow {
    GuiIOClient {
        id: clientIo
        url: "ws://127.0.0.1:3000"

        onConnected: clientIo.invoke( 'hello world' );
    }
}
```

## Namespaces
#### Server side
Each GuiIO instance works within its own namespace. GuiIOServer itself is a
GuiIO instance and works within top level namespace (as '/' in socket.io).
To create new namespace one have to do it via GuiIOServer like this:
```C++
auto io1 = server.ioOf( "my_namespace1" );
auto io2 = server.ioOf( "my_namespace2" );
```

#### Client side
Precondition is that GuiIOClient instance is created. Then you can declare
GuiIO instances with their namespaces.
```qml
Item {
    GuiIO {
        id: io1
        namespace: "my_namespace1"
    }

    GuiIO {
        id: io2
        namespace: "my_namespace2"
    }
}
```

## Binding to events
#### Server side
```C++
auto io = server.ioOf( "my_namespace" );

// bind with lambda or free standing function
io->on( "foo event", [](const QJsonValue& data) {
    qDebug() << "foo event received with data" << data;
});

// bind with member function
FooBar* obj = ...;
io->on( "bar event", obj, &FooBar::barMethod );
```

#### Client side
```qml
Item {
    GuiIO {
        id: io1
        namespace: "my_namespace"

        Component.onCompleted: {
            on( 'fooBarEvent', function (data) {
                console.log( 'fooBarEvent received with data', data );
            });
        }
    }
}
```

## Emit event
#### Server side
```C++
auto io = ...;

// without data
io->invoke( "fooEvent" );

// with simple data
io->invoke( "fooEvent", 25 );

// with some JSON data
io->invoke( "fooEvent", QJsonObject {
      { "name", "James" },
      { "surname", "Bond" }
} );
```

#### Client side
```qml
Item {
    Button {
        text: "Button One"
        onClicked: io.invoke( 'barEvent' ) // without data
    }

    Button {
        text: "Button Two"
        onClicked: io.invoke( 'barEvent', { hello: "world" } ) // with JSON data
    }

    GuiIO {
        id: io
        namespace: "my_namespace"
    }
}
```

## License

MIT
