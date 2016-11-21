import QtQuick 2.0
import QtQuick.Window 2.2

Rectangle{

    property alias value: input.text
    width: Screen.pixelDensity*20
    height:Screen.pixelDensity*8

    color: "lightBlue"

    signal enter()
    TextInput{
        id: input
        text:"0"
        anchors.fill: parent
        font.pixelSize: parent.height
        onAccepted: {
            parent.enter()
        }
    }
}
