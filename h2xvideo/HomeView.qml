import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

import "./qmluilib/bar"
import "./qmluilib/header"

Rectangle {
    id: homeView

    property var pageId : ""
    property var pageParam : ""

    width: parent.width
    height: parent.height
    color: "white"

    // 标题栏
    TitleBar {
        id: titleBarId

        width: parent.width

        onSystemBtnClick: function(sysBtnId) {
            console.log("HomeView TitleBaronSystemBtnClick sysBtnId : " + sysBtnId)

            onSysMenuClick(sysBtnId);
        }
    }

    // 搜索头
    SearchHeader {
        id: searchWin

        anchors {
            top: titleBarId.bottom
            topMargin: 0
        }

        width: parent.width
        boxHeight: 80
        padTop: 15
        padRight: 320
    }

    Text {
        anchors.centerIn: parent
        text: "Hello, World!, home!"
    }

    /*MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("HomeView.qml onClicked.")
            mainViewHandler.routerPageSet("HomeView", "login", "");
        }
    }*/

    function onSysMenuClick(sysBtnId) {
        console.log("HomeView onSysMenuClick sysBtnId : " + sysBtnId)

        if (sysBtnId === "system_btn_min") {
            // 最小化窗口
            mainViewHandler.minAppEvent("HomeView System Btn Min");
        }
        else if (sysBtnId === "system_btn_max") {
            // 最大化窗口
            mainViewHandler.maxAppEvent("HomeView System Btn Max");
        }
        else if (sysBtnId === "system_btn_close") {
            // 关闭窗口
            mainViewHandler.closeApp("HomeView System Btn Close", 0);
        }
    }

}
