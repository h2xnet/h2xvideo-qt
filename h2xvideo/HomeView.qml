import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

import "./qmluilib/bar"
import "./qmluilib/header"
import "./qmluilib/list"

// 子页面
import "./home"

import "./navbar_data.js" as NavbarData
import "./router.js" as Router


/*
 * ClassName: HomeView
 * Desc: 主页面
 * Author: zfs
 */
Rectangle {
    id: homeView

    property var pageId : ""
    property var pageParam : ""

    // 头部选中头部导航项ID，根据它来决定显示的内容
    property var curHeadNavItemId: ""

    // 列表内容边距
    property var contentPadLeft: 30
    property var contentPadTop: 15
    property var contentPadRight: 60
    property var contentPadBottom: 15

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

        z: 1
        width: parent.width
        height: 140
        padTop: 50
        padRight: 30
    }

    // 选项导航栏
    Rectangle {
        id: optionNavBarAreaId

        anchors {
            top: parent.top
            topMargin: 10
            right: parent.right
            rightMargin: 10
        }

        z: 1
        height: 25
        width: 140
        color: "transparent"

        NavBar {
            id: optionNavBarId

            width: parent.width
            height: parent.height
            boxBkColor: "transparent"

            onNavItemClick: function(itemId) {
                //console.log("HomeView.qml optionNavBarId onNavItemClick itemId : " + itemId)
                onSimpleNavItemClick(itemId);
            }
        }
    }

    // 头部导航栏
    NavBar {
        id: topNavBarId

        anchors {
            top: searchWin.bottom
            topMargin: 0
        }

        z: 1
        height: 35

        onNavItemClick: function(itemId) {
            //console.log("HomeView.qml topNavBarId onNavItemClick itemId : " + itemId)

            onSimpleNavItemClick(itemId);
        }
    }

    // 中间内容区域
    Rectangle {
        id: contentAreaId

        anchors {
            top: topNavBarId.bottom
            topMargin: 0
        }

        z: 0
        width: parent.width
        height: (parent.height - searchWin.height - topNavBarId.height)
        color: "#ABABAB"

        // 关注内容
        FocusContentView {
            id: focusContentView

            visible: curHeadNavItemId == "focus"

            anchors {
                left: parent.left
                leftMargin: contentPadLeft
                top: parent.top
                topMargin: contentPadTop
                right: parent.right
                rightMargin: contentPadRight
                bottom: parent.bottom
                bottomMargin: contentPadBottom
            }

            width: parent.width - contentPadLeft - contentPadRight
            height: parent.height - contentPadTop - contentPadBottom
        }

        // 热点内容
        HotspotContentView {
            id: hotspotContentView

            visible: (curHeadNavItemId == "hotspot" || curHeadNavItemId == "")

            anchors {
                left: parent.left
                leftMargin: contentPadLeft
                top: parent.top
                topMargin: contentPadTop
                right: parent.right
                rightMargin: contentPadRight
                bottom: parent.bottom
                bottomMargin: contentPadBottom
            }

            width: parent.width - contentPadLeft - contentPadRight
            height: parent.height - contentPadTop - contentPadBottom
        }

        // 视频内容
        VideoContentView {
            id: videoContentView

            visible: curHeadNavItemId == "video"

            anchors {
                left: parent.left
                leftMargin: contentPadLeft
                top: parent.top
                topMargin: contentPadTop
                right: parent.right
                rightMargin: contentPadRight
                bottom: parent.bottom
                bottomMargin: contentPadBottom
            }

            width: parent.width - contentPadLeft - contentPadRight
            height: parent.height - contentPadTop - contentPadBottom

        }

        // 音频内容
        AudioContentView {
            id: audioContentView

            visible: curHeadNavItemId == "audio"

            anchors {
                left: parent.left
                leftMargin: contentPadLeft
                top: parent.top
                topMargin: contentPadTop
                right: parent.right
                rightMargin: contentPadRight
                bottom: parent.bottom
                bottomMargin: contentPadBottom
            }

            width: parent.width - contentPadLeft - contentPadRight
            height: parent.height - contentPadTop - contentPadBottom
        }

    } // end contentAreaId

    /*
     * FunctionName: onInit
     * Desc: 初始化页面
     * Author: zfs
     * Date: 2021-06-19 08:48
     */
    function onInit() {
        // 初始化选项导航栏
        onInitOptionNavBar();

        // 初始化头部导航栏
        onInitTopNavBar();

        // 初始化内容
        onInitContentList();

    }

    /*
     * FunctionName: onInitOptionNavBar
     * Desc: 初始化选项导航栏
     * Author: zfs
     * Date: 2021-06-19 10:57
     */
    function onInitOptionNavBar() {
        let navDatas = []

        if (mainViewHandler.getIsLogined()) {
            // 已经登录
            navDatas = NavbarData.getLogoutRegistNavDatas();
        }
        else {
            // 未登录
            navDatas = NavbarData.getLoginRegistNavDatas();
        }

        optionNavBarId.onSetBtnFontSize(10)
        optionNavBarId.onSetBtnWidth(60)
        optionNavBarId.onSetBtnFontColor("#000000", "#0000FF");
        optionNavBarId.onSetBtnSpaceColor("#0000FF");
        optionNavBarId.onSetRepeatEnable(true);
        optionNavBarId.onStart(navDatas, -1, "center", 2)
    }

    /*
     * FunctionName: onInitTopNavBar
     * Desc: 初始化头部导航栏
     * Author: zfs
     * Date: 2021-06-19 10:57
     */
    function onInitTopNavBar() {
        let navDatas = NavbarData.getHomeTopNavDatas();
        topNavBarId.onStart(navDatas, 1, 'left', 0);
    }

    /*
     * FunctionName: onInitContentList
     * Desc: 初始化内容列表
     * Author: zfs
     * Date: 2021-06-20 11:19
     */
    function onInitContentList() {
        // 热点
        let hotspotListDatas = NavbarData.getHotspotTestDatas();
        console.log("HomeView.qml onInitContentList NavbarData.getGroupListTestDatas datas : " + JSON.stringify((hotspotListDatas)))
        hotspotContentView.onStart(hotspotListDatas);

        // 视频
        let videoListDatas = NavbarData.getVideoTestListData();
        console.log("HomeView.qml onInitContentList NavbarData.getVideoTestListData datas : " + JSON.stringify(videoListDatas));
        videoContentView.onStart(videoListDatas);
    }

    /*
     * FunctionName: onSimpleNavItemClick
     * Desc: 统一的导航按钮事件处理函数（简化版）
     * Author: zfs
     * Date: 2021-06-19 17:37
     * @itemId: 导航按钮ID
     */
    function onSimpleNavItemClick(itemId) {
        console.log("HomeView onSimpleNavItemClick itemId : " + itemId);
        if (itemId === "focus") {
            // 关注
            curHeadNavItemId = itemId
            //focusContentView.onStart([]);
        }
        else if (itemId === "hotspot") {
            // 热点
            curHeadNavItemId = itemId;
        }
        else if (itemId === "video") {
            // 视频
            curHeadNavItemId = itemId;
        }
        else if (itemId === "audio") {
            // 音频
            curHeadNavItemId = itemId;
        }
        else {
            // 主页面去路由
            Router.navPageRouter("HomeView", itemId, "");
        }

    }

}
