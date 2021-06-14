import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

import "./qmluilib/header"

Rectangle {
    id: homeView

    property var pageId : ""
    property var pageParam : ""

    width: parent.width
    height: parent.height
    color: "white"

    // 搜索头
    SearchHeader {
        id: searchWin
    }

    Text {
        anchors.centerIn: parent
        text: "Hello, World!, home!"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("HomeView.qml onClicked.")
            mainViewHandler.routerPageSet("HomeView", "login", "");
        }
    }


}
