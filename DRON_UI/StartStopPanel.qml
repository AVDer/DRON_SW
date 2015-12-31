import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    property int margin: 5
    height: start_button.height + 2 * margin

    SimpleButton {
        id: start_button
        anchors.right: parent.right; anchors.rightMargin: margin
        anchors.verticalCenter: parent.verticalCenter
        button_text: qsTr("Stop")
    }

    SimpleButton {
        id: pause_button
        anchors.right: start_button.left; anchors.rightMargin: margin
        anchors.verticalCenter: parent.verticalCenter
        button_text: qsTr("Pause")
    }

    SimpleButton {
        id: stop_button
        anchors.right: pause_button.left; anchors.rightMargin: margin
        anchors.verticalCenter: parent.verticalCenter
        button_text: qsTr("Start")
    }
}

