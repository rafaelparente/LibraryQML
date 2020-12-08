import QtQuick 2.6
import QtQuick.Controls 2.0
import library.backend 1.0

ApplicationWindow {
    id: root
    width: 800
    height: 600
    visible: true
    title: qsTr("Biblioteca")

    BackEnd {
        id: backend
    }

    TextField {
        text: backend.userName
        placeholderText: qsTr("User name")
        anchors.centerIn: parent

        onEditingFinished: backend.userName = text
    }

    Label {
        text: backend.userName
    }
}
