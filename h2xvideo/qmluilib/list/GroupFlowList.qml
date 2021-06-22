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

    signal itemClick(int itemId);

    // 数据模型
    ListModel {
        id: listDataModelId
    }
    // 数据列表
    property var datas: []

    // 背景颜色
    property var listBkColor: "transparent"

    // 列表边距
    property var marginLeft: 5
    property var marginTop: 5
    property var marginRight: 5
    property var marginBottom: 5

    // 行列间隔
    property var rowSpace: 10
    property var columnSpace: 10

    // 列表项相关
    // 组名相关
    property var itemGroupNameHeight: 40
    property var itemGroupNameWidth: 100
    property var itemGroupNameFontSize: 18
    property var itemGroupNameMarginLeft: 0
    // 项尺寸
    property var itemWidth: 184
    property var itemHeight: 250
    // 封面尺寸
    property var itemCoverWidth: 184
    property var itemCoverHeight: 190
    // 标题栏高
    property var itemTitleHeight: 30
    property var itemTitleFontSize: 12
    // 描述高
    property var itemDescHeight: 30
    property var itemDescFontSize: 11

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
                top: parent.top
                topMargin: marginTop
            }

            width: parent.width - marginLeft - marginRight
            height: parent.height - marginTop - marginBottom
            contentWidth: width
            contentHeight: height

            Column {
                id: contentId
                // 小组列表
                width: parent.width
                spacing: rowSpace

                Repeater {
                    model: listDataModelId

                    Column {
                        id: groupDataId

                        width: parent.width
                        spacing: rowSpace

                        Row {
                            // 小组名称
                            Rectangle {
                                anchors.verticalCenter: parent.verticalCenter
                                width: itemGroupNameWidth;
                                height: itemGroupNameHeight;
                                color: "transparent"

                                // 小组名称
                                Text {
                                    id: groupNameId

                                    anchors {
                                        verticalCenter: parent.verticalCenter
                                        left: parent.left
                                        leftMargin: itemGroupNameMarginLeft
                                    }

                                    font.pointSize: itemGroupNameFontSize
                                    text: qsTr(groupName)
                                }
                            }

                        } // end Row

                        // 视频列表
                        Flow {
                            width: parent.width
                            spacing: columnSpace

                            anchors {
                                horizontalCenter: parent.horizontalCenter
                            }

                            Repeater {
                                model: videos

                                Rectangle {
                                    id: itemVideoId

                                    width: itemWidth
                                    height: itemHeight
                                    color: "#5F5F5F"

                                    MouseArea {
                                        anchors.fill: parent

                                        onClicked: {
                                            console.log("GroupFlowList itemVideo onClick index id : " + id);
                                            itemClick(id);
                                        }
                                    }

                                    Column {
                                        // 封面图片
                                        Image {
                                            asynchronous: true
                                            cache: false
                                            width: itemCoverWidth
                                            height: itemCoverHeight
                                            source: coverUrl
                                        }

                                        // 标题项
                                        Rectangle {
                                            id: itemTitleId
                                            width: parent.width
                                            height: itemTitleHeight
                                            color: "transparent"
                                            Text {
                                                id: itemTitleTextId

                                                anchors {
                                                    verticalCenter: parent.verticalCenter
                                                }

                                                font.pointSize: itemTitleFontSize
                                                width: parent.width
                                                elide: Text.ElideRight  // 超出部分用省略号代替
                                                color: "#000000"
                                                text: qsTr(title)
                                            }
                                        }

                                        // 描述
                                        Rectangle {
                                            id: itemDescId
                                            width: itemWidth
                                            height: itemDescHeight
                                            color: "transparent"

                                            Text {
                                                id: itemDescTextId

                                                font.pointSize: itemDescFontSize
                                                color: "#000000"
                                                width: parent.width
                                                elide: Text.ElideRight  // 超出部分用省略号代替
                                                text: qsTr(desc)
                                            }
                                        }

                                        // 选项
                                        /*Row {
                                            Rectangle {

                                                width: 100
                                                height: itemOptionHeight
                                                color: "transparent"

                                                Text {
                                                    id: idStarId

                                                    anchors {
                                                        verticalCenter: parent.verticalCenter
                                                        left: parent.left
                                                        leftMargin: 15;
                                                    }
                                                    color: "#000000"
                                                    text: qsTr(JSON.stringify(star))

                                                }
                                            }
                                        }*/

                                    }

                                } // end itemVideoId

                            } // end Repeater

                        } // end Flow

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

        // 计算内容高度
        onCalContentHeight();
    }

    /*
     * FunctionName: onStop
     * Desc: 停止组件
     * Author: zfs
     * Date: 2021-06-20 09:39
     */
    function onStop() {

    }

    /*
     * FunctionName: onCalContentHeight
     * Desc: 计算内容高度
     * Author: zfs
     * Date: 2021-06-21 22:27
     */
    function onCalContentHeight() {

        // 计算内容高
        let lineCount = Math.floor(listId.width / (itemWidth + rowSpace));
        if (lineCount < 1) {
            lineCount = 1;
        }

        // 计算总行数
        let rowCount = 1;
        for(let idx = 0; idx < datas.length; idx++) {
            let itemObj = datas[idx];

            let itemVideosObj = itemObj["videos"];
            let itemRowCount = Math.ceil(itemVideosObj.length / lineCount);
            if (itemRowCount > 0) {
                rowCount += itemRowCount;
            }
            else {
                rowCount += 1;
            }
        }

        // 计算内容高，并修正最小值
        let cHeight = rowCount * (itemHeight + columnSpace + itemGroupNameHeight);
        if (cHeight < listId.height) {
            cHeight = listId.height;
        }

        console.log("---- lineCount " + lineCount + "  --- rowCount " + rowCount + "   cHeight " + cHeight)

        listId.contentHeight = cHeight
    }

}
