import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    id: debugView
    state: "hidden"
    width: column.width + 2*column.margin
    anchors.right: parent.right
    anchors.rightMargin: 0
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    Column {
        id: column
        anchors.right: parent.right
        property int margin: 10
        anchors.margins: margin 

        FrequencySlider {
            id: cpuSlider
            label: "CPU Frequency"
            minValue: 0
            maxValue: 1000
            value: 500
            function updateFun(newValue) {
                chip8Interpreter.setCpuFrequency(newValue)
            }
        }

        FrequencySlider {
            id: timersSlider
            label: "Timers Frequency"
            minValue: 0
            maxValue: 300
            value: 60
            function updateFun(newValue) {
                chip8Interpreter.setTimersFrequency(newValue)
            }
        }

        Button {
            text: qsTr("Reset Defaults")
            onClicked: {
                cpuSlider.value = 500
                timersSlider.value = 60
            }
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 30

            // Style
            // TODO possition under theslider
            //anchors.horizontalCenter: timersSlider.frequencySlider.horizontalCenter
        }
    }

    states: [
        State {
            name: "visible"
            PropertyChanges {
                target: debugView
                anchors.rightMargin: 0
            }
            PropertyChanges {
                target: chip8InterpreterScreen
                width: window.width - debugView.width

            }
        },
        State {
            name: "hidden"
            PropertyChanges {
                target: debugView
                anchors.rightMargin: -debugView.width
            }
            PropertyChanges {
                target: chip8InterpreterScreen
                width: window.width

            }
        }
    ]

    transitions: [
        Transition {
            from: "hidden"
            to: "visible"
            NumberAnimation {
                properties:"anchors.rightMargin"
                duration: 400
            }
            NumberAnimation {
                properties:"width"
                duration: 400
            }
        },
        Transition {
            from: "visible"
            to: "hidden"
            NumberAnimation {
                properties:"anchors.rightMargin"
                duration: 400
            }
            NumberAnimation {
                properties:"width"
                duration: 400
            }
        }
    ]

}
