import QtQuick 2.0
import QtQuick.Window 2.2

Rectangle {
    property int value: 0
    property int minValue: 0
    property int maxValue: 100

    color: "grey"
    border.width: 1
    border.color: "lightBlue"
    height:Screen.pixelDensity*10
    Rectangle{
        color: "blue"
        anchors.left: parent.left
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        width: parent.width/100*value
    }
    signal update()
    MouseArea{
        anchors.fill: parent
        onClicked: {
            value=mouseX/parent.width*100
            parent.update();
        }
    }

}

