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
    property var boxBkColor: "#0099FF"
    // 边距
    property var padTop: 20
    property var padRight: 30

    width: parent.width
    height: parent.height

    // 背景区域
    Rectangle {
        id: bkWin
        width: parent.width
        height: parent.height
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

        width: 250
        height: 36

        onSearchBtnClick: function(keyword) {
            console.log("SearchHeader onSearchBtnClick keyword : " + keyword);
        }
    }

}
