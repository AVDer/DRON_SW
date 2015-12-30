import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Rectangle {
    id: root
    anchors.fill: parent
    visible: true
    color: "slategray"

    property int partition: width/4
    //color:"slategray"

    state: "SETTINGS_OPEN"

    Row {
        id: mainLayout
        anchors.fill: parent

        GraphPanel {
            id: graphPanel
            width: partition * 3
        }

        Rectangle {
            id: arrowDrawer
            width: 15; height: parent.height
            border { color : "#6A6D6A"; width: 1 }
            z: 1
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#8C8F8C" }
                GradientStop { position: 0.17; color: "#6A6D6A" }
                GradientStop { position: 0.77; color: "#3F3F3F" }
                GradientStop { position: 1.0; color: "#6A6D6A" }
            }
            Image {
                id: arrowIcon
                source: "images/arrow.png"
                anchors.verticalCenter: parent.verticalCenter
                Behavior{ NumberAnimation { property: "rotation"; easing.type: Easing.OutExpo } }
            }

            MouseArea {
                id: drawerMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: parent.border.color = Qt.lighter("#6A6D6A")
                onExited:  parent.border.color = "#6A6D6A"
                onClicked: {
                    if (root.state == "SETTINGS_CLOSED") {
                        root.state = "SETTINGS_OPEN"
                    }
                    else if (root.state == "SETTINGS_OPEN"){
                        root.state = "SETTINGS_CLOSED"
                    }
                }
            }

        }

        DataInputTabs {
            z: -1
            id: dataTab
            width: parent.width - graph_panel.width - 60
        }
    }

    //! [states]
    states:[
        State {
            name: "SETTINGS_OPEN"
            PropertyChanges { target: dataTab; x: arrowDrawer.x + arrowDrawer.width }
            PropertyChanges { target: graphPanel; width: partition * 3}
            PropertyChanges { target: arrowIcon; rotation: 270}
        },
        State {
            name: "SETTINGS_CLOSED"
            PropertyChanges { target: dataTab; x: 0 }
            PropertyChanges { target: graphPanel; width: mainLayout.width - arrowDrawer.width}
            PropertyChanges { target: arrowIcon; rotation: 90 }
        }
    ]
    //! [states]
}

