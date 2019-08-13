import QtQuick 2.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("chip8")

    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("File")
            MenuItem
            {
                text: qsTr("&Open")
                onTriggered: romFilePicker.open()
            }

            FileDialog
            {
                id: romFilePicker
                title: "Please choose a chip8 rom"
                onAccepted:
                {
                    interpreter.loadRom(romFilePicker.fileUrl)
                    console.log("You chose: " + romFilePicker.fileUrls)
                }

                onRejected:
                {
                    console.log("Cancelled")
                }
            }

            MenuItem
            {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Column {
        x: 70
        y: 9
        width: 500
        height: 125

        Item {
            id: cpuFrequencyItem
            property int value: 500

            function update(newValue)
            {
                //if (newValue !== cpuFrequencyItem.value)
                //{
                cpuFrequencyItem.value = newValue
                interpreter.setCpuFrequency(newValue)
                //}
            }

            Text {
                id: cpuText

                text: qsTr("CPU Frequency:")

                // Style
                x: 25
                y: 2
                width: 98
                height: 16
                anchors.verticalCenterOffset: 39
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12

            }

            Slider {
                id: cpuFrequencySlider

                value: cpuFrequencyItem.value
                from: 1
                to: 1000
                onValueChanged: cpuFrequencyItem.update(value)

                // Style
                x: 177
                y: 2
                anchors.verticalCenterOffset: 40
                anchors.verticalCenter: parent.verticalCenter

            }

            TextEdit {
                id: cpuTextEdit

                text: cpuFrequencyItem.value
                onTextChanged: cpuFrequencyItem.update(Number(text))

                // Style
                x: 398
                y: 2
                width: 80
                height: 20
                anchors.verticalCenterOffset: 43
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12

            }
        }

        Item {
            id: timersFrequencyItem
            property int value: 60

            function update(newValue)
            {
                //if (newValue !== cpuFrequencyItem.value)
                //{
                timersFrequencyItem.value = newValue
                interpreter.setTimersFrequency(newValue)
                //}
            }

            Text {
                id: timersText

                text: qsTr("Timers Frequency:")

                // Style
                x: 24
                width: 98
                height: 16
                anchors.verticalCenterOffset: 85
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12

            }

            Slider {
                id: timersFrequencySlider

                value: timersFrequencyItem.value
                from: 1
                to: 300
                onValueChanged: timersFrequencyItem.update(value)

                // Style
                x: 182
                y: 7
                anchors.verticalCenterOffset: 85
                anchors.verticalCenter: parent.verticalCenter
            }

            TextEdit {
                id: timersTextEdit

                text: timersFrequencyItem.value
                onTextChanged: timersFrequencyItem.update(Number(text))

                // Style
                x: 399
                y: 7
                width: 80
                height: 20
                anchors.verticalCenterOffset: 89
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
            }
        }

    }
}
