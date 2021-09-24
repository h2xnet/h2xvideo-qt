import QtQuick 2.0
import QtQuick.Controls 2.12

import "qrc:/qmluilib/list"

import "../router.js" as Router

/*
 * ClassName: HotspotContentView
 * Desc: 热点内容页面
 * Author: zfs
 * Date: 2021-06-24 22:55
 */
Item {
    id: hotspotContentView

    width: parent.width
    height: parent.height

    GroupFlowList {
        id: groupListId

        width: parent.width
        height: parent.height

        onItemClick: function(itemId) {
            console.log("HotspotContentView onItemClick : " + itemId);
            Router.listItemRouter("HotspotContentView", itemId, "");
        }
    }

    /*
     * FunctionName: onStart
     * Desc: 启动
     * Author: zfs
     * Date: 2021-06-24 23:15
     */
    function onStart(listDatas) {
        groupListId.onStart(listDatas);
    }
}
