#ifndef _CORE_TM_H_
#define _CORE_TM_H_


#ifdef __cplusplus
extern "C"
{
#endif


typedef enum tagTimeEventType
{
    CORE_TM_CYCLE = 0,         /* 循环执行 */
    CORE_TM_ONCE,              /* 执行一次即销毁 */

    CORE_TM_BUTT
}CORE_TM_TYPE_E;

typedef enum tagTimeEventListType
{
    WH_TIME_ARRAY = 0, /* 数组 */
    WH_TIME_LINKLIST,  /* 链表 */

    WH_TIME_BUTT
}WH_TIME_LISTTYPE_E;

typedef struct tagTimeEventArryObj
{
    CORE_TM_TYPE_E eTmType;
    U32 u32Time;
    U8 u8TimeId;
    TimeEventProc FnProc; /* 回调处理函数 */
}WH_TIME_EVENT_ARRY_OBJ_S;

typedef struct tagTimeEventClass
{
    WH_TIME_LISTTYPE_E eType;
    U8 u8NextIdle;         /* 记录下一个空闲位 */
    WH_TIME_EVENT_ARRY_OBJ_S *pstHead;
}WH_TIME_EVENT_CLASS_S;


#if 0
#endif

typedef struct tagTimeClass
{
    U32 u32jiffies;   /* 系统滴答数 */
    U8  u8H;
    U8  u8M;
    U8  u8S;
}WH_TIME_S;


#ifdef __cplusplus
}
#endif

#endif



