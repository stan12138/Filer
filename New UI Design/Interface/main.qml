
import QtGraphicalEffects 1.0

import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

Window {
    visible: true
    property int wanted_width: 360
    property int wanted_height: 470

    width: wanted_width+20
    height: wanted_height+20

    id: root

    flags: Qt.Window | Qt.FramelessWindowHint

    color: Qt.rgba(0,0,0,0)

    onVisibilityChanged: {
        if(visible)
        {
            flags= Qt.Window | Qt.FramelessWindowHint;
        }
    }

    Rectangle
    {
        id: rect
        width: wanted_width
        height: wanted_height
        anchors.left: parent.left
        anchors.top: parent.top
        radius: 7.69

    }

    DropShadow
    {
        anchors.fill: rect
        horizontalOffset: 3
        verticalOffset: 3
        radius: 15
        samples: 31
        color: "#B3231815"
        spread: 0.0
        source: rect
    }


    RoundRect {
        radius_left_lower: 0
        radius_left_upper: 7.69
        radius_right_lower: 0
        radius_right_upper: 7.69

        height: 51
        width: rect.width
        color: "#5866ae"

        anchors.top: rect.top
        anchors.left: rect.left

        id: title

        MouseArea {
            anchors.fill: parent
            id: move_area

            property bool move_press: false
            property int mx: 0
            property int my: 0
            cursorShape: move_press?Qt.SizeAllCursor:Qt.ArrowCursor

            onPressed: {
                mx = mouseX
                my = mouseY
                move_press=true
                focus = true;
            }
            onPositionChanged: {
                root.x += mouseX-mx
                root.y += mouseY-my
            }
            onReleased:
            {
                move_press=false
            }
        }
    }

    Image {
        id: setting
        property bool enter: false
        source: enter?"qrc:/pic/Setting_click.png":"qrc:/pic/Setting_normal.png"
        width: 15
        height: 15
        fillMode: Image.PreserveAspectFit

        anchors.verticalCenter: title.verticalCenter
        anchors.left: title.left
        anchors.leftMargin: 20

        MouseArea {
            anchors.fill: parent
            enabled: stack.currentItem.objectName!="set"
            hoverEnabled: true
            onEntered: {
                setting.enter = true;
            }
            onExited: {
                setting.enter = false;
            }
            onClicked: {
                setting.enter = true;
                stack.replace(set_page)
            }
        }

    }

    Image {
        id: mi
        property bool enter: false
        source: enter?"qrc:/pic/min_click.png":"qrc:/pic/min.png"

        width: 15
        height: 15
        fillMode: Image.PreserveAspectFit

        anchors.verticalCenter: title.verticalCenter
        anchors.right: title.right
        anchors.rightMargin: 55

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                mi.enter = true;
            }
            onExited: {
                mi.enter = false;
            }
            onClicked: {
                root.flags = Qt.Window | Qt.CustomizeWindowHint | Qt.WindowMinMaxButtonsHint;
                root.showMinimized();
            }
        }

    }

    Image {
        id: ex
        property bool enter: false
        source: enter?"qrc:/pic/exit_click.png":"qrc:/pic/exit.png"

        width: 15
        height: 15
        fillMode: Image.PreserveAspectFit

        anchors.verticalCenter: title.verticalCenter
        anchors.right: title.right
        anchors.rightMargin: 20

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                ex.enter = true;
            }
            onExited: {
                ex.enter = false;
            }

            onClicked: {
                Qt.quit();
            }
        }

    }

    property Component device_page: DevicePage { objectName: "device"}
    property Component set_page: SetPage {objectName: "set"}
    property Component talk_page: TalkPage {objectName: "talk"}

    StackView {
        id: stack
        width: 360
        height: 419
        anchors.bottom: rect.bottom
        anchors.left: rect.left
        initialItem: talk_page
    }




}
