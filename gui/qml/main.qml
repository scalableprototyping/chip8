import QtQuick 2.13
import QtQuick.Controls 2.13

import "components"
import "components/DebugView"

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("chip8")

    menuBar: TopMenu {
    }

    DebugView {
        id: debugView
    }
}
