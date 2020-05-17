/**
 * 
 * 
 * 
 * 
 * 
 * 
 */


WH_MODE_CLASS_S gstModeClass[WH_MODE_BUTT];
WH_CLASS gstWHObj;




//返回系统DL时间
U8 WH_GetDlTime()
{
    return gstWHObj.u8DlTime;
}

VOID WH_SetDlTime(U8 u8DlTime)
{
    gstWHObj.u8DlTime = u8DlTime;
}




WH_CB gstWhCb = {0};

WH_MODE_E WH_MODE_Get()
{
	return gstWhCb.eCurMode;
}

VOID WH_MODE_Set(WH_MODE_E eMode)
{
	gstWhCb.eCurMode = eMode;
}


//电源键长按短按,任何模式下只有一种结果
U32 WH_MODE_PowerLongPress()
{
	

}

U32 WH_MODE_PowerShortPress()
{
	//切换时钟
	u8ClockBit[]

	

}

#if 0
#endif

VOID __ClockLpRegTmrHandl()

{
    //打开负离子和加热器

    //打开风扇
    
    //创建一个定时器，DL时间后关闭继电器

    return;
}

/* 时钟模式下长按，保存LP组数 */
U32 WH_MODE_ClockLongPress()
{
    LONG lJiffies = 0, lLpJiffies = 0;
    WH_TIME_EVENT_ARRY_OBJ_S stTimer;
    //获取当前的时间
    lJiffies = CORE_GetSysTmStamp();

    // 创建一个LP时间事件
    lLpJiffies = lJiffies + DAY_TO_SECOND;

    stTimer.eTmType = CORE_TM_CYCLE;
    stTimer.u32Time = lLpJiffies;
    stTimer.FnProc = __ClockLpRegTmrHandl;
    //注册一个定时器时间
    stTimer.u8TimeId =  CORE_TM_RegTimer();

    gstWHObj.au8LpTimerId[gstWHObj.u8LpNum] = stTimer.u8TimeId;
    gstWHObj.u8LpNum++

    if( LP_SET_MAX < gstWHObj.u8LpNum )
    {
        gstWHObj.u8LpNum = 0;
        /* 定时器事件覆盖 */
        CORE_TM_DestoryTimer(gstWHObj.au8LpTimerId[gstWHObj.u8LpNum]);
        gstWHObj.au8LpTimerId[gstWHObj.u8LpNum] = 0;
    }

    return ZP_SUCCED;

}

/* 按键短按处理 */
VOID __ClockSpRegTmrHandl()
{
    gstWHObj.u8SetClockCnt++;

    //FIXME 数码管闪烁

    
    if ( 4 < gstWHObj.u8SetClockCnt )
    {
        gstWHObj.u8SetClockCnt = 0;
        //销毁定时器
        CORE_TM_DestoryTimer(gstWHObj.u8ClockTimerId);
    }

    //切入空闲模式
    WH_MODE_Set(WH_MODE_IDLE);

}

/* 注册一个短按定时器 */
U8 __WH_MODE_ClockSpRegTimer()
{
    LONG lJiffies = 0, lLpJiffies = 0;
    WH_TIME_EVENT_ARRY_OBJ_S stTimer;
    //获取当前的时间
    lJiffies = CORE_GetSysTmStamp();

    // 创建一个LP时间事件
    lLpJiffies = lJiffies + 3;

    stTimer.eTmType = CORE_TM_CYCLE;
    stTimer.u32Time = lLpJiffies;
    stTimer.FnProc = __ClockSpRegTmrHandl;
    //注册一个定时器时间
    stTimer.u8TimeId =  CORE_TM_RegTimer();

    return stTimer.u8TimeId;
}

/* 时钟模式下短按，设置系统时间 */
U32 WH_MODE_ClockShortPress()
{
    LONG lJiffies = 0;
    
    if( !ZP_IS_ZERO(gstWHObj.u8ClockTimerId) )
    {
        lJiffies = CORE_GetSysTmStamp();
        lJiffies += 3;
        //更新定时器时间
        CORE_TM_UpdateTm(gstWHObj.u8ClockTimerId, lJiffies);
    }
    else
    {
        gstWHObj.u8ClockTimerId = __WH_MODE_ClockSpRegTimer();
    }

    /* 注册一个3s定时事件 */
    gstWHObj.u8ClockBit[gstWHObj.u8SetClockCnt]++;

    switch(gstWHObj.u8SetClockCnt)
    {
        case 1:
            if ( 2 < gstWHObj.u8ClockBit[gstWHObj.u8SetClockCnt] )
            {
                gstWHObj.u8ClockBit[gstWHObj.u8SetClockCnt] = 0;
            }
        break;

        case 3:
            if ( 5 < gstWHObj.u8ClockBit[gstWHObj.u8SetClockCnt] )
            {
                gstWHObj.u8ClockBit[gstWHObj.u8SetClockCnt] = 0;
            }
        break;

        case 2:
        case 4:
            if ( 9 < gstWHObj.u8ClockBit[gstWHObj.u8SetClockCnt] )
            {
                gstWHObj.u8ClockBit[gstWHObj.u8SetClockCnt] = 0;
            }
        break;

        default: break;

    }
    gstWHObj.u8SetClockCnt++;

}

#if 0
#endif

/* DL模式下长按，设置DL时间*/
U32 WH_MODE_DlLongPress()
{
    U8 u8DlTime = 0;
    u8DlTime = WH_GetDlTime();

    u8DlTime += 10;   /* 每次的步进值 15 25 35 45 */
    if(u8DlTime >= 45)
    {
        u8DlTime = 15 /* 默认是15 */
    }
    
    WH_SetDlTime(u8DlTime);
    return ZP_SUCCED;
}

