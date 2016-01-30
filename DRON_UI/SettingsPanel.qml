import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import Qt.labs.settings 1.0

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
        text: processor.brakeTime
        validator: DoubleValidator {}
        onTextChanged: {
            processor.brakeTime = break_input.text
        }
    }
    Text {text: qsTr("ms")}

    Text {text: qsTr("Delay")}
    TextField {
        id: delay_input
        text: processor.delay
        validator: DoubleValidator {}
        onTextChanged: {
            processor.delay = delay_input.text
        }
    }
    Text {text: qsTr("s")}

    Text {text: qsTr("Directory")}
    Text {
        id: file_dir_part
        text: processor.directory
        Layout.columnSpan: 2
    }

    Text {text: qsTr("File")}
    TextField {
        id: file_file_part
        text: processor.filename
    }
    Button {
        text: qsTr("Browse")
        onClicked: fileDialog.open()
    }

    Text {text: qsTr("Port")}
    ComboBox {
        id: port_selection_box
        model: processor.com_port_names
        Layout.columnSpan: 2
        Layout.fillWidth: true
        onCurrentTextChanged: processor.selectedPort = currentText
    }

    Item {
        visible: false
        FileDialog {
            id: fileDialog
            title: "Please choose a file"
            //folder: shortcuts.desktop
            folder: processor.directory
            selectExisting: false
            selectFolder: false

            onAccepted: {
                processor.filename = fileDialog.fileUrl
            }
        }
    }
}
