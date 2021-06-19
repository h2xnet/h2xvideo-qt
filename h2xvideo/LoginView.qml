import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

/*
 * ClassName: LoginView
 * Desc: 登录页面
 * Author: zfs
 */
Rectangle {
    id: loginView
    
    property var pageId : ""
    property var pageParam : ""

    width: parent.width
    height: parent.height
    color: "white"

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
