import QtQuick 2.0
import QtQuick.Window 2.2

Item {
    property alias text: label.text
    width: Screen.pixelDensity*30
    height: Screen.pixelDensity*5
    //border.width: 1
    //border.color: "green"
    Text{
        id: label
        text:"---"
        anchors.fill: parent
        font.pixelSize:  parent.height
    }

}

