import QtQuick 2.3
import QtQuick.Window 2.2
import "qrc:/"
Window {
    width: (Screen.width>1024)? 1024 : Screen.width
    height:(Screen.height>1800) ? 1800 : Screen.height
    visible: true
    Rectangle {
        anchors.fill: parent
        anchors.centerIn: parent
        color:"DarkGreen"


        Rectangle {
            width: parent.width*2
            height: parent.height/2
            rotation: 30
            anchors.centerIn: parent
            color:"lightGreen"

        }


        ServoData {
            width:parent.width
            height:parent.height
            anchors.left: parent.left
            anchors.top: parent.top
        }
    }
}

