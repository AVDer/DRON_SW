import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    TextInput {
        anchors.horizontalCenter: parent.horizontalCenter

        text: processor.adcValue
        horizontalAlignment : TextInput.AlignHCenter
        font.pointSize: 42
        color: "red"
    }
}
