import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

GridLayout {
    anchors.centerIn: parent
    columns: 3
    //spacing: 10

    Text {text: " "}
    Text {text: " "}
    Text {text: " "}

    Text {text: qsTr("Braking time")}
    TextField { }
    Text {text: qsTr("ms")}

    Text {text: qsTr("Delay")}
    TextField { }
    Text {text: qsTr("s")}

    Text {text: qsTr("File")}
    TextField { }
    Button {
        text: qsTr("Browse")
    }

}
