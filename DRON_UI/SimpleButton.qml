import QtQuick 2.3

Rectangle {
    width: 120; height: 35
    radius: 10
    smooth: true

    property color buttonColor: "lightblue"
    property color onHoverColor: "black"
    property color borderColor: "white"
    property string button_text: "Push me"

    signal buttonClick()

    Text {
        id: buttonLabel
        anchors.centerIn: parent
        text: button_text
    }

    onButtonClick: {
        //console.log(buttonLabel.text + " clicked")
        console.log(parent.width)
    }

    MouseArea{
        id: buttonMouseArea
        anchors.fill: parent
        onClicked: buttonClick()
        hoverEnabled: true
        onEntered: parent.border.color = onHoverColor
        onExited:  parent.border.color = borderColor
    }

    border { color: borderColor; width: 2 }

    property Gradient released_gradient: Gradient {
        GradientStop { position: 0.0; color: "lightsteelblue" }
        GradientStop { position: 1.0; color: "slategray" }
    }
    property Gradient pressed_gradient: Gradient {
        GradientStop { position: 0.0; color: "slategray" }
        GradientStop { position: 1.0; color: "lightsteelblue" }
    }

    gradient: buttonMouseArea.pressed ? pressed_gradient : released_gradient
}
