import QtQuick 2.0
import QtQuick.Controls 1.2

TabView {
    Tab {
        title: qsTr("Fast scan")
        FastScanPanel {

        }
    }
    Tab {
        title: "Blue"
        Rectangle { color: "blue" }
    }
    Tab {
        title: "Settings"
    }
}

