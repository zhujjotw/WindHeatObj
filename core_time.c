#include "core_time.h"


WH_TIME_EVENT_CLASS_S gstTimeEventCb[CORE_TIME_EVENT_MAX];
static WH_TIME_S gstSysTime;


WH_TIME_EVENT_ARRY_OBJ_S *CORE_GetTmEventObj()
{
    return gstTimeEventCb.pstHead;
}

U8 CORE_TM_Push(WH_TIME_EVENT_ARRY_OBJ_S *pstNode)
{
    U8 u8TimerId = 0;
    WH_TIME_EVENT_ARRY_OBJ_S *pstArryObj = NULL;
    if ( CORE_TIME_EVENT_MAX <= gstTimeEventCb.u8NextIdle)
    {
    	return BP_FAILED;
    }
    //寻找数组的空闲位
    gstTimeEventCb.pstHead[gstTimeEventCb.u8NextIdle].FnProc = pstNode->FnProc;
    gstTimeEventCb.pstHead[gstTimeEventCb.u8NextIdle].u32Time = pstNode->u32Time;
    u8TimerId = gstTimeEventCb.u8NextIdle;
    gstTimeEventCb.pstHead[gstTimeEventCb.u8NextIdle].u8TimeId = u8TimerId;

    for (int i = 0; i < CORE_TIME_EVENT_MAX; i++)
    {
        pstArryObj = gstTimeEventCb.pstHead[i];
        if( 0 < pstArryObj.u32Time )
        {
            continue;
        }

        gstTimeEventCb.u8NextIdle = i;
        break;
    }

    return u8TimerId;
}


/* 销毁一个 */
VOID CORE_TM_Pop(U8 u8TimerId) 
{
    gstTimeEventCb.u8NextIdle = u8TimerId;
    gstTimeEventCb.pstHead[u8TimerId].u32Time = 0; /* time为0默认销毁 */

    return;
}

/* 注册一个定时器事件 */
VOID CORE_TM_RegTimer(U32 u32Time, TimeEventProc pfn, OUT u8 *pTimerId, CORE_TM_TYPE_E eTmType)
{
    WH_TIME_EVENT_ARRY_OBJ_S stTimer;

    stTimer.eTmType = eTmType;
    stTimer.u32Time = u32Time;
    stTimer.FnProc = pfn;

    *pTimerId = CORE_TM_Push(&stTimer);

    return;
}

/* 销毁一个定时器事件 */
VOID CORE_TM_DestoryTimer(U8 u8TimerId)
{
    CORE_TM_Pop(u8TimerId);

    return;
}

/* 更新定时器时间 */
VOID CORE_TM_UpdateTm(U8 u8TimerId, U32 u32Time)
{
    gstTimeEventCb.pstHead[u8TimerId].u32Time = u32Time;
}

void* MemSet(void* dst,int val,int size)
{
    char *_dst = (char*)dst;

    for (;0 < size;size--)
    {
        *_dst++ = val;
    }
    return dst;
}

/* 获取系统的时间戳 */
U32 CORE_GetSysTmStamp()
{
    return gstSysTime.u32jiffies; 

}


/* 定时器模块 */
VOID CORE_TM_Init()
{
    /* 初始化数组 */
    MemSet(&gstTimeEventCb, 0, sizeof(gstTimeEventCb) * WH_TIME_EVENT_MAX);
    MemSet(&gstSysTime, 0, sizeof(gstTimeEventCb));

    return;
}

