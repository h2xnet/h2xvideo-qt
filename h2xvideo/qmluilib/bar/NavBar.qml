import QtQuick 2.0
import QtQuick.Controls 2.12

import "qrc:/qmluilib/bar"

/*
 * ClassName: NavBar
 * Desc: 导航栏
 * Author: zfs
 * Date: 2021-06-18 22:15
 */
Item {
    id: navBarWin

    signal navItemClick(var itemId);

    // 导航栏背景颜色
    property var boxBkColor: "#797979"
    // 导航排列方式，可选值：left | center | right，默认left
    property var alimStype: "left"
    // 左边距,alimStype为left时才有意义
    property var marginLeft: 0
    // 右边距，alimStype为right时才有意义
    property var marginRight: 0
    // 圆角值
    property var roundValue: 10

    width: parent.width
    height: 40

    // 背景窗口
    Rectangle {
        id: bkWin

        width: parent.width
        height: parent.height
        color: boxBkColor
        radius: roundValue
    }

    // 导航栏按钮列表
    TextButtonBar {
        id: barBtnsId

        height: parent.height

        onClickItem: function(itemId) {
            //console.log("NavBar TextButtonBar onClickItem itemId : " + itemId)
            navItemClick(itemId);
        }
    }

    /*
     * FunctionName: onStart
     * Desc: 初始化导航栏
     * Author: zfs
     * Date: 2021-06-19 10:24
     * @btns: 导航按钮JSON数组，项包含(id,title)
     * @curIndex: 当前选中项序号，从0开始
     * @alimStyle: 对齐方式
     */
    function onStart(btns, curIndex, alimStyle, roundValue) {
        let paramObj = {
            btns: btns,
            curIndex: curIndex
        }
        console.log("NavBar onStart params : " + JSON.stringify(paramObj))

        // 初始化导航按钮列表
        barBtnsId.onInit(btns, curIndex, roundValue)
        // 初始化显示方式
        onSetAlimStyle(alimStyle);
        // 圆角
        navBarWin.roundValue = roundValue

    }

    function onStop() {

    }

    /*
     * FunctionName: onSetBkColor
     * Desc: 设置导航栏背景颜色
     * Author: zfs
     * Date: 2021-06-19 10:28
     * @color: 颜色值
     */
    function onSetBkColor(color) {
        boxBkColor = color
    }

    /*
     * FunctionName: onSetAlimStyle
     * Desc: 设置导航栏的对齐方式
     * Author: zfs
     * Date: 2021-06-19 10:42
     * @alimText: 对齐方式,left | center | right
     */
    function onSetAlimStyle(alimText) {
        alimStype = alimText;

        if (alimStype == 'center') {
            barBtnsId.anchors.horizontalCenter = navBarWin.horizontalCenter
        }
        else if (alimStype == 'right') {
            barBtnsId.anchors.right = navBarWin.right
            barBtnsId.anchors.rightMargin = marginRight
        }
        else {
            barBtnsId.anchors.left = navBarWin.left
            barBtnsId.anchors.leftMargin = marginLeft
        }
    }

}
