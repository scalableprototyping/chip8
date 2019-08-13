import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Grid {
        id: grid
        anchors.fill: parent
        rows: 32
        columns: 64

        Repeater {
            model: grid.columns * grid.rows;
            delegate: delegateGridImage
        }
    }

    Component {
        id: delegateGridImage

        Item {
            id: gridItem
            property int currentColumn: index % grid.columns
            property int currentRow: Math.floor(index / grid.rows);

            property bool pixel_state: false

            // Resize to screen size
            width: grid.width / grid.columns
            height: grid.height / grid.rows

            Rectangle {
                id: pixel
                anchors.fill: parent

                color: if (gridItem.pixel_state == true ) { "white" } else { "black" }
            }

        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        property bool pixel_activate: true

        onPressed: {
            var child = grid.childAt(mouse.x, mouse.y)
            child.pixel_state ^= true
            pixel_activate = child.pixel_state
        }

        onPositionChanged: {
            if (!pressed) return;
            var child = grid.childAt(mouse.x, mouse.y)
            child.pixel_state = pixel_activate
        }
    }
}
