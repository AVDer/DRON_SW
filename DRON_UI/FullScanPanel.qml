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
        text: measureSettings.startAngle
        onTextChanged: {
            //n_start_angle.focus = false
            measureSettings.startAngle = n_start_angle.text
        }
    }
    Text {text: qsTr("°")}

    Text {text: qsTr("Stop angle")}
    TextField {
        id: n_stop_angle
        text: measureSettings.stopAngle
        onTextChanged: {
            //n_stop_angle.focus = false
            measureSettings.stopAngle = n_stop_angle.text
        }
    }
    Text {text: qsTr("°")}

    Text {text: qsTr("Step")}
    TextField {
        id: step_input
        text: measureSettings.step
        onTextChanged: {
            //step_input.focus = false
            measureSettings.step = step_input.text
        }
    }
    Text {text: qsTr("°")}

    Text {text: qsTr("Exposition")}
    TextField {
        id: exp_input
        text: measureSettings.exposition
        onTextChanged: {
            //exp_input.focus = false
            measureSettings.exposition = exp_input.text
        }
    }
    Text {text: qsTr("s")}

    Settings {
        property alias start_angle: n_start_angle.text
        property alias stop_angle: n_stop_angle.text
        property alias step: step_input.text
        property alias exposition: exp_input.text
    }

}
