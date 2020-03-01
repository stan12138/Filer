import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.0

RoundRect {
    width: 360
    height: 419
    color: "#F0F0F1"
    radius_left_upper: 0
    radius_right_upper: 0
    radius_left_lower: 7.69
    radius_right_lower: 7.69

    StackView {
        id: set_stack
        width: 215
        height: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 114.4
        initialItem: server_set
        replaceExit: Transition {
            id: replaceExit
            PropertyAction { property: "x"; value: replaceExit.ViewTransition.item.pos }
            PropertyAction { property: "y"; value: replaceExit.ViewTransition.item.pos }
            NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 800; easing.type: Easing.OutCubic }
        }
        replaceEnter: Transition {
            id: replaceEnter
            PropertyAction { property: "x"; value: replaceEnter.ViewTransition.item.pos }
            PropertyAction { property: "y"; value: replaceEnter.ViewTransition.item.pos }
            NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 800; easing.type: Easing.OutCubic }
        }
    }


    Row {
        id: set_title
        spacing: 10.31
        anchors.top: parent.top
        anchors.topMargin: 29.39
        anchors.horizontalCenter: parent.horizontalCenter
        property int current_item: 0
        ShadowRoundRect {
            radius1: 6.34
            radius2: 6.34
            radius3: 2
            radius4: 2
            the_color: parent.current_item==0 ? "#65B84A" : "#F0F0F1"
            Text {
                text: qsTr("Server")
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                enabled: (set_title.current_item==0) ? false : true
                onClicked: {
                    set_title.current_item = 0;
                    set_stack.replace(server_set);
                }
            }
        }
        ShadowRoundRect {
            radius1: 2
            radius2: 2
            radius3: 2
            radius4: 2
            the_color: parent.current_item==1 ? "#65B84A" : "#F0F0F1"
            Text {
                text: qsTr("This Device")
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                enabled: (set_title.current_item==1) ? false : true
                onClicked: {
                    set_title.current_item = 1;
                    set_stack.replace(my_set);
                }
            }
        }
        ShadowRoundRect {
            radius4: 6.34
            radius3: 6.34
            radius1: 2
            radius2: 2
            the_color: parent.current_item==2 ? "#65B84A" : "#F0F0F1"
            Text {
                text: qsTr("About")
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                enabled: (set_title.current_item==2) ? false : true
                onClicked: {
                    set_title.current_item = 2;
                    set_stack.replace(about_info);
                }
            }
        }
    }

    Row {
        spacing: 0
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 65.743
        anchors.bottomMargin: 61.402
        RoundRect {
            width: 38.552
            height: 28.348
            radius_left_upper: 6.334
            radius_left_lower: 6.334
            radius_right_lower: 1
            radius_right_upper: 1
            color: "#E01F26"
            Image {
                id: set_no
                anchors.centerIn: parent
                width: 20
                height: 20
                source: "qrc:/pic/false.png"
                visible: false
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {
                    set_no.visible = true
                }
                onExited: {
                    set_no.visible = false
                }
                onClicked: {
                    stack.replace(device_page);
                    setting.enter = false;
                }
            }

        }
        RoundRect {
            width: 38.552
            height: 28.348
            radius_left_lower: 1
            radius_left_upper: 1
            radius_right_lower: 6.334
            radius_right_upper: 6.334
            color: "#65B84A"
            Image {
                id: set_yes
                anchors.centerIn: parent
                width: 20
                height: 20
                source: "qrc:/pic/correct.png"
                visible: false
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {
                    set_yes.visible = true
                }
                onExited: {
                    set_yes.visible = false
                }

                onClicked: {
                    stack.replace(device_page);
                    setting.enter = false;
                }
            }
        }

    }

    Component {
        id: about_info
        ShadowRoundRect {
            width: 215
            height: 200
            radius1: 12
            radius2: 12
            radius3: 12
            radius4: 12
            the_color: "#F7F8F8"
            Text {
                text: qsTr("Design by stan")
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -10
            }
            Text {
                text: qsTr("2020.2.22")
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 10
            }
        }
    }

    Component {
        id: my_set
        ShadowRoundRect {
            width: 215
            height: 200
            radius1: 12
            radius2: 12
            radius3: 12
            radius4: 12
            the_color: "#F7F8F8"
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5
                spacing: 40
                width: 40
                Text {

                    text: qsTr("text")
                }

                Text {

                    text: qsTr("text")
                }

                Text {

                    text: qsTr("text")
                }

            }
            Column {
                anchors.centerIn: parent
                spacing: 25.6
                RoundRect {
                    width: 117.28
                    height: 24
                    radius_left_upper: 6.33
                    radius_right_upper: 6.33
                    radius_left_lower: 3
                    radius_right_lower: 3
                    color: "#F0EA3A"
                }
                RoundRect {
                    width: 117.28
                    height: 24
                    radius_left_upper: 3
                    radius_right_upper: 3
                    radius_left_lower: 3
                    radius_right_lower: 3
                    color: "#6AB82D"
                }
                RoundRect {
                    width: 117.28
                    height: 24
                    radius_left_upper: 3
                    radius_right_upper: 3
                    radius_left_lower: 6.33
                    radius_right_lower: 6.33
                    color: "#E01F26"
                }

            }
        }
    }




    Component {
        id: server_set
        ShadowRoundRect {
            width: 215
            height: 200
            radius1: 12
            radius2: 12
            radius3: 12
            radius4: 12
            the_color: "#F7F8F8"
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5
                spacing: 60
                width: 40
                Text {

                    text: qsTr("text")
                }

                Text {

                    text: qsTr("text")
                }

            }
            Column {
                anchors.centerIn: parent
                spacing: 25.6
                RoundRect {
                    width: 117.28
                    height: 24
                    radius_left_upper: 6.33
                    radius_right_upper: 6.33
                    radius_left_lower: 3
                    radius_right_lower: 3
                    color: "#F0EA3A"
                }
                RoundRect {
                    width: 117.28
                    height: 24
                    radius_left_upper: 3
                    radius_right_upper: 3
                    radius_left_lower: 6.33
                    radius_right_lower: 6.33
                    color: "#E01F26"
                }

            }
        }
    }

}
