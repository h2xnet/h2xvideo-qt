import QtQuick 2.0

/*
 * ClassName: ImageButton
 * Desc: 图片按钮
 * Author: zfs
 * Date: 2021-06-15 22:55
 */
Item {
    id: imageButtonId

    signal click();

    // 按钮宽
    property var btnWidth: 20
    // 按钮高
    property var btnHeight: 20
    // 按钮图片
    property var normalImgUrl: ""
    property var hoveredImgUrl: ""
    property var pressedImgUrl: ""

    width: btnWidth
    height: btnHeight

    Image {
        id: imageBtnImgId

        width: btnWidth
        height: btnHeight

        source: normalImgUrl

        MouseArea {
            anchors.fill: parent

            // 图片按钮单击事件
            onClicked: {
                //console.log("ImageButton onClicked.")
                click();
            }
        }
    }
}
