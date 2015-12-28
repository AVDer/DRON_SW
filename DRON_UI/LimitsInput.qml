import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    width: 120; height: 35
    radius: 10
    smooth: true

    property color borderColor: "black"
    property string hintText: ""

    TextField {
        anchors.fill: parent
        placeholderText: hintText
        focus: true
    }

    MouseArea {
        id: buttonMouseArea
        // Anchor all sides of the mouse area to the rectangle's anchors
        anchors.fill: parent
        // onClicked handles valid mouse button clicks
        //onClicked: console.log(buttonLabel.text + " clicked")
    }

    // Determines the color of the button by using the conditional operator
    border.color: borderColor
    color: "green"

}

