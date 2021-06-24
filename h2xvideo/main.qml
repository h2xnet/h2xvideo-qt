import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

import "qrc:/qmluilib/router"

Window {
    id: mainWin

    // 包含标题栏标志
    property bool hasTitleBar: true

    visible: true

    //flags: Qt.Dialog | Qt.FramelessWindowHint

    flags: {
        if (hasTitleBar) {
            return Qt.Window;
        }
        else {
            return Qt.Window | Qt.FramelessWindowHint
        }
    }
    width: 1024 // Screen.desktopAvailableWidth
    height: 668 // Screen.desktopAvailableHeight


    title: qsTr("慧行无限视频")

    //
    // RouterStackView : 路由
    //
    RouterStackView {
        id: routerStack
    }

    // 底部导航栏
    TopNavBarView {
        id: bottomNavBar
        visible: false

        width: parent.width
        height: 55
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
        if (winId.width >= Screen.desktopAvailableWidth && winId.height >= Screen.desktopAvailableHeight) {
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

    //
    // FriendsView : 友圈页面
    //
    FriendsView {
        id: friendsView
        visible: false
        pageId: "friends"
        pageParam: ""
    }

    //
    // FriendsView : 我的页面
    //
    MyView {
        id: myView
        visible: false
        pageId: "my"
        pageParam: ""
    }

    Component.onCompleted: {
        console.log("main.qml Component.onCompleted.")
        // 初始化导航栏
        bottomNavBar.onInit();
        bottomNavBar.onShowHide(false);

        // 初始化页面
        homeView.onInit();
        loginView.onInit();

        friendsView.onInit();
        myView.onInit();

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

            let bottomNavBarShow = true;

            if (pageId === "home") {
                // 首页
                mainWin.hasTitleBar = true;
                routerStack.setReplece(homeView, pageId, pageParam);
            }
            else if (pageId === "login") {
                mainWin.hasTitleBar = false;
                routerStack.setReplece(loginView, pageId, pageParam);
                bottomNavBarShow = false;
            }
            else if (pageId === "friends") {
                // 友圈
                routerStack.setReplece(friendsView, pageId, pageParam);
            }
            else if (pageId === "my") {
                // 我的
                routerStack.setReplece(myView, pageId, pageParam);
            }
            bottomNavBar.onShowHide(bottomNavBarShow);

        }


    }


}
