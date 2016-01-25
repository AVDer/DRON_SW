import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import Qt.labs.settings 1.0

Grid {
    anchors.centerIn: parent
    columns: 3
    spacing: 10

    Text {text: " "}
    Text {text: " "}
    Text {text: " "}

    Text {text: qsTr("Start angle")}
    TextField {
        id: n_start_angle
        text: processor.startAngle
        validator: DoubleValidator {}
        onTextChanged: {
            processor.startAngle = n_start_angle.text
        }
    }
    Text {text: qsTr("°")}

    Text {text: qsTr("Stop angle")}
    TextField {
        id: n_stop_angle
        text: processor.stopAngle
        validator: DoubleValidator {}
        onTextChanged: {
            processor.stopAngle = n_stop_angle.text
        }
    }
    Text {text: qsTr("°")}

    Text {text: qsTr("Step")}
    TextField {
        id: step_input
        text: processor.step
        validator: DoubleValidator {}
        onTextChanged: {
            processor.step = step_input.text
        }
    }
    Text {text: qsTr("x 0.01°")}

    Text {text: qsTr("Exposition")}
    TextField {
        id: exp_input
        text: processor.exposition
        validator: DoubleValidator {}
        onTextChanged: {
            processor.exposition = exp_input.text
        }
    }
    Text {text: qsTr("s")}
}
