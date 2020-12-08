import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: window
    width: 540
    height: 960
    visible: true
    title: qsTr("Biblioteca")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: BookListPage {}
    }
}
