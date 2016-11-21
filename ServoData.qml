import QtQuick 2.0
import QtQuick.Window 2.2

Item {
    property int leftMargin: Screen.pixelDensity*3

    Flickable{
        contentHeight: addressBlock.height
        contentWidth: addressBlock.width
        anchors.fill: parent
       // movingHorizontally: false

        Column{
        id: addressBlock
        width: Screen.pixelDensity*50
        spacing: leftMargin

        anchors{
            top:parent.top
            left:parent.left
        }



        InputField{
            id: ipInput

            width:leftMargin*27
            value:"192.168.0.129"
        }


        Button{
            id: connectButton
            text:"Connect"
            onClick: {
                var res = sData.Connect(ipInput.value);
                color=(res==true)? "green":"red"
                if(res) {
                    sData.GetDataForServo()
                }
            }

        }

        Label{
            id:servolbl

            text:"Servo #"
        }

        Row{
            spacing: leftMargin
            InputField{
                id: servoInput
                value: sData.currentServo
                onEnter: {
                    sData.setCurrentServo(value)
                }
            }
            Button{
                id:selectButton
                text: "Set"
                color:"Green"
                onClick: {
                    sData.setCurrentServo(servoInput.value)
                }
            }
        }


        Row{
            spacing: leftMargin
            Label{
                id:adapterLable
                text: "Adapter"
            }
            InputField{
                id: adapterInput
                value: sData.adapterNumber
            }
        }
        Row{
            spacing: leftMargin
            Label{
                id: connectorLabel

                text: "Connector"
            }
            InputField{
                id:portInput
                value: sData.portNumber
            }
        }

        Row{
            spacing: leftMargin
            Button{

                id: buttonOn
                color:(sData.on==false) ? "Red" : "Green"
                text: sData.on ? "ON" : "OFF"
                onClick: {
                    if(sData.on == false){
                        sData.setOn(true)
                    }
                    else
                    {
                        sData.setOn(false)
                    }
                    sData.UpdateOnOff()
                }
            }

            Button{
                color: "yellow"
                text:"SET"
                onClick: {
                    sData.setAdapterNumber(adapterInput.value)
                    sData.setPortNumber(portInput.value)
                    sData.SetAdapterAndPort()
                }
            }
        }
        Row{
            spacing: leftMargin
            Button{
                id: plusButton
                text:"+"
                color: "green"
                onClick: {sData.AngleInc()}
            }

            InputField{
                id: rawInput
                value: sData.currentData
                onEnter: {
                    sData.setCurrentData(value)
                    slider.value=(sData.currentData-150)/4.5
                }
                onValueChanged: slider.value=(sData.currentData-150)/4.5
            }
        }


        Button{
            id: minusButton
            text:"-"
            color: "green"
            onClick: {sData.AngleDec()}
        }


        HorizontalSlider{
            id:slider
            value:(sData.currentData-150)/4.5

            width:leftMargin*27
            onUpdate: {
                sData.setCurrentData(value*4.5+150)
            }
        }

        Row{
            spacing: leftMargin
            InputField{
                id: firstAngle

            }

            Button{
                id: firstSet
                text: "Set"
                color: "yellow"
                onClick: {
                    sData.setFirstData(sData.currentData)
                    sData.setFirstAngle(firstAngle.value)
                    color="green"
                }
            }
        }

        Row{
            spacing: leftMargin

            InputField{
                id: secondAngle
            }

            Button{
                id: secondSet
                text: "Set"
                color: "yellow"
                onClick: {
                    sData.setSecondData(sData.currentData)
                    sData.setSecondAngle(secondAngle.value)
                    color="green"
                }
            }

        }

        Button{
            text: "Done"
            color: "yellow"
            onClick: {
                firstSet.color="yellow"
                secondSet.color="yellow"

                sData.SendCalibrationData() }
        }

    }



}





}
