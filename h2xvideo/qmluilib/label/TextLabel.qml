import QtQuick 2.0
import QtQuick.Controls 2.12

/*
 * ClassName: TextLabel
 * Desc: 文本标签
 * Author: zfs
 * Date: 2021-06-20 13:33
 */
Item {
    //id: textLabelId

    // 背景颜色
    property var bkColor: "#FF0000"
    // 显示文本内容
    property var labelText: ""
    // 字体颜色
    property var fontColor: "#00000"
    // 字体大小
    property var fontSize: 12

    // 对齐方式
    property var marginLeft: 5
    property var marginRight: 5

    width: parent.width
    height: parent.height

    // 背景窗口
    Rectangle {
        width: parent.width
        height: parent.height
        color: bkColor

        Text {
            id: textId

            anchors {
                verticalCenter: parent.verticalCenter
            }
            color: fontColor
            font.pointSize: fontSize
            text: qsTr(labelText)

        }
    }

    function onSetAlimStyle(alimText) {
        if (alimText === "center") {
            textId.anchors.verticalCenter = parent.verticalCenter
        }
        else if (alimText === "right") {
            textId.anchors.right = parent.right
            textId.anchors.rightMargin = marginRight;
        }
        else {
            textId.anchors.left = parent.left
            textId.anchors.leftMargin = marginLeft;
        }
    }

}
