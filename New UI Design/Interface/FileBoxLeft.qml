import QtQuick 2.14
import QtQuick.Shapes 1.14
import QtQuick.Controls 2.14


Row {
    id: my_root
    spacing: 0
    anchors.left: parent.left
    anchors.leftMargin: 10
    width: 176
    height: 50
    Shape {
        width: 8
        height: 12
        anchors.top: parent.top
        anchors.topMargin: 7
        ShapePath {
            strokeWidth: 0
            strokeColor: "#6AB82D"
            fillColor: "#6AB82D"
            startX: 0; startY: 6
            PathLine { x: 8; y: 0 }
            PathLine { x: 8; y: 12 }
            PathLine { x: 0; y: 6 }
        }
    }
    Rectangle {
        id: message_rect
        radius: 5
        width: 155
        height: 50
        color: "#6AB82D"
        Row {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 5
            anchors.rightMargin: 2
            spacing: 0

            Column {
                spacing:10
                Text {
                    clip: true
                    padding: 3
                    elide: Text.ElideRight
                    text: value
                    width: 110
                    height: 20
                }


                Rectangle {
                    width: 100
                    height: 10
                    radius: 5
                    color: "white"
                    Rectangle {
                        width: Math.min(1, process)*100
                        height: 10
                        radius: 5
                        color: "green"
                        anchors.top: parent.top
                        anchors.left: parent.left
                    }

                }
            }
            Image {
                source: "qrc:/pic/File.png"
                width: 40
                height: 40
                fillMode: Image.PreserveAspectFit
            }
        }


    }


}




