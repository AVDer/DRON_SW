import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import Qt.labs.settings 1.0

import dron.FileManager 1.0


GridLayout {
    id: settings_page
    anchors.centerIn: parent
    columns: 3

    Text {text: " "}
    Text {text: " "}
    Text {text: " "}

    Text {text: qsTr("Braking time")}
    TextField {
        id: break_input
        text: measureSettings.brakeTime
        onTextChanged: {
            //break_input.focus = false
            measureSettings.brakeTime = break_input.text
        }
    }
    Text {text: qsTr("ms")}

    Text {text: qsTr("Delay")}
    TextField {
        id: delay_input
        text: measureSettings.delay
        onTextChanged: {
            //delay_input.focus = false
            measureSettings.delay = delay_input.text
        }
    }
    Text {text: qsTr("s")}

    Text {text: qsTr("Directory")}
    Text {
        id: file_dir_part
        text: file_manager.directory
        Layout.columnSpan: 2
    }

    Text {text: qsTr("File")}
    TextField {
        id: file_file_part
        text: file_manager.filename
    }
    Button {
        text: qsTr("Browse")
        onClicked: fileDialog.open()
    }

    Text {text: qsTr("Port")}
    ComboBox {
        id: port_selection_box
        model: measureSettings.com_port_names
        Layout.columnSpan: 2
        Layout.fillWidth: true
        onCurrentTextChanged: measureSettings.selectedPort = currentText
    }

    FileManager {
        id: file_manager
    }


    Item {
        visible: false
        FileDialog {
            id: fileDialog
            title: "Please choose a file"
            folder: shortcuts.home

            onAccepted: {
                file_manager.filename = fileDialog.fileUrl
            }
        }
    }

    Settings {
        property alias break_time: break_input.text
        property alias delay: delay_input.text
        property alias work_dir: file_dir_part.text
        property alias work_file: file_file_part.text
    }
}