U32 WH_MODE_DlShortPress()
{
    return ZP_SUCCED;
}


#if 0
#endif

/* 长按必须关机 */
U32 WH_MODE_PowerLongPress()
{

}

/* 短按切换开和关状态 */
U32 WH_MODE_PowerShortPress()
{

}

#if 0
#endif

/* 注册三个模式下的处理 */
U32 WH_MODE_Register()
{
    /* 注册类方法 */
    gstModeClass[WH_MODE_RUN].eParentModeName = WH_MODE_RUN;
    gstModeClass[WH_MODE_RUN].eChildModeName[0] = WH_SUB_MODE_DL;
    gstModeClass[WH_MODE_RUN].eChildModeName[1] = WH_SUB_MODE_CLOCK;
    gstModeClass[WH_MODE_RUN].eModName = WH_MODE_RUN;
    gstModeClass[WH_MODE_RUN].u8ModeDepth = 2;
    gstModeClass[WH_MODE_RUN].astMethod[WH_KEY_SET].pPress[PRESS_LONG] = NULL;
    gstModeClass[WH_MODE_RUN].astMethod[WH_KEY_SET].pPress[PRESS_SHORT] = NULL;
    gstModeClass[WH_MODE_RUN].astMethod[WH_KEY_SET].MainEvent = NULL;  /* 开启电扇，加热器，切换到第一个子模式,注册时间事件 */

    gstModeClass[WH_SUB_MODE_DL].eParentModeName = WH_MODE_RUN;
    gstModeClass[WH_SUB_MODE_DL].eModName = WH_SUB_MODE_DL;
    gstModeClass[WH_SUB_MODE_DL].u8ModeDepth = 0;
    gstModeClass[WH_SUB_MODE_DL].astMethod[WH_KEY_SET].pPress[PRESS_LONG] = WH_MODE_DlLongPress; /* 短按进入 */
    gstModeClass[WH_SUB_MODE_DL].astMethod[WH_KEY_SET].pPress[PRESS_SHORT] = WH_MODE_DlShortPress;
    gstModeClass[WH_SUB_MODE_DL].astMethod[WH_KEY_SET].MainEvent = NULL; /* 注册定时事件，切换到第二个子模式 */

    gstModeClass[WH_SUB_MODE_CLOCK].eParentModeName = WH_MODE_RUN;
    gstModeClass[WH_SUB_MODE_CLOCK].eModName = WH_SUB_MODE_CLOCK;
    gstModeClass[WH_SUB_MODE_CLOCK].u8ModeDepth = 0;
    gstModeClass[WH_SUB_MODE_CLOCK].astMethod[WH_KEY_SET].pPress[PRESS_LONG] = WH_MODE_ClockLongPress;   /* 记录LP的值 */
    gstModeClass[WH_SUB_MODE_CLOCK].astMethod[WH_KEY_SET].pPress[PRESS_SHORT] = WH_MODE_ClockShortPress; /* 设置时钟值 */

    gstModeClass[WH_MODE_IDLE].eParentModeName = WH_MODE_IDLE;
    gstModeClass[WH_MODE_IDLE].eChildModeName[0] = WH_SUB_MODE_CLOCK;
    gstModeClass[WH_MODE_IDLE].eModName = WH_MODE_IDLE;
    gstModeClass[WH_MODE_IDLE].u8ModeDepth = 1;
    gstModeClass[WH_MODE_IDLE].astMethod[WH_KEY_SET].pPress[PRESS_LONG] = WH_MODE_ClockLongPress;
    gstModeClass[WH_MODE_IDLE].astMethod[WH_KEY_SET].pPress[PRESS_SHORT] = WH_MODE_ClockShortPress;
    gstModeClass[WH_MODE_IDLE].astMethod[WH_KEY_SET].MainEvent = NULL; /* 关闭电机，加热器，切换第一个子模式 */

    for( int i = 0; i < (INT)WH_MODE_BUTT, i++)
    {
        gstModeClass[i].astMethod[WH_KEY_POW].pPress[PRESS_LONG] = WH_MODE_PowerLongPress();
        gstModeClass[i].astMethod[WH_KEY_POW].pPress[PRESS_SHORT] = WH_MODE_PowerShortPress();
    }

    return ZP_SUCCED;

}


VOID WH_KEY_SET_INTR_FN()
{  
    U8 u8Mode = WH_MODE_Get();
    U8 u8PressMode = CORE_PressGet(); 

    MODE_METHOD pFn = gstModeClass[u8Mode].astMethod[WH_KEY_SET].pPress[u8PressMode];
    pFn(); /* 函数执行 */

    return;
}

VOID WH_KEY_POW_INTR_FN()
{  
    U8 u8Mode = WH_MODE_Get();
    U8 u8PressMode = CORE_PressGet(); 

    MODE_METHOD pFn = gstModeClass[u8Mode].astMethod[WH_KEY_POW].pPress[u8PressMode];
    pFn();

    return;
}


/* 初始化函数 */
U32 WH_ModeInit()
{
    //初始化资源
    WH_MODE_Register();
}

U32 WH_ModeDeInit()
{
    //模块退出
    return;
}


/* 显示时间处理 */
VOID WH_DisPlay_Proc()
{
    U8 u8TimerId = 0;
    WH_TIME_EVENT_ARRY_OBJ_S *pstTmEventTable = CORE_GetTmEventObj();

    if( BP_IS_NULL(pstTmEventTable) )
    {
        return;
    }

    for ( INT i = 0; i < WH_TIME_EVENT_MAX; i++ ) 
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



/**
 * 主函数处理
 * 
 */
INT main()
{
    WH_Init();

    for (; ;)
    {
        WH_INTR_Proc();
        WH_TIME_Proc();
        WH_DisPlay_Proc();
    }
}

