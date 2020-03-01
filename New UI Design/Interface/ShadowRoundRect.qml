import QtQuick 2.0

import QtGraphicalEffects 1.0


Item {
    property double radius1: 0
    property double radius2: 0
    property double radius3: 0
    property double radius4: 0
//    property double the_width: 101
//    property double the_heigth: 37
    width: 101
    height: 37
    property color the_color: "#F0F0F1"
    RoundRect {
        id: server_set
        width: parent.width
        height: parent.height
        color: the_color
        radius_left_lower: radius2
        radius_right_lower: radius4
        radius_left_upper: radius1
        radius_right_upper: radius3

    }

    DropShadow {
        anchors.fill: server_set
        horizontalOffset: 5
        verticalOffset: 5
        radius: 15
        samples: 31
        color: "#a3231815"
        spread: 0.0
        source: server_set
    }
}
