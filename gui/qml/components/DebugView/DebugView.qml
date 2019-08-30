import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    visible: false
    width: 300
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    Column {
        anchors.right: parent.right
        anchors.margins:10 

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

            // Style
            // TODO possition under theslider
            anchors.horizontalCenter: timersSlider.frequencySlider.horizontalCenter
        }
    }
}
