import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: root
    height: 40
    color: "transparent"

    signal selectLibrary(string name, string version, bool selected)

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.ListView.view.currentIndex = index
        }
    }

    Rectangle {
        anchors.fill: parent
        color: root.ListView.isCurrentItem ? "lightblue" : "lightgrey"
    }

    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: "#eee"
    }

    Row {
        id: eventItemColumn
        anchors.top: parent.top
        width: parent.width
        height: parent.height
        spacing: 5
        property int columns: 4

        Rectangle {
            width: (parent.width - parent.spacing) / (2*parent.columns)
            height: parent.height
            color: "transparent"

            CheckBox {
                anchors.fill: parent
                width: parent.width
                onCheckedChanged: {
                    console.log(name + ":" + checked)
                    root.selectLibrary(name, version, checked)
                }
            }
        }

        Rectangle {
            width: (parent.width - parent.spacing) / (2*parent.columns)
            height: parent.height
            color: "transparent"

            Label {
                anchors.fill: parent
                width: parent.width
                wrapMode: Text.Wrap
                text: name
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Rectangle {
            width: (parent.width - parent.spacing) / (2*parent.columns)
            height: parent.height
            color: "transparent"

            Label {
                anchors.fill: parent
                width: parent.width
                wrapMode: Text.Wrap
                text: version
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Rectangle {
            width: 5*(parent.width - parent.spacing) / (2*parent.columns)
            height: parent.height
            color: "transparent"

            Label {
                anchors.fill: parent
                width: parent.width
                wrapMode: Text.Wrap
                text: url
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
