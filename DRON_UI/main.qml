import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Rectangle {
    id: root
    anchors.fill: parent
    visible: true

    RowLayout {
        id: main_layout
        anchors.fill: parent

        GroupBox {
            title: "Rect layout"
            Layout.fillWidth: true
            CurveGraph {
                anchors.centerIn: parent
            }
        }

        GroupBox {
            title: "Row layout"
            Layout.fillWidth: true
            RowLayout {
                id: button_layout
                anchors.centerIn: parent
                spacing: main_layout.width / 10
                SimpleButton {
                    button_text: qsTr("Start")
                    buttonColor: "green"
                    //onClicked: Qt.quit()
                }
                SimpleButton {
                    buttonColor: "red"
                    button_text: qsTr("Stop")
                    //onClicked: Qt.quit()
                }
                SimpleButton {
                    buttonColor: "grey"
                    button_text: qsTr("Quit")
                    //onClicked: Qt.quit()
                }

            }
        }

    }


}

