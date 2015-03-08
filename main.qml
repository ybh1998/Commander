import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import ybh1998.Commander 1.0

ApplicationWindow {
    id:window
    title: qsTr("Commander")
    visible: true
    minimumHeight: 200
    minimumWidth: 400
    Commander{
        id:commander
        onShow: window.visible=true
    }

    TabView{
        anchors.margins: 2
        anchors.fill: parent
        Tab{
            anchors.margins: 4
            title: qsTr("Sender")
            ColumnLayout{
                anchors.margins: 2
                anchors.fill: parent
                RowLayout{
                    Layout.fillWidth: true
                    Label{ text:qsTr("Port:")}
                    TextField{
                        id:server_port
                        validator: IntValidator{bottom: 0;top:65535}
                        text:commander.port()
                    }
                }
                ColumnLayout{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Label{ text:qsTr("Commands:")}
                    TextArea{
                        id:cmds
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
                RowLayout{
                    Label{ text:qsTr("Usual CMDs:")}
                    ComboBox{
                        id:combo
                        model: commander.cmd()
                    }
                    Item{ Layout.fillWidth: true}
                }
                RowLayout{
                    Item{ Layout.fillWidth: true}
                    Button{
                        text:qsTr("Add")
                        onClicked: cmds.text+=combo.currentText+"\n"
                    }
                    Button{
                        text:qsTr("Clear")
                        onClicked: cmds.text=""
                    }
                    Button{
                        text:qsTr("Send")
                        onClicked: commander.send(server_port.text,cmds.text)
                    }

                }
            }
        }
        Tab{
            anchors.margins: 4
            title: qsTr("Receiver")
            ColumnLayout{
                anchors.margins: 2
                Item { Layout.fillHeight: true}
                RowLayout{
                    Label{ text:qsTr("Port:")}
                    TextField{
                        id:client_port
                        validator: IntValidator{bottom: 0;top:65535}
                        text:commander.port()
                    }
                }
                RowLayout{
                    Button{
                        id:stat
                        text:qsTr("Start")
                        onClicked:{
                            if(stat.text===qsTr("Start")){
                                client_port.enabled=false
                                stat.text=qsTr("Stop")
                                commander.start(client_port.text)
                            }else{
                                client_port.enabled=true
                                stat.text=qsTr("Start")
                                commander.stop()
                            }
                        }
                    }
                    Button{ text:qsTr("Hide"); onClicked: window.visible=false}
                }
                Item { Layout.fillHeight: true}
            }
        }
    }
}
