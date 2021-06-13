import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

import "qrc:/qmluilib/router"

Window {
    id: mainWin

    visible: true
    flags: Qt.Dialog | Qt.FramelessWindowHint
    x: 0
    y: 0
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    //
    // RouterStackView : 路由
    //
    //RouterStackView {
    //    id: routerStackView
    //}
    StackView {
        id: routerStackView
        anchors.fill: parent
    }

    //
    // HomeView : 首页页面
    //
    HomeView {
        id: homeView
        visible: false
        pageName: "home"
        pageParam: ""
    }

    //
    // LoginView : 登录页面
    //
    LoginView {
        id: loginView
        visible: false
        pageName: "login"
        pageParam: ""
    }

    Component.onCompleted: {
        console.log("main.qml Component.onCompleted.")
        // 加载主页
        mainViewHandler.routerPageSet("main", "home", "");
    }

    Connections {
        target: mainViewHandler
        onRouterPageChanged: function(sender, pageName, pageParam) {
            console.log("main.qml MainViewHandler.onRouterPageChanged.");
            let paramObj = {
                sender: sender,
                pageName: pageName,
                pageParam: pageParam
            }
            console.log("main.qml MainViewHandler.onRouterPageChanged params: " + JSON.stringify(paramObj));

            if (pageName === "home") {
                routerStackView.push(loginView)
            }
            else if (pageName === "login") {
                routerStackView.push(homeView)
            }
        }
    }

    // 信号
    MainViewHandler {
        id: mainViewHandler
        /*onRouterPageChanged : function(sender, pageName, pageParam) {
            console.log("main.qml MainViewHandler.onRouterPageChanged.");
            let paramObj = {
                sender: sender,
                pageName: pageName,
                pageParam: pageParam
            }
            console.log("main.qml MainViewHandler.onRouterPageChanged params: " + JSON.stringify(paramObj));

            if (pageName === "home") {
                routerStackView.push(loginView)
            }
            else if (pageName === "login") {
                routerStackView.push(homeView)
            }

        }*/

    }

    /*MainViewHandler.onRouterPageChanged : function(sender, pageName, pageParam) {
    console.log("main.qml MainViewHandler.onRouterPageChanged.");
    let paramObj = {
        sender: sender,
        pageName: pageName,
        pageParam: pageParam
    }
    console.log("main.qml MainViewHandler.onRouterPageChanged params: " + JSON.stringify(paramObj));

    if (pageName === "home") {
        routerStackView.push(loginView)
    }
    else if (pageName === "login") {
        routerStackView.push(homeView)
    }

    }*/

}
