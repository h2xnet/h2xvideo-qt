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

    // 搜索头
    SearchHeader {
        id: searchWin

        anchors {
            top: parent.top
            topMargin: 0
        }

        width: parent.width
        boxHeight: 140
        padTop: 50
        padRight: 320
    }

    // 头部导航栏
    NavBar {
        id: topNavBarId

        height: 35
        anchors {
            top: searchWin.bottom
            topMargin: 0
        }

        onNavItemClick: function(itemId) {
            console.log("HomeView.qml topNavBarId onNavItemClick itemId : " + itemId)
        }
    }

    // 底部导航栏
    Rectangle {
        id: bottomNavAreaId

        anchors {
            bottom: homeView.bottom
            bottomMargin: 10
        }
        width: parent.width
        height: 55
        color: "transparent"

        NavBar {
            id: bottomNavBarId

            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            width: 180
            height: parent.height

            onNavItemClick: function(itemId) {
                console.log("HomeView.qml bottomNavBarId onNavItemClick itemId : " + itemId)
            }
        }
    }

    Text {
        anchors.centerIn: parent
        text: "Hello, World!, home!"
    }

    /*
     * FunctionName: onInit
     * Desc: 初始化页面
     * Author: zfs
     * Date: 2021-06-19 08:48
     */
    function onInit() {
        // 初始化头部导航栏
        onInitTopNavBar();

        // 初始化底部导航栏
        onInitBottomNavBar();

    }

    /*
     * FunctionName: onInitTopNavBar
     * Desc: 初始化头部导航栏
     * Author: zfs
     * Date: 2021-06-19 10:57
     */
    function onInitTopNavBar() {
        let navBts = [
            {
                    id: "focus",
                    title: '关注'
            },
            {
                    id: "hotspot",
                    title: "热点"
            },
            {
                    id: "nearby",
                    title: "附近"
            }
        ]

        topNavBarId.onStart(navBts, 1, 'left', 0);
    }

    function onInitBottomNavBar() {
        let navBts = [
            {
                    id: "first",
                    title: '首页'
            },
            {
                    id: "friends",
                    title: "朋友"
            }
        ]

        bottomNavBarId.onStart(navBts, 0, 'center', 10);
    }

}
