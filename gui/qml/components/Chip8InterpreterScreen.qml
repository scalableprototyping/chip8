import QtQuick 2.12

Item {
    id: chip8InterpreterScreen
    property int rows: 32
    property int columns: 64

    property int pixelOnDelay: 100
    property int pixelOffDelay: 300

    Grid {
        id: grid
        anchors.fill: parent
        rows: chip8InterpreterScreen.rows
        columns: chip8InterpreterScreen.columns

        Repeater {
            id: pixels
            model: grid.columns * grid.rows;
            delegate: pixelComponent
        }
    }

    Component {
        id: pixelComponent

        Item {
            id: gridItem
            property int currentColumn: index % grid.columns
            property int currentRow: Math.floor(index / grid.columns);

            property bool pixelIsOn: false
            property int pixelToggleDelay: 100

            width: grid.width / chip8InterpreterScreen.columns
            height: grid.height / chip8InterpreterScreen.rows

            Image {
                source: "../assets/pixel_off.png"
                anchors.fill: parent
            }

            Image {
                id: onImage
                source: "../assets/pixel_on.png"
                opacity: 0                
                anchors.fill: parent
            }

            states: [
                State {
                    name: "on"
                    PropertyChanges {
                        target:onImage
                        opacity: 1
                    }
                },
                State {
                    name: "off"
                    PropertyChanges {
                        target:onImage
                        opacity: 0
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "on"
                    to: "off"
                    NumberAnimation {
                        properties: "opacity"
                        duration: chip8InterpreterScreen.pixelOffDelay
                    }
                },
                Transition {
                    from: "off"
                    to: "on"
                    NumberAnimation {
                        properties: "opacity"
                        duration: chip8InterpreterScreen.pixelOnDelay
                    }
                }
            ]

        }
    }

    Timer {
        interval: 20 // milliseconds
        running: true
        repeat: true
        onTriggered: {
            var i;
            for (i = 0; i < grid.rows*grid.columns; i++) {
                var pixel = pixels.itemAt(i)
                var col = i % grid.columns
                var row = Math.floor(i / grid.columns);
                var pixelIsOn = chip8Interpreter.GetPixelState(col, row)
                if (pixelIsOn == true) {
                    pixel.state = "on"
                } else {
                    pixel.state = "off"
                }
            }
        }
    }

}
