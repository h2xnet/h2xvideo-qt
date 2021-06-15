import QtQuick 2.0
import QtQuick.Controls 2.12

/*
 * ClassName: RoundButton
 * Desc: 圆角按钮
 * Author: zfs
 * Date: 2021-06-14 21:23
 */
Item {
    id: roundBtnId

    // 单击信号
    signal click();

    // 按钮宽
    property var btnWidth: 98
    // 按钮高
    property var btnHeight: 42
    // 按钮背景颜色
    property var btnBkColor: "#F5F5F5"
    // 按钮圆角值
    property var btnRoundValue: 6

    // 按钮文本
    property var btnText: "按钮"
    // 按钮文本颜色
    property var btnTextColor: "#151515"
    // 字休大小
    property var btnFontSize: 12

    // 按钮背景
    Rectangle {
        id: btnBkId
        width: btnWidth
        height: btnHeight
        color: btnBkColor
        radius: btnRoundValue

        // 按钮文本
        Text {
            id: btnTextId
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            color: btnTextColor
            font.pointSize: btnFontSize
            text: btnText
        }

        // 鼠标事件
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("RoundButton onclicked.");
                click();
            }
        }
    }

}
