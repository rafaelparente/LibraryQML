import QtQuick 2.12
import QtQuick.Controls 2.12

Dialog {
    id: dialog

    signal finished(string isbn, string title, string author, string category)

    function createBook() {
        form.isbn.clear();
        form.title.clear();
        form.author.clear();
        form.category.clear();

        dialog.title = qsTr("Adicionar livro");
        dialog.open();
    }

    function editBook(book) {
        form.isbn.text = book.isbn;
        form.title.text = book.title;
        form.author.text = book.author;
        form.category.text = book.category;

        dialog.title = qsTr("Editar livro");
        dialog.open();
    }

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    focus: true
    modal: true
    title: qsTr("Adicionar livro")
    standardButtons: Dialog.Ok | Dialog.Cancel

    contentItem: BookForm {
        id: form
    }

    onAccepted: finished(form.isbn.text, form.title.text, form.author.text, form.category.text)
}
