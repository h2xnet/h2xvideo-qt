import QtQuick 2.0
import QtQuick.Controls 2.12

/*
 * TitleBar
 * Desc: 标题栏
 * Author: zfs
 * Date: 2021-06-14
 */
Item {
    id: titleBar

    property var bkcolor: "white"
    property var areaHeight: 50

    // 背景区域
    Rectangle {
        width: parent.width
        height: areaHeight
        color: bkcolor
    }

}
