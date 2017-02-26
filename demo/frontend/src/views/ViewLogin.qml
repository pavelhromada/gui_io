import QtQuick 2.4
import QtQuick.Controls 1.3
import GuiIOClient 1.0

Item {
    visible: true
    width: 640
    height: 480

    Label {
        text: "Try 'hallo', '4711' ;)"
        anchors{
            top: parent.top
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        TextField {
            id: username
            placeholderText: "Username"
        }

        TextField {
            id: password
            placeholderText: "Password"
        }

        Button {
            text: "Login"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: io.invoke( "validateLogin", { usr: username.text, pwd: password.text })
        }
    }

    GuiIO {
        id: io
        namespace: "view_login"
    }
}
