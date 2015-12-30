import QtQuick 2.0
<<<<<<< HEAD
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TextField {
    horizontalAlignment : TextInput.AlignHCenter
    validator: IntValidator {}

    style: TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 2
                implicitWidth: 100
                implicitHeight: 24
                border.color: "#333"
                border.width: 1
                width: 60; height: 25
            }
        }
=======
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

TextField {
    horizontalAlignment : TextInput.AlignHCenter
    validator: DoubleValidator {}
    style: TextFieldStyle {
           textColor: "black"
           background: Rectangle {
               radius: 2
               implicitWidth: 60
               implicitHeight: 25
               border.color: "#333"
               border.width: 1
               color: "lightsteelblue"
           }
       }
>>>>>>> c371a99747b0e10e6c63051eaee0202535b7fb28
}

