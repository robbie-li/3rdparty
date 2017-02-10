import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: root
    height: 30
    color: "transparent"

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.ListView.view.currentIndex = index
        }
    }

    states: State {
        name: "Current"
        when: root.ListView.isCurrentItem
        PropertyChanges { target: root; x: 5 }
    }

    transitions: Transition {
        NumberAnimation { properties: "x"; duration: 200 }
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

            Label {
                anchors.fill: parent
                width: parent.width
                wrapMode: Text.Wrap
                text: qsTr("Choose")
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
                text: qsTr("Library")
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
                text: qsTr("Version")
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
                text: qsTr("Address")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
