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

    Item {
        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            if (event.key == Qt.Key_F5) {
                console.log("reloading")
                _loader.reload()
                event.accepted = true
            }
        }
    }

    Loader {
        id: _loader

        function reload() {
            source = "";
            qmlEngine.clearComponentCache();
            source = "./components/TopMenu.qml";
        }

        anchors.centerIn: parent
        source: "./components/TopMenu.qml"
    }

}
