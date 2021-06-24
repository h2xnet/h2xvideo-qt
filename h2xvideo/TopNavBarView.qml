import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

import "./qmluilib/bar"

import "./navbar_data.js" as NavbarData
import "./router.js" as Router

/*
 * ClassName: TopNavBarView
 * Desc: 顶层导航栏页面
 * Author: zhaofushou
 * Date: 2021-06-24 21:28
 */

// 底部导航栏
Rectangle {
    id: topNavBarView

    anchors {
        bottom: parent.bottom
        bottomMargin: 10
    }

    z: 1
    color: "transparent"

    NavBar {
        id: bottomNavBarId

        anchors {
            horizontalCenter: parent.horizontalCenter
        }

        width: 270
        height: parent.height

        onNavItemClick: function(itemId) {
            //console.log("TopNavBarView.qml bottomNavBarId onNavItemClick itemId : " + itemId)
            Router.navPageRouter("TopNavBarView", itemId, "");
        }
    }

    /*
     * FunctionName: onInit
     * Desc: 初始化页面
     * Author: zfs
     * Date: 2021-06-24 07:11
     */
    function onInit() {
        // 初始化底部导航栏
        onInitBottomNavBar();
    }

    function onShowHide(isShow) {
        if (isShow) {
            topNavBarView.visible = true;
        }
        else {
            topNavBarView.visible = false;
        }
    }

    /*
     * FunctionName: onInitBottomNavBar
     * Desc: 初始化底部导航栏
     * Author: zfs
     * Date: 2021-06-19 10:57
     */
    function onInitBottomNavBar() {
        let navDatas = NavbarData.getBottomNavDatas();
        bottomNavBarId.onStart(navDatas, 0, 'center', 10);
        bottomNavBarId.onSetBtnFontSize(16);
    }

}


