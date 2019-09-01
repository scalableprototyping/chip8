import QtQuick 2.13
import QtQuick.Controls 2.13

import "components"
import "components/DebugView"

ApplicationWindow
{
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("chip8")

    menuBar: TopMenu {
    }

    /*
    DebugView {
        id: debugView
    }
    */

   // Live Preview
   property alias  debugView: _loader.item
   Loader {
       id: _loader
   
       function reload() {
           source = ""
           qmlEngine.clearCache()
           source = "components/DebugView/DebugView.qml"
       }
   
       source: "components/DebugView/DebugView.qml"
       anchors.fill: parent
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
   // End of Live Preview

    Chip8InterpreterScreen {
        id: chip8InterpreterScreen
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }
}
