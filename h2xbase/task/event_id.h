#ifndef H2XBASE_TASK_EVENT_ID_H
#define H2XBASE_TASK_EVENT_ID_H

//
// 此文件主要定义事件ID规则
// 用户自定义ID从EVENT_ID_USER_BASE开始往后加，EVENT_ID_USER_BASE之前的为框架内部使用，用户不得使用
// 一个事件ID只能代表团个事件，定义时最好全局唯一
//

#define EVENT_ID_USER_BASE 1000

#endif // H2XBASE_TASK_EVENT_ID_H
