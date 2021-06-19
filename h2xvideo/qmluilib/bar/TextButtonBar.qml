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
    // 圆角值
    property var roundValue: 10

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
                            color: selIndex == index ? "#A8A8A8" : "#FFFFFF"
                            font.pointSize: 14
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                                verticalCenter: parent.verticalCenter
                            }
                        }

                        MouseArea {
                            anchors.fill: parent

                            // 单击事件
                            onClicked: {
                                if (selIndex == index) {
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
                        color: "#A8A8A8"
                        width: btnSpace
                        height: textButtonBarId.height - 12
                        radius: roundValue
                        anchors {
                            verticalCenter: parent.verticalCenter
                        }
                    }

                }

            }
        }

    }

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

}
