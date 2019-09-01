import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    state: "visible"
    width: 450
    anchors.right: parent.right
    anchors.rightMargin: 0
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    property int menuAminationDuration: 300

    states: [
        State {
            name: "visible"
            PropertyChanges {
                target: sideMenu
                anchors.rightMargin: 0
                visible: true
            }
            PropertyChanges {
                target: chip8InterpreterScreen
                width: root.width - sideMenu.width

            }
        },
        State {
            name: "hidden"
            PropertyChanges {
                target: sideMenu
                visible: false
                anchors.rightMargin: -sideMenu.width
            }
            PropertyChanges {
                target: chip8InterpreterScreen
                width: root.width
            }
        }
    ]

    transitions: [
        Transition {
            from: "hidden"
            to: "visible"
            SequentialAnimation {
                PropertyAnimation {
                    properties:"visible"
                }
                ParallelAnimation {
                    NumberAnimation {
                        properties:"anchors.rightMargin"
                        duration: menuAminationDuration
                    }
                    NumberAnimation {
                        properties:"width"
                        duration: menuAminationDuration
                    }
                }
            }
        },
        Transition {
            from: "visible"
            to: "hidden"
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation {
                        properties:"anchors.rightMargin"
                        duration: menuAminationDuration
                    }
                    NumberAnimation {
                        properties:"width"
                        duration: menuAminationDuration
                    }
                }
                PropertyAnimation {
                    properties:"visible"
                }
            }
        }
    ]

}
