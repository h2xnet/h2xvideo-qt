import QtQuick 2.0
import QtQuick.Controls 2.12

/*
 * ClassName: TextButtonHorBar
 * Desc: 水平文本按钮工具条
 * Author: zfs
 * Date: 2021-06-18 22:28
 */
Item {
    id: textButtonBarId

    // 点击项事件信号
    signal clickItem(var itemId);

    // 按钮数据列表
    property var datas: []
    // 当前选中序号
    property int selIndex: -1
    // 按钮宽
    property var btnWidth: 80
    // 间隔
    property var btnSpace: 2
    // 间隔颜色
    property var btnSpaceColor: "#A8A8A8"
    // 圆角值
    property var roundValue: 10
    //  字体大小
    property var fontSize: 14
    // 字体颜色
    property var fontDefColor: "#FFFFFF"
    property var fontSelColor: "#A8A8A8"
    // 按下状态使能
    property bool repeatEnable: false

    ListModel {
        id: dataListModel
    }

    height: 35

    Rectangle {
        id: listBkWin

        width: parent.width
        height: parent.height
        color: "transparent"
        radius: roundValue

        Row {
            Repeater {
                model: dataListModel

                Row {

                    // 项按钮
                    Rectangle {
                        color: "transparent"
                        width: btnWidth
                        height: textButtonBarId.height
                        radius: roundValue

                        Text {
                            text: title
                            color: selIndex == index ? fontSelColor : fontDefColor
                            font.pointSize: fontSize
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                                verticalCenter: parent.verticalCenter
                            }
                        }

                        MouseArea {
                            anchors.fill: parent

                            // 单击事件
                            onClicked: {
                                if (!repeatEnable && selIndex == index) {
                                    return;
                                }
                                selIndex = index;

                                if (selIndex >= 0 && selIndex < datas.length) {
                                    let itemObj = datas[selIndex];
                                    let itemId = itemObj["id"];
                                    clickItem(itemId);
                                }
                            }
                        }
                    }

                    // 分隔线
                    Rectangle {
                        visible: (index < (dataListModel.count - 1))
                        color: btnSpaceColor
                        width: btnSpace
                        height: textButtonBarId.height - 16
                        radius: roundValue
                        anchors {
                            verticalCenter: parent.verticalCenter
                        }
                    }

                }

            }
        }

    }

    /*
     * FunctionName: onInit
     * Desc: 初始化列表
     * Author: zfs
     * Date: 2021-06-19 16:07
     * @list: 所有项数据列表
     * @curIndex: 当前选中项
     * @roundValue: 圆角值
     */
    function onInit(list, curIndex, roundValue) {
        dataListModel.clear();
        datas = [];
        for(let idx = 0; idx < list.length; idx++) {
            let itemObj = list[idx];

            datas.push(itemObj);
            dataListModel.append(itemObj);
        }

        if (curIndex >= 0 && curIndex < datas.length) {
            selIndex = curIndex;
        }
        else {
            selIndex = -1;
        }

        // 计算宽度
        textButtonBarId.width = datas.length * (btnWidth + btnSpace) - btnSpace;

        // 圆角
        textButtonBarId.roundValue = roundValue;

    }

    /*
     * FunctionName: onSetFontSize
     * Desc: 设置字休大小
     * Author: zfs
     * Date: 2021-06-19 16:07
     */
    function onSetFontSize(fontSize) {
        textButtonBarId.fontSize = fontSize;
    }

    /*
     * FunctionName: onSetFontColor
     * Desc: 设置字休颜色
     * Author: zfs
     * Date: 2021-06-19 16:17
     * @defColor: 默认时的颜色
     * @selColor: 选中时的颜色
     */
    function onSetFontColor(defColor, selColor) {
        textButtonBarId.fontDefColor = defColor;
        textButtonBarId.fontSelColor = selColor;
    }

    /*
     * FunctionName: onSetBtnSpaceColor
     * Desc: 设置按钮分隔线颜色
     * Author: zfs
     * Date: 2021-06-19 17:04
     */
    function onSetBtnSpaceColor(spaceColor) {
        textButtonBarId.btnSpaceColor = spaceColor;
    }

    /*
     * FunctionName: onSetBtnWidth
     * Desc: 设置按钮宽
     * Author: zfs
     * Date: 2021-06-19 16:46
     */
    function onSetBtnWidth(val) {
        btnWidth = val;
    }

    /*
     * FunctionName: onSetRepeatEnable
     * Desc: 是否启用重复输入状态，启用则不允许重复输入，不启用则允许重复输入
     * Author: zfs
     * Date: 2021-06-19 18:13
     * @enable: 启用标志，true则启用，false则禁用，默认不启用
     */
    function onSetRepeatEnable(enable) {
        repeatEnable = enable;
    }

    /*
     * FunctionName: onGetCurSelIndex
     * Desc: 获取当前选中项序号
     * Author: zfs
     * Date: 2021-06-24 22:41
     * 返回值：成功返回大于0序号，失败返回-1
     */
    function onGetCurSelIndex() {
        return selIndex;
    }

    /*
     * FunctionName: onGetCurSelId
     * Desc: 获取当前选中项ID
     * Author: zfs
     * Date: 2021-06-24 22:41
     * 返回值：成功返回ID，失败返回空字符串
     */
    function onGetCurSelId() {
        if (selIndex >= 0 && selIndex < datas.length) {
            let itemObj = datas[selIndex];

            let itemId = itemObj["id"];
            return itemId;
        }
        return "";
    }

}
