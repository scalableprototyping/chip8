import QtQuick 2.0
import QtQuick.Controls 1.0
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
