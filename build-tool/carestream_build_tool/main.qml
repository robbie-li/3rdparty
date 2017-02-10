import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import com.carestream.dental 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 640
    title: qsTr("Carestream Build Toolkit")

    Popup {
        id: popup
        x: 0
        y: 0
        implicitWidth: root.width
        implicitHeight: root.height
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        function scrollToBottom() {
            scrollBar.position = 1.0
        }

        function appendText(text) {
            log.text += text
        }

        function clearText() {
            log.text = ""
        }

        ColumnLayout {
            anchors.fill: parent
            Flickable {
                id: log_flicker
                Layout.fillHeight: true
                Layout.fillWidth: true

                Keys.onUpPressed: scrollBar.decrease()
                Keys.onDownPressed: scrollBar.increase()

                ScrollBar.vertical: ScrollBar {
                    id: scrollBar
                }
                TextArea.flickable: TextArea {
                    id: log
                    wrapMode: TextArea.Wrap
                    font.family: "Monaco, Consolas, Courier New"
                    readOnly: true
                    background: Rectangle {
                        anchors.fill: parent
                        border.color: log.enabled ? "#21be2b" : "transparent"
                    }
                }
            }
            RowLayout {
                Layout.fillWidth: true
                Item {
                    Layout.fillWidth: true
                }
                Button {
                    text: qsTr("Close")

                    onClicked: {
                        build_process.cancelBuild()
                        popup.close()
                    }
                }
                Item {
                    Layout.fillWidth: true
                }
            }
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            spacing: 6

            ComboBox {
                id: vc_versions
                model: [ "VS2005", "VS2008", "VS2010", "VS2012", "VS2013", "VS2015" ]
            }

            ComboBox {
                id: architecture
                model: [ "x86", "x64" ]
            }

            Item { Layout.fillWidth: true }

            Switch {
                checked: true
                text: qsTr("Notifications")
            }
        }
    }

    LibraryModel {
        id: library_model
    }

    BuildProcess {
        id: build_process
        onMessage:  {
            popup.appendText(message)
            popup.scrollToBottom()
        }
    }

    Frame {
        anchors.fill: parent

        background: Rectangle {
            color: "transparent"
            border.color: "#21be2b"
            radius: 2
        }

        RowLayout {
            id: controls
            width: parent.width
            spacing: 4

            Label {
                id: lbl
                text: qsTr("Build Script Directory:")
                anchors.verticalCenter: parent.verticalCenter
            }

            TextField {
                id: build_script_directory
                Layout.fillWidth: true
                anchors.verticalCenter: parent.verticalCenter
                text: library_model.buildScriptsRootDirectory;
                color: "red"
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("...");
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Set");
                onClicked: library_model.buildScriptsRootDirectory = build_script_directory.text
            }
        }

        ListView {
            id: scanner_list
            width: parent.width
            anchors.top: controls.bottom
            anchors.topMargin: 4
            anchors.bottom: buttons.top
            model: library_model
            clip: true
            spacing: 4
            delegate: ListViewDelegate {
                width: parent.width
                onSelectLibrary: {
                    library_model.selectLibrary(name, version, selected)
                }
            }

            header: ListViewHeader {
                width: parent.width
                height: 30
            }
        }



        Button {
            id: buttons

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            width: (parent.width - 20) * 0.8
            enabled: scanner_list.currentIndex != -1
            text: qsTr("Start Build")
            onClicked: {
                popup.clearText()
                popup.open()
                build_process.build(vc_versions.currentText, architecture.currentText, library_model.selectedLibraries);
            }
        }
    }
}
