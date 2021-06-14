import QtQuick 2.0
import QtQuick.Controls 2.12

import "qrc:/qmluilib/button"
import "qrc:/qmluilib/header"

/*
 * SearchHeader : 搜索控件
 * Author: zfs
 * Date: 2021-06-14 14:40
 */
Item {
    id: searchWin

    // 背景颜色
    property var areaBkColor: "blue"

    // 宽
    property var areaWidth: parent.width
    // 高
    property var areaHeight: 120

    width: areaWidth
    height: areaHeight

    // 背景区域
    Rectangle {
        id: bkWin
        width: parent.width
        height: parent.height
        color: areaBkColor
    }


    // 搜索区域
    SearchBox {
        id: searchBoxId

        anchors {
            top: parent.top
            topMargin: 30
            right: parent.right
            rightMargin: 350
        }

        onSearchBtnClick: function(keyword) {
            console.log("SearchHeader onSearchBtnClick keyword : " + keyword);
        }
    }

}
