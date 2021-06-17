import QtQuick 2.0
import QtQuick.Controls 2.12

import "qrc:/qmluilib/bar"
import "qrc:/qmluilib/box"
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
    property var boxBkColor: "blue"

    // 宽
    property var boxWidth: parent.width
    // 高
    property var boxHeight: 100
    // 边距
    property var padTop: 20
    property var padRight: 350

    width: boxWidth
    height: boxHeight

    // 背景区域
    Rectangle {
        id: bkWin
        width: boxWidth
        height: boxHeight
        color: boxBkColor
    }

    // 搜索区域
    SearchBox {
        id: searchBoxId

        anchors {
            top: parent.top
            topMargin: searchWin.padTop
            right: parent.right
            rightMargin: searchWin.padRight
        }

        onSearchBtnClick: function(keyword) {
            console.log("SearchHeader onSearchBtnClick keyword : " + keyword);
        }
    }

}
