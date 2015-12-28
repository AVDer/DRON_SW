import QtQuick 2.3
import QuickQwt 1.0
import QtQuick.Controls 1.4

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
        hintText: qsTr("Angle min")
    }

    TextField {
        id: x_max
        anchors.right: qwt_plot.right
        anchors.top: qwt_plot.bottom
        placeholderText: qsTr("Angle max")
    }

    LimitsInput {
        id: y_min
        anchors.right: qwt_plot.left
        anchors.bottom: qwt_plot.bottom
        hintText: qsTr("Int min")
    }

    LimitsInput {
        id: y_max
        anchors.right: qwt_plot.left
        anchors.top: qwt_plot.top
        hintText: qsTr("Int max")
    }

}


