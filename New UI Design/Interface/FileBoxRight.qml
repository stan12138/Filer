import QtQuick 2.14
import QtQuick.Shapes 1.14
import QtQuick.Controls 2.14


Row {
    id: my_root
    spacing: 0
    anchors.right: parent.right
    anchors.rightMargin: 0
    width: 176
    height: 50
    Rectangle {
        id: message_rect
        radius: 5
        width: 155
        height: 50
        color: "#6AB82D"
        Row {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 5
            anchors.leftMargin: 5
            spacing: 5
            Image {
                source: "qrc:/pic/File.png"
                width: 40
                height: 40
                fillMode: Image.PreserveAspectFit
            }

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
        }


    }

    Shape {
        anchors.top: parent.top
        anchors.topMargin: 7
        width: 8
        height: 12
        antialiasing: true
        ShapePath {
            strokeWidth: 0
            strokeColor: "#6AB82D"
            fillColor: "#6AB82D"
            fillRule: ShapePath.WindingFill
            startX: 0; startY: 0
            PathLine { x: 8; y: 6 }
            PathLine { x: 0; y: 12 }
            PathLine { x: 0; y: 0 }
        }
    }

}




