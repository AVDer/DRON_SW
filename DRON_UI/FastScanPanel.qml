import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Grid {
    anchors.centerIn: parent
    columns: 3
    spacing: 10

    Text {text: " "}
    Text {text: " "}
    Text {text: " "}

    Text {text: qsTr("Start angle")}
    TextField {
        id: f_start_angle
        text: processor.startAngle
        validator: DoubleValidator {}
        onTextChanged: {
            //f_start_angle.focus = false
            processor.startAngle = f_start_angle.text
        }
    }
    Text {text: qsTr("°")}

    Text {text: qsTr("Stop angle")}
    TextField {
        id: f_stop_angle
        text: processor.stopAngle
        validator: DoubleValidator {}
        onTextChanged: {
            //f_stop_angle.focus = false
            processor.stopAngle = f_stop_angle.text
        }
    }
    Text {text: qsTr("°")}
}

