import QtQuick 2.12
import QtQuick.Controls 2.12

import library.sqlbookmodel 1.0

Page {
    id: root

    header: ToolBar {
        Label {
            text: qsTr("Livros")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 20
        model: SqlBookModel {}
        delegate: ItemDelegate {
            text: model.title
            width: ListView.view.width - ListView.view.leftMargin - ListView.view.rightMargin
            height: avatar.implicitHeight
            leftPadding: avatar.implicitWidth + 32
            onClicked: root.StackView.view.push("qrc:/BookPage.qml", {
                                                    bookIsbn: model.isbn,
                                                    bookTitle: model.title,
                                                    bookAuthor: model.author,
                                                    bookCategory: model.category,
                                                })

            Label {
                id: avatar
                text: model.title
            }
        }
    }
}
