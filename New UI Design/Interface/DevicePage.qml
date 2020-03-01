import QtQuick 2.0
import QtQuick.Controls 2.14

RoundRect {
    width: 360
    height: 419
    color: "#F0F0F1"
    radius_left_upper: 0
    radius_right_upper: 0
    radius_left_lower: 7.69
    radius_right_lower: 7.69

    Text {
        id: label
        text: qsTr("On-Line Devices")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 45
    }

    ListView {
        id: device_listview
        width: 300
        height: 250
        clip: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: label.bottom
        anchors.topMargin: 33.4
        spacing: 19.5
        model: device_list
        delegate: device_item
        footer: foot
        header: foot
    }

    Component {
        id: device_item
        ShadowRoundRect {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 220
            height: 37.5
            radius1: 5.89
            radius2: 5.89
            radius3: 5.89
            radius4: 5.89

            Text {
                anchors.centerIn: parent
                text: device_name
            }

            MouseArea {
                anchors.fill: parent
                property bool enter: false
                hoverEnabled: true
                onEntered: {
                    enter=true;
                }
                onExited: {
                    enter=false;
                }

                ToolTip {
                    x: parent.mouseX
                    y: parent.mouseY
                    timeout: 500
                    visible: parent.enter && !device_listview.moving
                    text: device_IP
                    background: Rectangle {
                        color: "#22444444"
                        radius: 3
                    }
                }
            }


        }
    }

    ListModel {
        id: device_list
        ListElement {
            device_name: "Stan-PC"
            device_IP: "192.168.0.1"
        }
        ListElement {
            device_name: "Stan-PC"
            device_IP: "192.168.0.2"
        }
        ListElement {
            device_name: "Stan-PC"
            device_IP: "192.168.0.3"
        }
        ListElement {
            device_name: "Stan-PC"
            device_IP: "192.168.0.4"
        }
        ListElement {
            device_name: "Stan-PC"
            device_IP: "192.168.0.5"
        }
        ListElement {
            device_name: "Stan-PC"
            device_IP: "192.168.0.6"
        }
        ListElement {
            device_name: "Stan-PC"
            device_IP: "192.168.0.7"
        }
    }


    Component {
        id: foot
        Rectangle {
            width: 200
            height: 15
            color: "#00000000"
        }
    }

}
