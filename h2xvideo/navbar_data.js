/*
 * FunctionName: getLoginRegistNavDatas
 * Desc: 获取登录注册导航栏数据
 * Author: zfs
 * Date: 2021-06-19 17:49
 */
function getLoginRegistNavDatas() {
    let navDatas = [
        {
            id: "login",
            title: "登录"
        },
        {
            id: "regist",
            title: "注册"
        }
    ]

    return navDatas
}

/*
 * FunctionName: getLogoutRegistNavDatas
 * Desc: 获取注销注册导航栏数据
 * Author: zfs
 * Date: 2021-06-19 17:49
 */
function getLogoutRegistNavDatas() {
    let navDatas = [
        {
            id: "logout",
            title: "注销"
        },
        {
            id: "regist",
            title: "注册"
        }
    ]

    return navDatas
}

/*
 * FunctionName: getHomeTopNavDatas
 * Desc: 获取首页顶部导航栏数据
 * Author: zfs
 * Date: 2021-06-19 17:49
 */
function getHomeTopNavDatas() {
    let navDatas = [
        {
            id: "focus",
            title: '关注'
        },
        {
            id: "hotspot",
            title: "热点"
        },
        {
            id: "video",
            title: "视频"
        },
        {
            id: "audio",
            title: "音乐"
        }
    ]

    return navDatas;
}

/*
 * FunctionName: getBottomNavDatas
 * Desc: 获取底部导航栏数据
 * Author: zfs
 * Date: 2021-06-19 17:49
 */
function getBottomNavDatas() {
    let navDatas = [
        {
            id: "first",
            title: '首页'
        },
        {
            id: "friends",
            title: "朋友"
        },
        {
            id: "about",
            title: "关于"
        }
    ]

    return navDatas;
}

//
// getGroupListTestDatas : 获取组列表测试数据
//
function getGroupListTestDatas() {
    let datas = [
        {
            groupId: 1,
            groupName:"旅行",
            tags: ["vlog","景点","美食","度假"],
            videos: [
                {
                    id: 1,
                    title: "武功山之行",
                    tag: "vlog",
                    star: 0,
                    desc: "美丽绿色武功山之行",
                    source: "",
                    createTime: "",
                    updateTime: ""
                },
                {
                    id: 2,
                    title: "玉龙雪山",
                    tag: "景点",
                    star: 0,
                    desc: "丽江玉龙雪山",
                    source: "",
                    createTime: "",
                    updateTime: ""
                }
            ]
        },
        {
            groupId: 2,
            groupName:"电影",
            tags: ["动作","科幻","喜剧","爱情"],
            videos: [
                {
                    id: 3,
                    title: "速度与激情",
                    tag: "动作",
                    star: 3,
                    desc: "经典美国动作大片",
                    source: "",
                    createTime: "",
                    updateTime: ""
                },
                {
                    id: 4,
                    title: "007",
                    tag: "赌王",
                    star: 0,
                    desc: "经典系列",
                    source: "",
                    createTime: "",
                    updateTime: ""
                }
            ]
        }
    ]

    return datas;
}
