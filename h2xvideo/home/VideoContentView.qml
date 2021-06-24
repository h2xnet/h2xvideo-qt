import QtQuick 2.0
import QtQuick.Controls 2.12

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

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#FF00FF"
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
