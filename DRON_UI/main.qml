import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
//import "SimpleButton.qml"

ApplicationWindow {
    id: main_window
    visible: true

    Row {

        CurveGraph {

        }

        Column {

            Text {
                text: qsTr("Hello World")
                //anchors.centerIn: parent
            }

            Row {
                //anchors.centerIn: parent
                spacing: parent.width / 10
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

