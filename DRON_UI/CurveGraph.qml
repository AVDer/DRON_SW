import QtQuick 2.3
import QuickQwt 1.0
import QtQuick.Controls 1.2

Item {
    width: parent.width
    height: parent.height

    QuickQwtPlot {
        id: qwt_plot
        anchors.right: parent.right
        anchors.top: parent.top
        width: parent.width - x_min.width
        height: parent.height - x_min.height

        titleXBottom: qsTr("Angle, °")
        titleYLeft: qsTr("Intensity")
    }

    MouseArea {
        anchors.fill: qwt_plot
        onDoubleClicked: qwt_plot.setAutoScale()
    }

    LimitsInput {
        id: x_min
        anchors.left: qwt_plot.left
        anchors.top: qwt_plot.bottom
        placeholderText: qsTr("Angle min")
        text: qwt_plot.xMin
        onAccepted: {
            x_min.focus = false
            qwt_plot.xMin = x_min.text
            qwt_plot.update()
        }
    }

    LimitsInput {
        id: x_max
        anchors.right: qwt_plot.right
        anchors.top: qwt_plot.bottom
        placeholderText: qsTr("Angle max")
        text: qwt_plot.xMax
        onAccepted: {
            x_max.focus = false
            qwt_plot.xMax = x_max.text
            qwt_plot.update()
        }
    }

    LimitsInput {
        id: y_min
        anchors.right: qwt_plot.left
        anchors.bottom: qwt_plot.bottom
        placeholderText: qsTr("Int min")
        text: qwt_plot.yMin
        onAccepted: {
            y_min.focus = false
            qwt_plot.yMin = y_min.text
            qwt_plot.update()
        }
    }

    LimitsInput {
        id: y_max
        anchors.right: qwt_plot.left
        anchors.top: qwt_plot.top
        placeholderText: qsTr("Int max")
        text: qwt_plot.yMax
        onAccepted: {
            y_max.focus = false
            qwt_plot.yMax = y_max.text
            qwt_plot.update()
        }
    }
}


