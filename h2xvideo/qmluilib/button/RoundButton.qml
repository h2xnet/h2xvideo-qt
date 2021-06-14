import QtQuick 2.0
import QtQuick.Controls 2.12

/*
 * ClassName: RoundButton
 * Desc: 圆角按钮
 */
Item {
    id: roundButton
    //
    property var areaWidth: 120
    property var areaHeight: 80

    // 背景颜色
    property var bkcolor: "#252525"

    // 圆角值
    property var roundValues: 10

    Rectangle {
        width: areaWidth
        height: areaHeight
        color: bkcolor
        radius: roundValues
    }

}
