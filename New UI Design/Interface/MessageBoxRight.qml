import QtQuick 2.0
import QtQuick.Shapes 1.14
import QtQuick.Controls 2.14


Row {
    spacing: 0
    anchors.right: parent.right
    anchors.rightMargin: 3
    width: message_rect.width + 21
    height: message_rect.height

    Rectangle {
        id: message_rect
        radius: 5
        width: Math.max(Math.min(messageText.implicitWidth + 24, the_list.width - 100), 10)
        height: Math.max(messageText.implicitHeight + 24, 40)
        color: "#6AB82D"
        Label {
            id: messageText
            color: "black"
            font.pixelSize: 10
            text: value
            anchors.fill: parent
            anchors.margins: 12
            wrapMode: Label.Wrap
        }
    }

    Shape {
        anchors.top: parent.top
        anchors.topMargin: 7
        width: 8
        height: 12
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




