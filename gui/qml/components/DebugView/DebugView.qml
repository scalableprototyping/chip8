import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    property alias sideMenu: debugViewSideMenu
    anchors.fill: parent

    SideMenu {
        id: debugViewSideMenu

        Column {
            id: sliders
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top

            property int margin: 10
            anchors.margins: margin 
            spacing: 10

            ValueSlider {
                id: cpuSlider
                label: "CPU Frequency"
                minValue: 1
                maxValue: 1000
                defaultValue: 500
                units: "Hz"
                function updateFun(newValue) {
                    chip8Interpreter.SetCpuFrequency(newValue)
                }
            }

            ValueSlider {
                id: timersSlider
                label: "Timers Frequency"
                minValue: 1
                maxValue: 300
                defaultValue: 60
                units: "Hz"
                function updateFun(newValue) {
                    chip8Interpreter.SetTimersFrequency(newValue)
                }
            }

            ValueSlider {
                id: pixelOnSlider
                label: "Pixel Off Delay"
                minValue: 0
                maxValue: 1000
                defaultValue: 125
                units: "ms"
                function updateFun(newValue) {
                    chip8InterpreterScreen.pixelOffDelay = newValue
                }
            }

            ValueSlider {
                id: pixelOffSlider
                label: "Pixel On Delay"
                minValue: 0
                maxValue: 1000
                defaultValue: 0
                units: "ms"
                function updateFun(newValue) {
                    chip8InterpreterScreen.pixelOnDelay = newValue
                }
            }
        }

        Column {
            id: buttons
            anchors.top: sliders.bottom
            anchors.topMargin: 10
            spacing: 10

            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: qsTr("Reset Defaults")
                onClicked: {
                    cpuSlider.resetDefaultValue()
                    timersSlider.resetDefaultValue()
                    pixelOnSlider.resetDefaultValue()
                    pixelOffSlider.resetDefaultValue()
                }
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                anchors.margins: 15
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                Button {
                    text: "Continue"
                    onClicked: {
                        chip8Interpreter.Play()
                    }
                }
                Button {
                    text: "Pause"
                    onClicked: {
                        chip8Interpreter.Pause()
                    }
                }
                Button {
                    text: "Step"
                    onClicked: {
                        chip8Interpreter.Step()
                    }
                }
            }
        }

        Grid {
            id: registersGrid
            rows: 4
            columns: 4
            spacing: 10
            anchors.top: buttons.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter

            Repeater {
                anchors.topMargin: 20
                id: registers
                model: 16
                delegate: registerComponent
            }
        }

        Component {
            id: registerComponent
            Row {
                Text {
                    text: "R" + index + ": "
                }
                Text {
                    text: "0"
                    // TODO: connect C++ model to link with the register values so the changes are reflected
                }

            }

        }
   }
}
