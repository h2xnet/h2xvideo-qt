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
    property var boxHeight: 120

    width: boxWidth
    height: boxHeight

    // 背景区域
    Rectangle {
        id: bkWin
        width: parent.width
        height: parent.height
        color: boxBkColor
    }

    // 标题栏
    TitleBar {
        id: titleBarId

        width: parent.width
    }

    // 搜索区域
    SearchBox {
        id: searchBoxId

        anchors {
            top: parent.top
            topMargin: 60
            right: parent.right
            rightMargin: 350
        }

        onSearchBtnClick: function(keyword) {
            console.log("SearchHeader onSearchBtnClick keyword : " + keyword);
        }
    }

}
