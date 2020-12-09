import QtQuick 2.12
import QtQuick.Controls 2.12

import library.sqlbookmodel 1.0

Page {
    id: root

    property int currentBook: -1

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
        spacing: 10
        model: SqlBookModel {}
        delegate: ItemDelegate {
            width: ListView.view.width - ListView.view.leftMargin - ListView.view.rightMargin
            height: titleLabel.implicitHeight + 10
            leftPadding: titleLabel.implicitWidth + 32
            onClicked: {
                currentBook = index;
                bookDialog.editBook(model);
            }

            Label {
                id: titleLabel
                anchors.verticalCenter: parent.verticalCenter
                text: model.title
            }

            RoundButton {
                text: qsTr("X")
                highlighted: true
                anchors.rightMargin: parent.height
                height: parent.height
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                onClicked: listView.model.doDelete(index)
            }
        }
    }

    BookDialog {
        id: bookDialog
        onFinished: {
            if (currentBook === -1)
                listView.model.doCreate(isbn, title, author, category)
            else
                listView.model.doUpdate(currentBook, title, author, category)
        }
    }

    RoundButton {
        text: qsTr("+")
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            currentBook = -1
            bookDialog.createBook()
        }
    }
}
