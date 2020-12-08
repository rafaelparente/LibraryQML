import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import library.sqlbookmodel 1.0

Page {
    id: root

    property SqlBookModel book

    header: ToolBar {
        ToolButton {
            text: qsTr("Voltar")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }

        Label {
            id: pageTitle
            text: book.title
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    Pane {
        id: detailsPane
        Layout.fillWidth: true

        Rectangle {
            width: isbnField.implicitWidth + 24
            height: isbnField.implicitHeight + 24

            TextArea {
                id: isbnField
                text: book.isbn
                Layout.fillWidth: true
                placeholderText: qsTr("ISBN")
                wrapMode: TextArea.Wrap
            }
        }

        Rectangle {
            width: titleField.implicitWidth + 24
            height: titleField.implicitHeight + 24

            TextArea {
                id: titleField
                text: book.title
                Layout.fillWidth: true
                placeholderText: qsTr("Título")
                wrapMode: TextArea.Wrap
            }
        }
    }

    Pane {
        id: buttonsPane
        Layout.fillWidth: true

        RowLayout {
            width: parent.width

            Button {
                id: saveButton
                text: qsTr("Salvar")
                enabled: isbnField.length > 0 && titleField.length > 0
                onClicked: {
                    book.saveDetails();
                }
            }

            Button {
                id: saveAndExitButton
                text: qsTr("Salvar e sair")
                enabled: isbnField.length > 0 && titleField.length > 0
                onClicked: {
                    book.saveDetails({
                                         "isbn": isbnField.text,
                                         "title": titleField.text,
                                         "author": book.author,
                                         "category": book.category,
                                     });
                    root.StackView.view.pop();
                }
            }
        }
    }
}
