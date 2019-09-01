import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    property alias sideMenu: debugViewSideMenu
    anchors.fill: parent

    SideMenu {
        id: debugViewSideMenu

         Column {
             id: column
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.top: parent.top
             anchors.bottom: parent.bottom

             property int margin: 10
             anchors.margins: margin 

             ValueSlider {
                 id: cpuSlider
                 label: "CPU Frequency"
                 minValue: 1
                 maxValue: 1000
                 defaultValue: 500
                 units: "Hz"
                 function updateFun(newValue) {
                     chip8Interpreter.setCpuFrequency(newValue)
                 }
             }

             ValueSlider {
                 id: timersSlider
                 label: "Timers Frequency"
                 minValue: 1
                 maxValue: 300
                 defaultValue: 60
                 units: "Hz"
                 function updateFun(newValue) {
                     chip8Interpreter.setTimersFrequency(newValue)
                 }
             }

             ValueSlider {
                 id: pixelOnSlider
                 label: "Pixel Off Delay"
                 minValue: 0
                 maxValue: 1000
                 defaultValue: 125
                 units: "ms"
                 function updateFun(newValue) {
                     chip8InterpreterScreen.pixelOffDelay = newValue
                 }
             }

             ValueSlider {
                 id: pixelOffSlider
                 label: "Pixel On Delay"
                 minValue: 0
                 maxValue: 1000
                 defaultValue: 0
                 units: "ms"
                 function updateFun(newValue) {
                     chip8InterpreterScreen.pixelOnDelay = newValue
                 }
             }

             Button {
                 text: qsTr("Reset Defaults")
                 onClicked: {
                     cpuSlider.resetDefaultValue()
                     timersSlider.resetDefaultValue()
                     pixelOnSlider.resetDefaultValue()
                     pixelOffSlider.resetDefaultValue()
                 }
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.horizontalCenterOffset: 30
             }
         }
    }
}
