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
            id: "home",
            title: '首页'
        },
        {
            id: "friends",
            title: "友圈"
        },
        {
            id: "my",
            title: "我的"
        }
    ]

    return navDatas;
}

//
// getHotspotTestDatas : 获取热点测试数据
//
function getHotspotTestDatas() {
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
                    desc: "美丽绿色武功山之行,一生值得一去的地方",
                    source: "",
                    coverUrl: "https://pic7.iqiyipic.com/image/20210621/55/94/v_160260694_m_601_480_270.jpg",
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
                    coverUrl: "https://pic9.iqiyipic.com/image/20210622/e6/a4/v_112846088_m_601_m3_260_360.jpg?caplist=jpg,webp,avif",
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
                    coverUrl: "https://pic4.iqiyipic.com/image/20210604/81/a4/v_159888228_m_601_320_180.jpg?caplist=jpg,webp,avif",
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
                    coverUrl: "https://pic5.iqiyipic.com/image/20210615/8e/a4/v_160107478_m_601_260_360.jpg?caplist=jpg,webp,avif",
                    createTime: "",
                    updateTime: ""
                }
            ]
        }
    ]

    return datas;
}

/*
 * FunctionName: getVideoTestListData
 * Desc: 获取视频测试数据
 * Author: zfs
 * Date: 2021-06-25 21:52
 */
function getVideoTestListData() {
    let datas = [
        {
            id: 4,
            title: "007",
            tag: "赌王",
            star: 0,
            desc: "经典系列",
            source: "",
            coverUrl: "https://pic5.iqiyipic.com/image/20210615/8e/a4/v_160107478_m_601_260_360.jpg?caplist=jpg,webp,avif",
            createTime: "",
            updateTime: "",
            groupId: 2,
            groupName: "电影"
        },
        {
            id: 3,
            title: "速度与激情",
            tag: "动作",
            star: 3,
            desc: "经典美国动作大片",
            source: "",
            coverUrl: "https://pic4.iqiyipic.com/image/20210604/81/a4/v_159888228_m_601_320_180.jpg?caplist=jpg,webp,avif",
            createTime: "",
            updateTime: "",
            groupId: 2,
            groupName: "电影"
        },
        {
            id: 1,
            title: "武功山之行",
            tag: "vlog",
            star: 0,
            desc: "美丽绿色武功山之行,一生值得一去的地方",
            source: "",
            coverUrl: "https://pic7.iqiyipic.com/image/20210621/55/94/v_160260694_m_601_480_270.jpg",
            createTime: "",
            updateTime: "",
            groupId: 1,
            groupName:"旅行"
        },
        {
            id: 2,
            title: "玉龙雪山",
            tag: "景点",
            star: 0,
            desc: "丽江玉龙雪山",
            source: "",
            coverUrl: "https://pic9.iqiyipic.com/image/20210622/e6/a4/v_112846088_m_601_m3_260_360.jpg?caplist=jpg,webp,avif",
            createTime: "",
            updateTime: "",
            groupId: 1,
            groupName:"旅行"
        }
    ]

    return datas;
}
