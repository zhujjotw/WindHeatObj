/**
 *1、提供中断注册机制
 */

#define MAX_INTR_UNIT      4



/* 类主表，新增一个类必须进行注册 */
DEV_CLASS_TAB gstClassTab[DEV_SUM] = \
                                        {\
                                        gstLedObj, 
                                        gstKeyObj, 
                                        gstRelayObj, 
                                        gstDispObj
                                        \};
                                              


U16 CORE_GenDevId(U8 u8Major, U8 u8Sub)
{
    U16 u16iFd;

    u16iFd = ((U16)u8Major << 8 | u8Sub);

    return u16iFd;
}

VOID CORE_RslDevId(U16 iFd, OUT U8 u8Major, OUT U8 u8Sub)
{
    u8Major = (U8)iFd;
    u8Sub = (U8)(iFd >> 8);

    return;
}

DEV_CLASS_TAB CORE_DevOpen(U8 u8DevId)
{
    if ( DEV_SUM <= u8DevId ) /* 用于裁剪 */
    {
        return NULL;
    }
    
    return gstClassTab[u8DevId];
}


/* 暂无资源需要处理 */
VOID CORE_DevClose(U8 u8DevId)
{
    return;
}



#if 0
#endif

/* 中断事件处理 */
VOID CORE_INTR_Proc()
{
	CORE_INTR_TABLE_S *pstIntrTab;
	pstIntrTab = CORE_GetInterTable();
	if ( BP_IS_NULL(pstIntrTab) )
    {
    	return;
    }

    for ( INT i = 0; i < SRC_INTR_BUTT; i++) /* 处理中断 */
    {
        if( pstIntrTab[i].bHappen )
        {
            pstIntrTab[i].CoreIntrFn();
        }
    }
}

/* 时间事件处理 */
VOID CORE_TIME_Proc()
{
    U8 u8TimerId = 0;
	WH_TIME_EVENT_ARRY_OBJ_S *pstTmEventTable = CORE_GetTmEventObj();

	if( BP_IS_NULL(pstIntrTab) )
	{
        return;
	}
	
	for ( INT i = 0; i < CORE_TIME_EVENT_MAX; i++ ) 
	{
		if( gstSysTime.u32jiffies == pstTmEventTable[i].u32Time )
		{
		    u8TimerId = pstTmEventTable[i].u8TimeId;
			pstTmEventTable[i].FnProc(); /* 执行定时器时间 */

		    if ( CORE_TM_ONCE == pstTmEventTable[i].eTmType)  /* 执行完则删除 */
		    {
                (VOID)CORE_TM_Pop(u8TimerId);
		    }
			
		}
	
	}

}

#if 0
#endif


/* 业务总线 链表/数组*/
//gstAppBus

/* read/write/ioctl 参考linux */

/* 驱动总线 链表/数组*/
//gstDevBus





