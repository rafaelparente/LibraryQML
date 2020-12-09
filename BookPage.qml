import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQml.Models 2.2

import library.sqlbookmodel 1.0

Page {
    id: root

    property string bookIsbn
    property string bookTitle
    property string bookAuthor
    property string bookCategory

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
            text: bookTitle
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    DelegateModel {
        id: visualModel
        model: SqlBookModel {
            isbn: bookIsbn
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Pane {
            id: detailsPane
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                width: parent.width

                RowLayout {
                    id: rowLayout1

                    Label {
                        text: qsTr("ISBN:")
                        horizontalAlignment: Text.AlignRight
                        Layout.topMargin: 6
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.minimumWidth: 50
                    }

                    TextArea {
                        id: isbnField
                        text: bookIsbn
                        placeholderText: qsTr("ISBN")
                        wrapMode: TextArea.Wrap
                        Layout.fillWidth: true
                    }
                }

                RowLayout {
                    id: rowLayout

                    Label {
                        text: qsTr("Título:")
                        horizontalAlignment: Text.AlignRight
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.topMargin: 6
                        Layout.minimumWidth: 50
                    }

                    TextArea {
                        id: titleField
                        text: bookTitle
                        placeholderText: qsTr("Título")
                        wrapMode: TextArea.Wrap
                        Layout.fillWidth: true
                    }
                }

                RowLayout {
                    id: rowLayout2

                    Label {
                        text: qsTr("Autor:")
                        horizontalAlignment: Text.AlignRight
                        Layout.topMargin: 6
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.minimumWidth: 50
                    }

                    TextArea {
                        id: authorField
                        text: bookAuthor
                        placeholderText: qsTr("Autor")
                        wrapMode: TextArea.Wrap
                        Layout.fillWidth: true
                    }
                }

                RowLayout {
                    id: rowLayout3

                    Label {
                        text: qsTr("Categoria:")
                        horizontalAlignment: Text.AlignRight
                        Layout.topMargin: 6
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.minimumWidth: 50
                    }

                    TextArea {
                        id: categoryField
                        text: bookCategory
                        placeholderText: qsTr("Categoria")
                        wrapMode: TextArea.Wrap
                        Layout.fillWidth: true
                    }
                }
            }
        }

        Pane {
            id: buttonsPane
            Layout.fillWidth: true

            RowLayout {
                width: parent.width

                Column {
                    id: column
                    Layout.fillWidth: true
                }

                Button {
                    id: saveButton
                    text: qsTr("Salvar")
                    enabled: isbnField.length > 0 && titleField.length > 0
                    onClicked: {
                        visualModel.model.saveDetails(isbnField.text,
                                                      titleField.text,
                                                      authorField.text,
                                                      categoryField.text,
                                                      );
                    }
                }

                Column {
                    id: column2
                    Layout.fillWidth: true
                }

                Button {
                    id: saveAndExitButton
                    text: qsTr("Salvar e sair")
                    enabled: isbnField.length > 0 && titleField.length > 0
                    onClicked: {
                        visualModel.model.saveDetails(isbnField.text,
                                                      titleField.text,
                                                      authorField.text,
                                                      categoryField.text,
                                                      );
                        root.StackView.view.pop();
                    }
                }

                Column {
                    id: column1
                    Layout.fillWidth: true
                }




            }
        }
    }
}
