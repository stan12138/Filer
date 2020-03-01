import QtQuick 2.0
import QtGraphicalEffects 1.0


Item {
    property string value: "Stan-PC"


    Rectangle {
        id: item_rect
        width: 220
        height: 38
        radius: 5.894
        color: "#F0F0F1"
        anchors.centerIn: parent

        Text {
            id: name
            text: qsTr("Stan-PC")
            anchors.centerIn: parent
        }
    }

    DropShadow
    {
        anchors.fill: item_rect
        horizontalOffset: 7
        verticalOffset: 7
        radius: 15
        samples: 31
        color: "#a3231815"
        spread: 0.0
        source: item_rect
    }

}
