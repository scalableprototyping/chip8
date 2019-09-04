import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.topMargin: 30
    width: 350; 

    ListView {
        id: disassembly
        anchors.fill: parent
        clip: true

        ScrollBar.vertical: ScrollBar {}

        function scrollToBottom() {
            disassembly.positionViewAtIndex(disassembly.count - 1, ListView.Visible)
        }

        model: ListModel {
            id: disassemblyModel
        }

        delegate: Row {
            Text { text: instruction; width: 160 }
        }

    }

    Connections {
        target: chip8Interpreter
        onDisassemblyCompleted: {
            if (disassemblyModel.count >= 200) {
                disassemblyModel.remove(0)
            }
            disassemblyModel.append({
                instruction: message
            })
            disassembly.positionViewAtIndex(disassembly.count - 1, ListView.End)
        }
    }

}
