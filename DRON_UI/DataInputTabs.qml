import QtQuick 2.0
import QtQuick.Controls 1.2

Item {
    TabView {
        z: -1
        anchors.fill: parent

        Tab {
            onVisibleChanged: { if (visible) processor.mode = 1 }
            title: qsTr("Point")
            FullScanPanel {

            }
        }
        Tab {
            onVisibleChanged: { if (visible) processor.mode = 2 }
            title: qsTr("Integral")
            FastScanPanel {

            }
        }
        Tab {
            onVisibleChanged: { if (visible) processor.mode = 3 }
            title: qsTr("Adjustment")
            AdjustPanel {

            }
        }
        Tab {
            title: qsTr("Settings")
            SettingsPanel {

            }
        }
        Tab {
            title: qsTr("Line")
            LinePanel {

            }
        }
    }
}
