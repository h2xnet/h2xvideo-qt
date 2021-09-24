import QtQuick 2.0
import QtQuick.Controls 2.12

import "qrc:/qmluilib/list"

import "../router.js" as Router

/*
 * ClassName: VideoContentView
 * Desc: 内容内容页面
 * Author: zfs
 * Date: 2021-06-24 23:05
 */

Item {
    id: videoContentView

    width: parent.width
    height: parent.height

    FlowList {
        id: flowListId

        width: parent.width
        height: parent.height

        onItemClick: function(itemId) {
            console.log("VideoContentView onItemClick : " + itemId);
            Router.listItemRouter("VideoContentView", itemId, "");
        }
    }

    /*
     * FunctionName: onStart
     * Desc: 启动
     * Author: zfs
     * Date: 2021-06-24 23:15
     */
    function onStart(listDatas) {
        flowListId.onStart(listDatas);
    }
}
