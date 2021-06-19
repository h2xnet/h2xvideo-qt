import QtQuick 2.0
import QtQuick.Controls 2.12

import "qrc:/qmluilib/button"

/*
 * ClassName: SearchBox
 * Desc: 搜索框
 * Author: zfs
 * Date: 2021-06-14 20:09
 */
Item {
    id: searchBoxId

    // 单击信号
    signal searchBtnClick(var keyword);

    // 搜索区域背景色
    property var boxBkColor: "#F5F5F5"
    // 搜索区域圆角值
    property var boxRoundValue: 5

    // 搜索按钮
    property var searchBtnWidth: 60
    property var searchBtnHeight: 30

    // 字休大小
    property var inputTextFontSize: 12

    // 间隔宽大小
    property var spaceWidth: 10

    // 边距大小
    property var padLeft: 5
    property var padTop: 2
    property var padRight: 5
    property var padBottom: 2

    // 背景框
    Rectangle {
        width: parent.width
        height: parent.height
        color: boxBkColor
        radius: boxRoundValue

        // 输入区域
        InputBox {
            id: searchTextId

            width: parent.width - spaceWidth
            height: parent.height
            roundValue: boxRoundValue
            inputFontSize: inputTextFontSize

            anchors {
                left: parent.left
                leftMargin: 0
                top: parent.top
                topMargin: 0
                verticalCenter: parent.verticalCenter
            }

            onInputTextChange: function(text) {
                console.log("SearchBox searchTextId onInputTextChange : " + text);
            }
        }

        // 搜索按钮
        RoundButton {
            id: searchBtnId

            anchors {
                top: parent.top
                topMargin: padTop
                right: parent.right
                rightMargin: searchBtnWidth + padRight
            }

            btnWidth: searchBtnWidth
            btnHeight: searchBtnHeight
            btnText: "搜 索"

            // 搜索事件
            onClick: {
                console.log("SearchBox onClick.")
                searchBtnClick(searchTextId.getInputText())
            }
        }

        // 下拉列表框
        /*ComboBox {
            id:combox
            anchors {
                left: parent.left
                leftMargin: 2
                top: parent.bottom
                topMargin: -2
            }
            currentIndex: 0
            model: ListModel {
                id: cbItems
                ListElement { text: "当前节点前"; color: "Yellow" }
                ListElement { text: "当前节点后"; color: "Green" }
            }
            width: 160
            onCurrentIndexChanged: {
                if(currentIndex==0){
                    console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
                    console.debug("0")
                }
                if(currentIndex==1){
                     console.debug("1")
                }
            }
        }*/


    }
}
