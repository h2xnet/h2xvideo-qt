import QtQuick 2.12
import QtQuick.Controls 2.12

/*
 * StackView : 路由器栈视图组件
 */
Item {
    id: routerStackView
    visible: true
    anchors.fill: parent

    // 页面管理器
    StackView {
        id: stack
        anchors.fill: parent
    }

    //
    // FunctionName: setPageParam
    // Desc: 设置页面参数
    // Author: zfs
    // Date: 2021-06-14 10:18
    function setPageParam(pageView, pageId, pageParam) {
        pageView.pageId = pageId;
        pageView.pageParam = pageParam;
    }

    //
    // FunctionName: getDepth
    // Desc: 获取路由栈深度值
    // Author: zfs
    // Date: 2021-06-14 10:02
    function getDepth() {
        return stack.depth;
    }

    //
    // FunctionName: getIsEmpty
    // Desc: 获取是否为空
    // Author: zfs
    // Date: 2021-06-14 10:02
    function getIsEmpty() {
        return stack.empty();
    }

    //
    // FunctionName: goReplece
    // Desc: 替换显示页面，此方法会把之前所有缓存清空
    // Author: zfs
    // Date: 2021-06-14 09:56
    // @pageView: 要显示的页面
    // @pageId: 页面ID
    // @pageParam: 页面参数
    function setReplece(pageView, pageId, pageParam) {
        setPageParam(pageView, pageId, pageParam);
        stack.replace(pageView)
    }

    //
    // FunctionName: setPush
    // Desc: 向栈增加一下页面
    // Author: zfs
    // Date: 2021-06-14 10:25
    function setPush(pageView, pageId, pageParam) {
        setPageParam(pageView, pageId, pageParam);
        stack.push(pageView);
    }

    //
    // FunctionName: setAdvPush（当前有点问题）
    // Desc: 向栈增加一下页面，此函数会先判断历史记录中是否有此页面，如果有则直接显示历史页面，没有则再加入
    // Author: zfs
    // Date: 2021-06-14 10:25
    function setAdvPush(pageView, pageId, pageParam) {
        /*var itemView = getPage(pageId, true);
        if (itemView) {
            //setReplece(pageView, pageId, pageParam);
            setPageParam(pageView, pageId, pageParam);
            stack.replace(pageView);
            return;
        }
        setPush(pageView, pageId, pageParam);*/
        return;
    }

    function setPop() {
        if (stack.depth < 1) {
            return null;
        }
        var pageView = null;
        stack.pop(pageView);
        return pageView;
    }

    //
    // FunctionName: setClear
    // Desc: 清空所有页面
    // Author: zfs
    // Date: 2021-06-14 10:12
    function setClear() {
        if (stack.depth > 0) {
            stack.clear();
        }
    }

    //
    // FunctionName: getCurPage
    // Desc: 获取当前页面
    // Author: zfs
    // Date: 2021-06-14 10:12
    function getCurPage() {
        return stack.view;
    }

    //
    // FunctionName: getCurPageIndex
    // Desc: 获取当前页面索引
    // Author: zfs
    // Date: 2021-06-14 10:22
    function getCurPageIndex() {
        return stack.index;
    }

    //
    // FunctionName: getPage
    // Desc: 根据页面ID获取查找页面
    // Author: zfs
    // Date: 2021-06-14 10:12
    // @pageName: 要查找的页面名称
    // @onlySearchLoadedItems: 为true则只查找已经加载的页面，false则查找所有页面
    function getPage(pageId, onlySearchLoadedItems) {
        var itemView = stack.find(function(item){
            if (pageId === item.pageId) {
                return true;
            }
            else {
                return false;
            }
        }, onlySearchLoadedItems);

        return itemView;
    }

}


