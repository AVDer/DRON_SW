import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import dron.FileManager 1.0

GridLayout {
    id: settings_page
    anchors.centerIn: parent
    columns: 3

    Text {text: " "}
    Text {text: " "}
    Text {text: " "}

    Text {text: qsTr("Braking time")}
    TextField { }
    Text {text: qsTr("ms")}

    Text {text: qsTr("Delay")}
    TextField { }
    Text {text: qsTr("s")}

    Text {
        id: file_dir_part
        text: file_manager.filename
        Layout.columnSpan: 3
    }

    Text {text: qsTr("File")}
    TextField { }
    Button {
        text: qsTr("Browse")
        onClicked: fileDialog.open()
    }

    FileManager {
        id: file_manager
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        visible: true

        onAccepted: {
            file_manager.filename = fileDialog.fileUrl
            file_dir_part.text = fileDialog.fileUrl
        }
        //Component.onCompleted: visible = true
    }
}
