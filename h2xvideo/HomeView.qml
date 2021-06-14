import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

Rectangle {
    id: homeView

    property var pageId : ""
    property var pageParam : ""

    width: 200
    height: 100
    color: "red"

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
