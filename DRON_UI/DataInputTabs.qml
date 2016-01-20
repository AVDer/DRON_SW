import QtQuick 2.0
import QtQuick.Controls 1.2

import dron.MeasureSettings 1.0

Item {
    TabView {
        z: -1
        anchors.fill: parent

        Tab {
            title: qsTr("Point scan")
            FullScanPanel {

            }
        }
        Tab {
            title: qsTr("Fast scan")
            FastScanPanel {

            }
        }
        Tab {
            title: "Settings"
            SettingsPanel {

            }
        }


        MeasureSettings {
            id: measureSettings
        }
    }

}
