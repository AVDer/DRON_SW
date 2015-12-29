import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

Grid {
    anchors.centerIn: parent
    columns: 3
    spacing: 10

    Text {text: " "}
    Text {text: " "}
    Text {text: " "}

    Text {text: qsTr("Start angle")}
    TextField { }
    Text {text: qsTr("°")}

    Text {text: qsTr("Stop angle")}
    TextField { }
    Text {text: qsTr("°")}

    Text {text: qsTr("Step")}
    TextField { }
    Text {text: qsTr("°")}

    Text {text: qsTr("Exposition")}
    TextField { }
    Text {text: qsTr("s")}

}
