import QtQuick 2.0

Rectangle {
    property double radius_left_upper: 0
    property double radius_left_lower: 0
    property double radius_right_upper: 0
    property double radius_right_lower: 0

    radius: Math.max(radius_left_lower, radius_left_upper, radius_right_lower, radius_right_upper)

    Rectangle {
        width: parent.width/2
        height: parent.height/2
        radius: radius_left_upper
        anchors.left: parent.left
        anchors.top: parent.top

        color: parent.color
    }

    Rectangle {
        width: parent.width/2
        height: parent.height/2
        radius: radius_left_lower
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        color: parent.color
    }

    Rectangle {
        width: parent.width/2
        height: parent.height/2
        radius: radius_right_upper
        anchors.right: parent.right
        anchors.top: parent.top


        color: parent.color
    }

    Rectangle {
        width: parent.width/2
        height: parent.height/2
        radius: radius_right_lower
        anchors.right: parent.right
        anchors.bottom: parent.bottom


        color: parent.color
    }

}
