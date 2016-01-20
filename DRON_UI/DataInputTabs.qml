import QtQuick 2.0
import QtQuick.Controls 1.2

Item {
    TabView {
        z: -1
        anchors.fill: parent

        Tab {
            onVisibleChanged: { if (visible) processor.mode = 1 }
            title: qsTr("Point scan")
            FullScanPanel {

            }
        }
        Tab {
            onVisibleChanged: { if (visible) processor.mode = 2 }
            title: qsTr("Integral scan")
            FastScanPanel {

            }
        }
        Tab {
            title: qsTr("Settings")
            SettingsPanel {

            }
        }
    }
}
