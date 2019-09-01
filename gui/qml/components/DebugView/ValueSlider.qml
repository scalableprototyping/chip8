import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    id: valueSlider

    property string label: "Slider"
    property int defaultValue: 50
    property int value: defaultValue
    property int minValue: 0
    property int maxValue: 100
    property string units: ""

    function updateFun(newValue) {}

    function update(newValue) {
        valueSlider.value = newValue
        updateFun(newValue)
    }

    function resetDefaultValue() {
        value = defaultValue
    }

    width: row.width
    height: row.height

    Row {
        id: row
        spacing: 15

        Text {
            text: qsTr(valueSlider.label)

            // Style
            width: 100 
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }

        Slider {
            id: frequencySlider
            value: valueSlider.value
            from: valueSlider.minValue
            to: valueSlider.maxValue
            onValueChanged: valueSlider.update(value)

            // Style
            anchors.verticalCenter: parent.verticalCenter
        }

        TextEdit {
            text: valueSlider.value
            onTextChanged: valueSlider.update(Number(text))

            // Style
            width: 30
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }

        Text {
            text: units

            // Style
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
