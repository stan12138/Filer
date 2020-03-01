import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQuick.Shapes 1.14

import QtQuick.Dialogs 1.0

RoundRect {
    width: 360
    height: 419
    color: "#F0F0F1"
    radius_left_upper: 0
    radius_right_upper: 0
    radius_left_lower: 7.69
    radius_right_lower: 7.69

    Rectangle {
        id: main_rect
        width: 331
        height: 393
        anchors.centerIn: parent
        color: "#F8F8F8"
        radius: 12
    }


    ListView {
        id: the_list
        model: commu_info
        width: main_rect.width
        height: 304
        spacing: 10
        displayMarginBeginning: 40
        displayMarginEnd: 40
        anchors.top: main_rect.top
        anchors.left: main_rect.left
        clip: true
        footer: foot
        delegate: Component {
            Loader {
                id: the_list_loader
                anchors.left: send_by_me ? parent.left : undefined
                anchors.right: !send_by_me ? parent.right : undefined

                source: switch(send_by_me) {
                   case true: return send_type+"BoxLeft.qml"
                   case false: return send_type+"BoxRight.qml"
                }
            }
        }
    }

    Component {
        id: foot
        Rectangle {
            width: 200
            height: 30
            color: "#00000000"
        }
    }

    ListModel {
        id: commu_info
        ListElement {
            send_by_me: true
            send_type: "Message"
            value: "begin"
        }
        ListElement {
            send_by_me: false
            send_type: "File"
            process: 0.5
            value: "feeeeee.pdf"
        }
        ListElement {
            send_by_me: true
            send_type: "File"
            process: 0.5
            value: "testewrettttttttttttt.pdf"
        }
    }

    Column {
        spacing: 0
        anchors.bottom: main_rect.bottom
        anchors.left: main_rect.left
        Rectangle {
            width: 331
            height: 1.5
            radius: 0.75
            color: "#DEDEDE"
        }

        RoundRect {
            width: 331
            height: 89
            radius_left_lower: 12
            radius_right_lower: 12
            radius_left_upper: 0
            radius_right_upper: 0
            color: "#fbfbfb"

            Image {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 10
                id: choose_file
                width: 30
                height: 30
                source: "qrc:/pic/File_small.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("click");
                        the_file.open();
                    }
                }

            }
            TextEdit {
                id: input
                color: "black"
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                wrapMode: TextEdit.Wrap
                anchors.fill: parent
                textMargin: 10
                property double p: 0.0
                Keys.onReturnPressed: {
                    commu_info.append({value:input.text, send_by_me: false, send_type: "Message"})
                    input.clear();
                    the_list.positionViewAtEnd();
                    commu_info.get(1).process += 0.1

                }

            }


        }


    }

    property Component the_file: FileDialog {
        id: fileDialog
        title: "Please choose a file"
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = true
    }


}
