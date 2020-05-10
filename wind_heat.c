/**
 * 
 * 
 * 
 * 
 * 
 * 
 */



WH_LP_TABLE_S gstLpTable[WH_LP_TABLE_MAX] = ;

WH_MODE_CLASS_S gstModeClass[WH_MODE_BUTT];

WH_TIME_EVENT_ARRY_OBJ_S gstTimeEventClass[WH_TIME_EVENT_MAX];
WH_TIME_EVENT_CLASS_S gstTimeEventCb;


WH_CB gstWhCb = {0};

WH_MODE_E WH_MODE_GET_CURRENT()
{
	return gstWhCb.eCurMode;
}

VOID WH_MODE_SET_CURRENT(WH_MODE_E eMode)
{
	gstWhCb.eCurMode = eMode;
}

/* 后续适配多种数据结构 */
U8 WH_Push(WH_TIME_EVENT_ARRY_OBJ_S *pstNode)
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
			if( 0 < pstArryObj.u32Time)
				{
					continue;
				}
			
			gstTimeEventCb.u8NextIdle = i;
			break;
		}


	return u8TimerId;
}

VOID WH_Pop(U8 u8TimerId) /* 销毁一个 */
{
	gstTimeEventCb.u8NextIdle = u8TimerId;
	gstTimeEventCb.pstHead[u8TimerId].u32Time = 0; /* time为0默认销毁 */

	return;
}

VOID WH_CORE_RegistTimer(U32 u32Time, TimeEventProc pfn, OUT u8 *pTimerId)
{
	//定义一个
	WH_TIME_EVENT_ARRY_OBJ_S stTimer;

	stTimer.u32Time = u32Time;
	stTimer.FnProc = pfn;

	*pTimerId = WH_Push(&stTimer);

	return;
}

VOID WH_CORE_DestoryTimer(U8 u8TimerId)
{
	WH_Pop(u8TimerId);
}



//电源键长按短按,任何模式下只有一种结果
U32 WH_MODE_PowerLongPress()
{
	

}

U32 WH_MODE_PowerShortPress()
{
	//切换时钟

}

#if 0
#endif

//时钟模式下长按
U32 WH_MODE_ClockLongPress()
{
	

}

U32 WH_MODE_ClockShortPress()
{
	//切换时钟

}

#if 0
#endif

//时钟模式下长按
//每一个键对应的处理任务
//长按切换一个模式
//短按
U32 WH_MODE_DlLongPress()
{

}

U32 WH_MODE_DlShortPress()
{


}

//
#if 0
#endif

//LP模式下长按
U32 WH_MODE_LpLongPress()
{
	//记录当前的时间

	//记录在LP表上

}

U32 WH_MODE_LpShortPress()
{

}

/* 注册三个模式下的处理 */
U32 WH_MODE_Register()
{
	/* 注册类方法 */
	gstModeClass[WH_MODE_RUN].eParentModeName = WH_MODE_RUN;
	gstModeClass[WH_MODE_RUN].eChildModeName[0] = WH_SUB_MODE_DL;
	gstModeClass[WH_MODE_RUN].eChildModeName[1] = WH_SUB_MODE_CLOCK;
	gstModeClass[WH_MODE_RUN].eModName = WH_MODE_RUN;
	gstModeClass[WH_MODE_RUN].u8ModeDepth = 2;
	gstModeClass[WH_MODE_RUN].astMethod[WH_KEY_SET].LongPress = NULL;
	gstModeClass[WH_MODE_RUN].astMethod[WH_KEY_SET].ShortPress = NULL;
	gstModeClass[WH_MODE_RUN].astMethod[WH_KEY_SET].MainEvent = NULL;  /* 开启电扇，加热器，切换到第一个子模式,注册时间事件 */

	gstModeClass[WH_SUB_MODE_DL].eParentModeName = WH_MODE_RUN;
	gstModeClass[WH_SUB_MODE_DL].eModName = WH_SUB_MODE_DL;
	gstModeClass[WH_SUB_MODE_DL].u8ModeDepth = 0;
	gstModeClass[WH_SUB_MODE_DL].astMethod[WH_KEY_SET].LongPress = NULL; /* 短按进入 */
	gstModeClass[WH_SUB_MODE_DL].astMethod[WH_KEY_SET].ShortPress = NULL;
	gstModeClass[WH_SUB_MODE_DL].astMethod[WH_KEY_SET].MainEvent = NULL; /* 注册定时事件，切换到第二个子模式 */

	gstModeClass[WH_SUB_MODE_CLOCK].eParentModeName = WH_MODE_RUN;
	gstModeClass[WH_SUB_MODE_CLOCK].eModName = WH_SUB_MODE_CLOCK;
	gstModeClass[WH_SUB_MODE_CLOCK].u8ModeDepth = 0;
	gstModeClass[WH_SUB_MODE_CLOCK].astMethod[WH_KEY_SET].LongPress = WH_MODE_ClockLongPress;   /* 记录LP的值 */
	gstModeClass[WH_SUB_MODE_CLOCK].astMethod[WH_KEY_SET].ShortPress = WH_MODE_ClockShortPress; /* 设置时钟值 */
	
	gstModeClass[WH_MODE_IDLE].eParentModeName = WH_MODE_IDLE;
	gstModeClass[WH_MODE_IDLE].eChildModeName[0] = WH_SUB_MODE_CLOCK;
	gstModeClass[WH_MODE_IDLE].eModName = WH_MODE_IDLE;
	gstModeClass[WH_MODE_IDLE].u8ModeDepth = 1;
	gstModeClass[WH_MODE_IDLE].astMethod[WH_KEY_SET].LongPress = NULL;
	gstModeClass[WH_MODE_IDLE].astMethod[WH_KEY_SET].ShortPress = NULL;
	gstModeClass[WH_SUB_MODE_DL].astMethod[WH_KEY_SET].MainEvent = NULL; /* 关闭电机，加热器，切换第一个子模式 */

	for( int i = 0; i < (INT)WH_MODE_BUTT, i++)
	{
		gstModeClass[i].astMethod[WH_KEY_POW].LongPress = WH_MODE_PowerLongPress();
	}

	return BP_SUCCESS;

}


/* 初始化函数 */
U32 WH_MODE_INIT()
{

	//初始化资源
	WH_MODE_Register();
}

U32 WH_MODE_DEINIT()
{
	//模块退出
}

//模块注册，暂不实现


VOID WH_INTR_Proc()
{
	BP_CORE_INTERR_TABLE_S *pstIntrTab;
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

VOID WH_TIME_Proc()
{
	
	for ( INT i = 0; i < SRC_INTR_BUTT; i++) /* 处理中断 */
		{
			if( pstIntrTab[i].bHappen )
				{
					pstIntrTab[i].CoreIntrFn();
				}
		
		}

}





/**
 * 主函数处理
 * 
 */
INT main()
{
	WH_Init();
	//注册中断处理函数
	for (; ;)
		{
			WH_Proc();
			//处理中断链表
			//当前状态
			//

		}


}






