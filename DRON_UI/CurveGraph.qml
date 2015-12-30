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
    }

    LimitsInput {
        id: x_min
        anchors.left: qwt_plot.left
        anchors.top: qwt_plot.bottom
        placeholderText: qsTr("Angle min")
    }

    LimitsInput {
        id: x_max
        anchors.right: qwt_plot.right
        anchors.top: qwt_plot.bottom
        placeholderText: qsTr("Angle max")
    }

    LimitsInput {
        id: y_min
        anchors.right: qwt_plot.left
        anchors.bottom: qwt_plot.bottom
        placeholderText: qsTr("Int min")
    }

    LimitsInput {
        id: y_max
        anchors.right: qwt_plot.left
        anchors.top: qwt_plot.top
        placeholderText: qsTr("Int max")
    }

    Text {
        text: qsTr("Angle, °")
        anchors.top: qwt_plot.bottom
        anchors.horizontalCenter: qwt_plot.horizontalCenter
    }

    Text {
        text: qsTr("Intensity")
        rotation: 270
        anchors.right: qwt_plot.left
        anchors.verticalCenter: qwt_plot.verticalCenter
    }

}


