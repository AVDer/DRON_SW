import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Grid {
    anchors.centerIn: parent
    columns: 3
    spacing: 10

    Text {text: " "}
    Text {text: " "}
    Text {text: " "}

    Text {text: qsTr("Style")}
    ExclusiveGroup { id: line_style_group }
    RadioButton {
        id: style_line
        text: qsTr("Line")
        checked: true
        exclusiveGroup: line_style_group
        onCheckedChanged: if (checked) processor.lineStyleChanged(1)
    }
    RadioButton {
        id: style_point
        text: qsTr("Point")
        exclusiveGroup: line_style_group
        onCheckedChanged: if (checked) processor.lineStyleChanged(2)
    }

    Text {text: qsTr("Size")}
    SpinBox {
        id: point_size
        value: 1
        onValueChanged: processor.lineSizeChanged(value)
    }
    Text {text: qsTr("pt")}
}

