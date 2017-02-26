import QtQuick 2.4
import GuiIOClient.Private 1.0

Object {
    id: io

    property string namespace: ""

    function invoke( evt, data ) {
        GuiClientDispatcher.send( namespace, evt, data )
    }

    function on( event, callback ) {
        if (!callback)
            return;
        _events[event] = callback;
    }

    property var _events: ({})

    Component.onCompleted: GuiClientDispatcher.attachIO( io )
    Component.onDestruction: GuiClientDispatcher.detachIO( io )
}
