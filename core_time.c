#include "core_time.h"


WH_TIME_EVENT_ARRY_OBJ_S gstTimeEventClass[WH_TIME_EVENT_MAX];
WH_TIME_EVENT_CLASS_S gstTimeEventCb;
WH_TIME_S gstSysTime;


WH_TIME_EVENT_ARRY_OBJ_S *CORE_GetTmEventObj()
{
    return &gstTimeEventClass;
}


U8 CORE_TM_Push(WH_TIME_EVENT_ARRY_OBJ_S *pstNode)
{
	U8 u8TimerId = 0;
	WH_TIME_EVENT_ARRY_OBJ_S *pstArryObj = NULL;
	if ( WH_TIME_EVENT_MAX <= gstTimeEventCb.u8NextIdle)
	{
		return BP_FAILED;
	}
	//寻找数组的空闲位
	gstTimeEventCb.pstHead[gstTimeEventCb.u8NextIdle].FnProc = pstNode->FnProc;
	gstTimeEventCb.pstHead[gstTimeEventCb.u8NextIdle].u32Time = pstNode->u32Time;
	gstTimeEventCb.pstHead[gstTimeEventCb.u8NextIdle].u8TimeId = pstNode->u8TimeId;
	u8TimerId = gstTimeEventCb.u8NextIdle;

    for (int i = 0; i < WH_TIME_EVENT_MAX; i++)
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

VOID CORE_TM_RegistTimer(U32 u32Time, TimeEventProc pfn, OUT u8 *pTimerId)
{
    WH_TIME_EVENT_ARRY_OBJ_S stTimer;

    stTimer.u32Time = u32Time;
    stTimer.FnProc = pfn;

    *pTimerId = CORE_TM_Push(&stTimer);

    return;
}

VOID CORE_TM_DestoryTimer(U8 u8TimerId)
{
	CORE_TM_Pop(u8TimerId);
}

