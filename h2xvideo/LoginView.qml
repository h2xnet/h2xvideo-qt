import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import module.h2xvideo.mainviewhandler 1.0

import "qrc:/qmluilib/bar"
import "qrc:/qmluilib/box"

/*
 * ClassName: LoginView
 * Desc: 登录页面
 * Author: zfs
 */
Rectangle {
    id: loginView
    
    property var pageId : ""
    property var pageParam : ""
    // 登录模式，0为微信二维码登录, 为手机号码登录，
    property var loginModel: 0

    width: parent.width
    height: parent.height
    color: "white"

    // 背景图片
    Image {
        id: bkImage
        source: "qrc:/qmluilib/imgs/login/login_bk_1.jpg"
        width: parent.width
        height: parent.height
    }

    // 登录背景框
    Rectangle {
        id: loginWinId

        anchors {
            top: parent.top
            topMargin: 80
            right: parent.right
            rightMargin: 50
        }

        radius: 20
        width: 320
        height: 400

        // 登录标题框
        Rectangle {
            id: loginTitleArea

            anchors {
                top: loginWinId.top
                topMargin: 10
            }

            color: "transparent"
            radius: parent.radius
            width: parent.width
            height: 35

            Text {
                id: loginTitleTextId

                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

                color: "#000000"
                font.pointSize: 16
                text: {
                    if (loginModel == 0) {
                        return qsTr("微信扫码登录")
                    }
                    else {
                        return qsTr("手机号登录")
                    }
                }
            }
        }

        // 微信二维码显示区域
        Rectangle {
            id: weixiAreaId

            visible: loginModel == 0

            anchors {
                top: parent.top
                topMargin: 45
            }

            width: parent.width
            height: parent.height - 90
            color: "#FF0000"
        }

        // 手机号码输入区域
        Rectangle {
            id: phoneAreaId

            visible: loginModel == 1

            anchors {
                top: parent.top
                topMargin: 45
            }

            width: parent.width
            height: parent.height - 90
            color: "#FFFF00"

            // 手机号码输入框


        }

        // 登录框底部功能区
        Rectangle {
            id: loginBottomAreaId

            anchors {
                bottom: loginWinId.bottom
                bottomMargin: 10
            }

            radius: parent.radius
            width: parent.width
            height: 35
            color: "transparent"

            // 登录导航
            NavBar {
                id: loginNavBarId

                boxBkColor: "transparent"
                width: parent.width
                height: parent.height

                onNavItemClick: function(itemId) {
                    // 设置登录方式
                    if (itemId === "phone") {
                        loginModel = 1;
                    }
                    else {
                        loginModel = 0;
                    }
                }
            }

            // 返回按钮
            Rectangle {
                id: loginBackAreaId

                anchors {
                    right: parent.right
                    rightMargin: 20
                }

                height: parent.height
                width: 40
                color: "transparent"

                Text {
                    id: idBackBtnTextId

                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        verticalCenter: parent.verticalCenter
                    }
                    font.pointSize: 10
                    color: "#0000FF"
                    text: qsTr("返回")
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // 返回事件
                        console.log("LoginView.qml onClicked.");
                        mainViewHandler.routerPageSet("LoginView", "home", "");
                    }
                }
            }
        } //


    }


    /*
     * FunctionName: onInit
     * Desc: 登录页面初始化
     * Author: zfs
     * Date: 2021-06-19 21:58
     */
    function onInit() {
        // 初始化登录导航
        let loginNavDatas = [
            {
                id: "weixiLogin",
                title: "微信扫码"
            },
            {
                id: "phone",
                title: "手机号"
            }
        ]

        loginNavBarId.onSetBtnFontSize(10)
        loginNavBarId.onSetBtnWidth(100);
        loginNavBarId.onSetBkColor("transparent")
        loginNavBarId.onSetBtnFontColor("#000000", "#0000FF")
        loginNavBarId.onStart(loginNavDatas, 0, "center", 10)
    }


}
