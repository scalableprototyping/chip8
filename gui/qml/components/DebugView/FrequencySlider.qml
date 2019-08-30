import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    id: chip8_slider

    property string label: "Slider"
    property int value: 50
    property int minValue: 0
    property int maxValue: 100

    function updateFun(newValue) {}

    function update(newValue) {
        chip8_slider.value = newValue
        chip8_interpreter_update(newValue)
    }

    width: row.width
    height: row.height

    Row {
        id: row
        spacing: 15

        Text {
            text: qsTr(chip8_slider.label)

            // Style
            width: 100 
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }

        Slider {
            id: frequencySlider
            value: chip8_slider.value
            from: chip8_slider.minValue
            to: chip8_slider.maxValue
            onValueChanged: chip8_slider.update(value)

            // Style
            anchors.verticalCenter: parent.verticalCenter
        }

        TextEdit {
            text: chip8_slider.value
            onTextChanged: chip8_slider.update(Number(text))

            // Style
            width: 30
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }

        Text {
            text: "Hz"

            // Style
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
