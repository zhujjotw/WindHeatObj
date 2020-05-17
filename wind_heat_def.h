/**
 * 通用平台定义
 */

 
#ifndef _WH_DEF_H_
#define _WH_DEF_H_


#ifdef __cplusplus
extern "C"
{
#endif

//根据模块加载

#define WH_DELAY_ONCE       15     /* s,默认一次运行时长15秒 */
#define WH_LP_TABLE_MAX     4
#define WH_SUB_MOD_MAX      4


typedef U32 (*MODE_METHOD)();
typedef VOID (*TM_EVENT_HNDL)();

typedef struct tagLpTable
{
	U8 u8LpId;
	WH_TIME_S stTime;
}WH_LP_TABLE_S;

enum
{
    PRESS_SHORT = 0,
    PRESS_LONG,
    PRESS_BUTT
}

typedef struct tagTimeTable
{
	WH_TIME_S stTime;
}WH_TIME_TABLE_S;

enum
{
	WH_SET = 0,
	WH_DISPY,

	WH_BUTT
};

//模式表，由表项确定模式


/**
 * 设置模式枚举
 */
typedef enum tagWindHeatSettingMode
{
	WH_MODE_RUN = 0,       /* 由Dl确定 */
		WH_SUB_MODE_CLOCK, /* 时钟模式 */
	    WH_SUB_MODE_DL,        /* 设置延时模式 */
	WH_MODE_IDLE,
	
	WH_MODE_BUTT
}WH_MODE_E;


/* 模式方法 */
typedef struct tagMODE_METHOD
{
	MODE_METHOD pPress[PRESS_BUTT];
	MODE_METHOD MainEvent;
}WH_MODE_CLASS_METHOD_S;

/* 主模式之间的切换 */
/* 主模式下子模式的切换 */

typedef struct tagWindHeatModeClass
{
	U8 u8ModeDepth;   /* 子模式嵌套深度 */
	//方法类，
	WH_MODE_E eParentModeName;
	WH_MODE_E eChildModeName[WH_SUB_MOD_MAX];
	WH_MODE_E eModName;
	//长按，短按处理
	WH_MODE_CLASS_METHOD_S astMethod[WH_KEY_BUTT];

	//模式之间支持子模式深度，怎么自由变化,只能使用链表
	VOID *pPrivate;

}WH_MODE_CLASS_S;


/* 每一个模式下一个类方法 */

/**
 * 总业务控制块
 */
typedef struct tagWindHeatContrlBlock
{
	WH_MODE_E eCurMode;
	WH_LP_TABLE_S stLptable[WH_LP_TABLE_MAX];       /* 循环表 */
	WH_TIME_TABLE_S stTmTable[WH_BUTT];             /* 时钟 */
	U8  u8DlTm[WH_BUTT];                            /* 持续运行多长时间 */
}WH_CB;


//change mode 切换模式
//

#ifdef __cplusplus
}
#endif

#endif


