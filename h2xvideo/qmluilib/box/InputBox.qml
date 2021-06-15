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

    //
    // 输入文本改变信号函数
    signal inputTextChange(var text);

    // 输入框宽大小
    property var boxWidth: 240
    // 输入框高大小
    property var boxHeight: 30
    // 圆角值
    property var roundValue: 5
    // 输入字体大小
    property var inputFontSize: 24
    // 输入文件字体颜色
    property var inputTextColor: "#A5A5A5"
    // 边距大小
    property var padLeft: 5
    property var padTop: 2
    property var padRight: 5
    property var padBottom: 2

    Rectangle {
        id: inputBkWin

        width: boxWidth
        height: boxHeight
        radius: roundValue

        // 文本输入框
        TextInput {
            id: inputTextId

            anchors {
                left: parent.left
                leftMargin: padLeft
                verticalCenter: parent.verticalCenter
            }
            width: parent.width - padLeft - padRight
            font.pointSize: inputTextFontSize
            color: inputTextColor
            text: ""

            onTextChanged: {
                inputTextChange(inputTextId.text);
            }
        }
    }

    /*
     * FunctionName: getInputText
     * Desc: 获取输入的文本内容
     * Author: zfs
     * Date: 2021-06-15 21:58
     */
    function getInputText() {
        return inputTextId.text
    }

    /*
     * FunctionName: setInputText
     * Desc: 设置输入的文本内容
     * Author: zfs
     * Date: 2021-06-15 21:59
     */
    function setInputText(text) {
        inputTextId.text = text
    }
}
