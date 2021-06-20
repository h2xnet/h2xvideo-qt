import QtQuick 2.0
import QtQuick.Controls 2.12

import "../label"

/*
 * ClassName: GroupFlowList
 * Desc: 按组显示列表模板类
 * Author: zfs
 * Date: 2021-06-20 09:25
 */
Item {
    id: groupFlowListId

    // 数据模型
    ListModel {
        id: listDataModelId
    }
    // 数据列表
    property var datas: []

    // 背景颜色
    property var listBkColor: "#FF0000"

    // 列表边距
    property var marginLeft: 5
    property var marginTop: 5
    property var marginRight: 5
    property var marginBottom: 5

    // 行列间隔
    property var rowSpace: 10
    property var columnSpace: 10

    // 列表项相关
    // 项尺寸
    property var itemWidth: 100
    property var itemHeight: 180
    // 封面尺寸
    property var itemCoverWidth: 90
    property var itemCoverHeight: 110
    // 标题栏高
    property var itemTitleHeight: 20
    // 描述高
    property var itemDescHeight: 30
    // 其它选项
    property var itemOptionHeight: 20

    // 背景窗口
    Rectangle {
        id: bkWinId

        color: listBkColor
        width: parent.width
        height: parent.height

        // 列表
        Flickable {
            id: listId

            anchors {
                left: parent.left
                leftMargin: marginLeft
                top: parent.top
                topMargin: marginTop
                right: parent.right
                rightMargin: marginRight
                bottom: parent.bottom
                bottomMargin: marginBottom
            }

            width: parent.width - marginLeft - marginRight
            height: parent.height - marginTop - marginBottom
            contentWidth: listId.width
            contentHeight: {
                // 计算内容高
                let lineCount = Math.floor(listId.width / (itemWidth + rowSpace));
                if (lineCount < 1) {
                    lineCount = 1;
                }
                // 计算总行数
                let rowCount = Math.ceil(datas.length / lineCount);
                // 计算内容高，并修正最小值
                let cHeight = rowCount * (itemHeight + columnSpace);
                if (cHeight < listId.height) {
                    cHeight = listId.height;
                }
                return cHeight;
            }

            Column {
                id: contentId
                // 小组列表
                width: parent.width

                Repeater {
                    model: listDataModelId

                    Column {
                        id: groupDataId

                        width: parent.width
                        spacing: rowSpace

                        // 小组名称
                        Text {
                            id: groupNameId
                            text: qsTr(groupName)
                        }

                    } // end Column groupDataId

                } // end Repeater

            } // end Column contentId

        } // end Flickable

    }

    /*
     * FunctionName: onStart
     * Desc: 启动组件
     * Author: zfs
     * Date: 2021-06-20 09:39
     */
    function onStart(listDatas) {
        listDataModelId.clear();
        datas = [];

        for(let idx = 0; idx < listDatas.length; idx++) {
            let itemObj = listDatas[idx];

            listDataModelId.append(itemObj);

            datas.push(itemObj);
        }
    }

    /*
     * FunctionName: onStop
     * Desc: 停止组件
     * Author: zfs
     * Date: 2021-06-20 09:39
     */
    function onStop() {

    }

}
