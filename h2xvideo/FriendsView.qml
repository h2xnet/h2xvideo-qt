import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

import "./qmluilib/bar"

import "./navbar_data.js" as NavbarData

/*
 * ClassName: FriendsView
 * Desc: 友圈类页面
 * Author: zfs
 * Date: 2021-06-24 07:04
 */

Rectangle {
    id: friendsView

    property var pageId: "friendsId"
    property var pageParam: ""

    width: parent.width
    height: parent.height
    color: "#FF0088"

    // 底部导航栏
    Rectangle {
        id: bottomNavAreaId

        anchors {
            bottom: parent.bottom
            bottomMargin: 10
        }

        z: 1
        width: parent.width
        height: 55
        color: "transparent"

        NavBar {
            id: bottomNavBarId

            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            width: 270
            height: parent.height

            onNavItemClick: function(itemId) {
                //console.log("FriendsView.qml bottomNavBarId onNavItemClick itemId : " + itemId)
                onSimpleNavItemClick(itemId);
            }
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

    /*
     * FunctionName: onSimpleNavItemClick
     * Desc: 统一的导航按钮事件处理函数（简化版）
     * Author: zfs
     * Date: 2021-06-19 17:37
     * @itemId: 导航按钮ID
     */
    function onSimpleNavItemClick(itemId) {
        console.log("FriendsView onSimpleNavItemClick itemId : " + itemId);
        mainViewHandler.routerPageSet("FriendsView", itemId, "");
    }


}


