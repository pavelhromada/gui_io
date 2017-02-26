import QtQuick 2.4
import QtQuick.Controls 1.3
import GuiIOClient 1.0

Item {
    visible: true
    width: 640
    height: 480

    Column {
        anchors.centerIn: parent
        spacing: 20

        Button {
            text: "Click me"
            onClicked: io.invoke( "clickMeClicked" )
        }

        Button {
            text: "Click me too"
            onClicked: io.invoke( "clickMeTooClicked" )
        }

        Button {
            text: "Log out"
            onClicked: io.invoke( "logOutClicked" )
        }
    }

    GuiIO {
        id: io
        namespace: "view_menu"
    }
}
