import QtQuick 2.0
import QtQuick.Controls 2.12

/*
 * ClassName: InputBox
 * Desc: 输入框
 * Author: zfs
 * Date: 2021-06-14 21:31
 */
Item {
    id: inputBoxId

    // 输入框宽大小
    property var areaWidth: 240
    // 输入框高大小
    property var areaHeight: 30
    // 输入字体大小
    property var inputFontSize: 24
    // 边距大小
    property var paddingLeft: 5
    property var paddingTop: 2
    property var paddingRight: 5
    property var paddingBottom: 2

    Rectangle {
        id: inputBkWin

        width: areaWidth
        height: areaHeight

        // 文本输入框
        TextInput {
            id: inputTextId

            anchors {
                left: parent.left
                leftMargin: paddingLeft
                verticalCenter: parent.verticalCenter
            }
            width: parent.width - paddingLeft - paddingRight
            font.pointSize: inputTextFontSize
            color: "#A5A5A5"
            text: ""
        }
    }
}
