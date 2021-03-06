import QtQuick 2.3

Rectangle {
    width: 105*4
    height: 74*4
    Image {
        objectName: "bgimage"
        id: preview
        width: parent.width
        height: parent.height
        source: "pics/badge.png"
        anchors.centerIn: parent
    }

    Text {
        objectName: "firstname"
        id: first
        text: "Etunimi"
        font.family:  "Junction"
        font.pixelSize: preview.height/4 //8
        anchors.horizontalCenter: preview.right
        anchors.horizontalCenterOffset: -preview.width / 2 //4
        anchors.bottom: preview.bottom
        anchors.bottomMargin: preview.height / 4//preview.height / 10< 40 ? 40 : preview.height / 10
    }

    Text {
        objectName: "lastname"
        id: last
        text: "Von Sukunimi"
        font.family:  "Junction"
        font.pixelSize: preview.height/18
        anchors.top: first.bottom
        anchors.horizontalCenter: first.horizontalCenter
    }


}
