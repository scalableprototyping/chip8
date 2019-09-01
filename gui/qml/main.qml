import QtQuick 2.13
import QtQuick.Controls 2.13

import "components"
import "components/DebugView"

ApplicationWindow
{
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("chip8")

    menuBar: TopMenu {
    }

    DebugView {
        id: debugView
    }

    Chip8InterpreterScreen {
        id: chip8InterpreterScreen
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }
}
