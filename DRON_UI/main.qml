import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Rectangle {
    id: root
    anchors.fill: parent
    visible: true
    color: "slategray"

    Row {
        id: main_layout
        anchors.fill: parent
        spacing: 10

        GraphPanel {
            id: graph_panel
            width: parent.width * 0.75
        }

        DataInputTabs {
            width: parent.width - graph_panel.width - 20
        }
    }
}

