import QtQuick 2.0
import QtQuick.Controls 2.12

/*
 * SearchHeader : 搜索控件
 * Author: zfs
 * Date: 2021-06-14 14:40
 */
Item {
    id: searchWin

    // 背景颜色
    property var bkcolor: "blue"

    // 宽
    property var areaWidth: parent.width
    // 高
    property var areaHeight: 120

    width: areaWidth
    height: areaHeight

    // 背景区域
    Rectangle {
        width: parent.width
        height: parent.height
        color: bkcolor
    }

}
