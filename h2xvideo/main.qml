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
    //width: Screen.desktopAvailableWidth
    //height: Screen.desktopAvailableHeight

    width: 800
    height: 600

    //
    // RouterStackView : 路由
    //
    RouterStackView {
        id: routerStack
    }

    //
    // HomeView : 首页页面
    //
    HomeView {
        id: homeView
        visible: false
        pageId: "home"
        pageParam: ""
    }

    function winIsMax(winId) {
        if (winId.width >= winId.maximumWidth && winid>height >= winId.maximumHeight) {
            return true;
        }
        return false;
    }

    //
    // LoginView : 登录页面
    //
    LoginView {
        id: loginView
        visible: false
        pageId: "login"
        pageParam: ""
    }

    Component.onCompleted: {
        console.log("main.qml Component.onCompleted.")
        // 加载主页
        mainViewHandler.routerPageSet("main", "home", "");
    }

    // 信号
    MainViewHandler {
        id: mainViewHandler

        // 页面改变事件
        onRouterPageChangeEvent : function(sender, pageId, pageParam) {
            console.log("main.qml MainViewHandler.onRouterPageChangeEvent.");
            let paramObj = {
                sender: sender,
                pageId: pageId,
                pageParam: pageParam
            }
            console.log("main.qml MainViewHandler.onRouterPageChangeEvent params: " + JSON.stringify(paramObj));

            if (pageId === "home") {
                routerStack.setReplece(homeView, pageId, pageParam);
            }
            else if (pageId === "login") {
                routerStack.setReplece(loginView, pageId, pageParam);
            }

        }

        // app最小化事件
        onMinAppEvent : function(sender) {
            console.log("main.qml MainViewHandler.onMinAppEvent sender : " + sender);

            mainWin.showMinimized();
        }

        // app最大化事件
        onMaxAppEvent: function(sender) {
            console.log("main.qml MainViewHandler.onMaxAppEvent sender : " + sender);
            console.log("------- isMax : " + winIsMax(mainWin))

            if (winIsMax(mainWin)) {
                mainWin.showNormal();
            }
            else {
                mainWin.showMaximized()
            }
        }

    }


}
