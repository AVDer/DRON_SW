import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    property int margin: 5
    height: start_button.height + 2 * margin

    signal startPressed();

    SimpleButton {
        id: start_button
        button_id: 1
        anchors.right: pause_button.left; anchors.rightMargin: margin
        anchors.verticalCenter: parent.verticalCenter
        button_text: qsTr("Start")
    }
    SimpleButton {
        id: pause_button
        button_id: 2
        anchors.right: stop_button.left; anchors.rightMargin: margin
        anchors.verticalCenter: parent.verticalCenter
        button_text: qsTr("Pause")
    }
    SimpleButton {
        id: stop_button
        button_id: 3
        anchors.right: parent.right; anchors.rightMargin: margin
        anchors.verticalCenter: parent.verticalCenter
        button_text: qsTr("Stop")
    }
}

