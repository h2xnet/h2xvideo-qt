import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

// 引入视频插件
import "./qmluilib/media"

/*
 * ClassName: VideoView
 * Desc: 视频页面
 * Author: zfs
 * Date: 2021-07-05
 */
Window {
    id: videoViewId

    title: "播放器"
    width: 800
    height: 600

    color: "transparent"

    onWidthChanged: {

        videoPlayerId.onSizeChange()
    }

    onHeightChanged: {
        videoPlayerId.onSizeChange()
    }

    onWindowStateChanged: {
        videoPlayerId.onSizeChange()
    }

    // 背景窗口
    Rectangle {
        id: bkWinId

        anchors {

        }

        width: parent.width
        height: parent.height
        color: "#AAAAAA"

        // 视频播放插件
        VideoPlayer {
            id: videoPlayerId

            width: parent.width
            height: parent.height

            onDoubleClickVideo: {
                console.log("---------- onDoubleClickVideo ----------")
                // 改变播放器尺寸
                if (onIsMaximized()) {
                    // 全屏模式
                    videoViewId.x = Math.floor((onGetMaxWidth() - 800) / 2)
                    videoViewId.y = Math.floor((onGetMaxHeight() - 600) / 2)
                    videoViewId.width = 800
                    videoViewId.height = 600
                }
                else {
                    // 非全屏模式
                    // 转为全屏幕
                    videoViewId.x = 0
                    videoViewId.y = 0
                    videoViewId.width = Screen.desktopAvailableWidth
                    videoViewId.height = Screen.desktopAvailableHeight
                }
            }

        } // end VideoPlayer videoPlayerId
    }

    /*
     * FunctionName: onStart
     * Desc: 播放视频
     * Author: zfs
     * Date: 2021-07-05 21:55
     */
    function onStart() {
        videoViewId.show();

        // 初始化播放器最大窗口值，为判断最大化做准备
        videoPlayerId.init(onGetMaxWidth(), onGetMaxHeight(), 0, 0.45);
    }

    /*
     * FunctionName: onStop
     * Desc: 停止播放
     * Author: zfs
     * Date: 2021-07-05 21:55
     */
    function onStop() {
        videoViewId.close();
    }

    /*
     * FunctionName: onGetMaxWidth
     * Desc: 获取窗口最大宽度
     * Author: zfs
     * Date: 2021-09-02 10:50
     */
    function onGetMaxWidth() {
        return Screen.desktopAvailableWidth
    }

    /*
     * FunctionName: onGetMaxHeight
     * Desc: 获取窗口最大高度
     * Author: zfs
     * Date: 2021-09-02 10:50
     */
    function onGetMaxHeight() {
        return Screen.desktopAvailableHeight
    }

    /*
     * FunctionName: onIsMaximized
     * Desc: 判断窗口是否是最大化，判断最大化时消除标题栏影响
     * Author: zfs
     * Date: 2021-09-02 10:51
     */
    function onIsMaximized() {
        let titleHeight = 30
        let isMaxWidth = videoViewId.width >= onGetMaxWidth() ? true : false;
        let isMaxHeight = (videoViewId.width >= onGetMaxHeight() - titleHeight) ? true : false
        return (isMaxWidth && isMaxHeight) ? true : false
    }
}
