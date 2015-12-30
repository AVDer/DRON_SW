import QtQuick 2.0
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
}

