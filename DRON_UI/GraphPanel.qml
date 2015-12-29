import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

GroupBox {
    id: graph_box
    title: "Intensity chart"
    //width: parent.width / 2
    height: parent.height

    ColumnLayout {
        anchors.fill: parent

        CurveGraph {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: parent.height - start_stop_panel.height - 60
        }

        StartStopPanel {
            id: start_stop_panel
            anchors.bottom: parent.bottom
            anchors.right: parent.right
        }
    }



}

