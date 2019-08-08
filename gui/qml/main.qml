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

            MenuItem
            {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Slider
    {
        id: cpuFrequencySlider
        from: 1
        to: 1000
        value: 500
        onValueChanged: interpreter.SetCpuFrequency(value)
    }

    Slider
    {
        id: timersFrequencySlider
        from: 1
        to: 100
        value: 60
        onValueChanged: interpreter.SetTimersFrequency(value)
        y: 50
    }

    FileDialog
    {
        id: romFilePicker
        title: "Please choose a chip8 rom"
        onAccepted:
        {
            interpreter.LoadRom(romFilePicker.fileUrl)
            console.log("You chose: " + romFilePicker.fileUrls)
        }

        onRejected:
        {
            console.log("Cancelled")
        }
    }
}
