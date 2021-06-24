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

    /*
     * FunctionName: onInit
     * Desc: 初始化页面
     * Author: zfs
     * Date: 2021-06-24 21:38
     */
    function onInit() {
    }

}


