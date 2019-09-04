import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    anchors.topMargin: 20
    anchors.horizontalCenter: parent.horizontalCenter
    width: registersGrid.width
    height: registersGrid.height

    Grid {
        id: registersGrid
        rows: 4
        columns: 4
        spacing: 10
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Repeater {
            id: registers
            property int numberOfRegisters: 16
            model: numberOfRegisters
            delegate: registerComponent
            anchors.topMargin: 20
        }
    }

    Component {
        id: registerComponent
        Item {
            id: registersItem
            property int value
            width: 50
            height: 15
            Row {
                Text {
                    text: "R" + index + ": "
                }
                Text {
                    text: value
                    // TODO: connect C++ model to link with the register values so the changes are reflected
                }

            }
        }
    }

    Connections {
        target: chip8Interpreter
        onTickTimersCompleted: {
            var i
            for (i = 0; i < registers.numberOfRegisters; i++) {
                var register = registers.itemAt(i)
                register.value = chip8Interpreter.GetDataRegister(i)
            }
        }
    }

}
