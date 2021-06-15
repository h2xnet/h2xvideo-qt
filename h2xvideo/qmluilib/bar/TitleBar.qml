﻿import QtQuick 2.0
import QtQuick.Controls 2.12

import "qrc:/qmluilib/button"

/*
 * TitleBar
 * Desc: 标题栏
 * Author: zfs
 * Date: 2021-06-14
 */
Item {
    id: titleBar

    // 标题栏背景颜色
    property var boxBkColor: "white"
    // 标题栏高
    property var boxHeight: 36
    // 标题栏图标
    property var iconUrl: "qrc:/qmluilib/imgs/logo/logo2.jpg"
    // 标题栏文本
    property var titleText: "慧行无限视频"
    // 标题栏字体颜色
    property var titleTextColor: "#000000"
    // 标题栏字体大小
    property var titleTextFontSize: 18

    // 背景区域
    Rectangle {
        width: parent.width
        height: boxHeight
        color: boxBkColor

        // 图标
        Image {
            id: titleIconId
            source: iconUrl
            width: 32
            height: 32

            anchors {
                left: parent.left
                leftMargin: 2
                top: parent.top
                topMargin: 2
            }
        } // end 图标

        // 标题栏文本
        Text {
            id: titleTextId

            color: titleTextColor
            font.pointSize: titleTextFontSize

            text: qsTr(titleText)

            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        } // end 标题栏文本

        // 系统菜单区域
        Rectangle {
            id: sysMenuBoxId

            anchors {
                right: parent.right
                rightMargin: 10
            }

            width: 110
            height: parent.height
            color: "transparent"

            Row {
                spacing: 5
                // 最小化按钮
                ImageButton {
                    id: minBtnId

                    btnWidth: 30
                    btnHeight: 30
                    normalImgUrl: "qrc:/qmluilib/imgs/button/btn_min_normal.png"
                    hoveredImgUrl: "qrc:/qmluilib/imgs/button/btn_min_hovered.png"
                    pressedImgUrl: "qrc:/qmluilib/imgs/button/btn_min_pressed.png"

                    onClick: {
                        console.log("TitleBar minBtn onClick.");
                    }
                }

                // 最大化按钮
                ImageButton {
                    id: maxBtnId

                    btnWidth: 30
                    btnHeight: 30
                    normalImgUrl: "qrc:/qmluilib/imgs/button/btn_max_normal.png"
                    hoveredImgUrl: "qrc:/qmluilib/imgs/button/btn_max_hovered.png"
                    pressedImgUrl: "qrc:/qmluilib/imgs/button/btn_max_pressed.png"

                    onClick: {
                        console.log("TitleBar maxBtn onClick.");
                    }
                }

                // 关闭按钮
                ImageButton {
                    id: closeBtnId

                    btnWidth: 30
                    btnHeight: 30
                    normalImgUrl: "qrc:/qmluilib/imgs/button/btn_close_normal.png"
                    hoveredImgUrl: "qrc:/qmluilib/imgs/button/btn_close_hovered.png"
                    pressedImgUrl: "qrc:/qmluilib/imgs/button/btn_close_pressed.png"

                    onClick: {
                        console.log("TitleBar closeBtn onClick.");
                    }
                }

            }
        } // end 系统菜单区域

    }

}
