import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        id: listView
        anchors.fill: parent
        model: myModel
        delegate: Item {
            x: 5
            width: 256
            height: 40
            Row {
                id: row1
                Text {
                    text: count
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }

                TextField {
                    id: nameField
                    text: name
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter

                    onEditingFinished: {
                        name = nameField.text
                    }
                }
                spacing: 10
            }
        }
    }
}
