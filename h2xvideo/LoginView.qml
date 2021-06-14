import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0


Rectangle {
    id: loginView
    
    property var pageId : ""
    property var pageParam : ""

    width: 200
    height: 100
    color: "red"

    Text {
        anchors.centerIn: parent
        text: "Hello, World!, login!"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("LoginView.qml onClicked.");
            mainViewHandler.routerPageSet("LoginView", "home", "");
        }
    }
    

}
