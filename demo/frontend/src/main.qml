import QtQuick 2.4
import QtQuick.Controls 1.3
import GuiIOClient 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: Qt.resolvedUrl( "views/ViewLogin.qml" )
    }

    GuiIOClient {
        url: "ws://127.0.0.1:9000"

        onConnected: console.log( "client connected" );
        onDisconnected: console.log( "client disconnected" );
        onError: console.log( "client connection error " + errorString );

        Component.onCompleted: {
            on( 'showView', function (data) {
                stack.push( Qt.resolvedUrl( "views/" + data + ".qml" ))
            });
        }
    }
}
