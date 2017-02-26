import QtQuick 2.4
import GuiIOClient.Private 1.0

GuiIO {
    id: client

    property url url
    property string errorString

    signal connected()
    signal disconnected()
    signal error()

    namespace: "/"

    Component.onCompleted: {
        GuiClientDispatcher.init( client );
        GuiClientDispatcher.run();
    }
}
