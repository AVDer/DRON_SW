import QtQuick 2.3

Rectangle {
    width: 150; height: 75
    radius: 20
    smooth: true

    property color buttonColor: "lightblue"
    property color onHoverColor: "gold"
    property color borderColor: "white"
    property string button_text: "Push me"

    signal buttonClick()

    Text {
        id: buttonLabel
        anchors.centerIn: parent
        text: button_text
    }

    onButtonClick: {
        console.log(buttonLabel.text + " clicked")
    }

    MouseArea {
        id: buttonMouseArea
        // Anchor all sides of the mouse area to the rectangle's anchors
        anchors.fill: parent
        // onClicked handles valid mouse button clicks
        onClicked: console.log(buttonLabel.text + " clicked")
    }

    MouseArea{
        onClicked: buttonClick()
        hoverEnabled: true
        onEntered: parent.border.color = onHoverColor
        onExited:  parent.border.color = borderColor
    }

    // Determines the color of the button by using the conditional operator
    color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor
    border.color: borderColor
}
