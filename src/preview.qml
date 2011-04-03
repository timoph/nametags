import Qt 4.7

Rectangle {
    width: 105*4
    height: 74*4
    Image {
        id: preview
        width: parent.width
        height: parent.height
        source: "pics/summit-fi.jpg"
        anchors.centerIn: parent
    }

    Text {
        objectName: "firstname"
        id: first
        text: "Etunimi"
        font.pixelSize: preview.height/8
        anchors.horizontalCenter: preview.right
        anchors.horizontalCenterOffset: -preview.width / 4
        anchors.bottom: preview.bottom
        anchors.bottomMargin: preview.height / 10< 40 ? 40 : preview.height / 10
    }

    Text {
        objectName: "lastname"
        id: last
        text: "Von Sukunimi"
        font.pixelSize: preview.height/18
        anchors.top: first.bottom
        anchors.horizontalCenter: first.horizontalCenter
    }


}
