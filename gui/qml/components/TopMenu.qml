import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Dialogs 1.3

MenuBar {

    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("&Open")
            onTriggered: romFilePicker.open()
        }

        FileDialog {
            id: romFilePicker
            title: qsTr("Please choose a chip8 rom")

            onAccepted: {
                chip8Interpreter.LoadRom(romFilePicker.fileUrl)
                console.log("You chose: " + romFilePicker.fileUrls)
            }

            onRejected: {
                console.log("Cancelled")
            }
        }

        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit();
        }
    }

    Menu {
        title: qsTr("View")

        MenuItem {
            checkable: true
            checked: false
            text: qsTr("Debug Tools")
            onToggled: {
                if (checked) {
                    debugView.sideMenu.state = "visible"
                } else {
                    debugView.sideMenu.state = "hidden"
                }
            }
        }
    }
}
