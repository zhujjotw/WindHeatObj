/**
 *1、提供中断注册机制
 */

#define MAX_INTR_UNIT      4
typedef SOFTWARE_INTR_HANDL  VOID(*pfn)();

//中断源
typedef enum tagInterrputSrc
{
	SRC_KEY_SET = 0,
	SRC_KEY_POW,

	SRC_INTR_BUTT
}BP_CORE_INTR_SRC_E;

//中断表，中断ID
//申请一个中断ID
typedef struct tagInterrputTable
{
	//中断源
	BP_CORE_INTR_SRC_E eCoreIntrSrc;

	//中断状态
	BOOL_T bHappen;

	//软中断绑定
	SOFTWARE_INTR_HANDL CoreIntrFn;

}BP_CORE_INTERR_TABLE_S;


BP_CORE_INTERR_TABLE_S gstInterTable[MAX_INTR_UNIT] = \
{\
	SRC_KEY_SET, FALSE, WH_KEY_SET_INTR_FN,\
	SRC_KEY_POW, FALSE, WH_KEY_POW_INTR_FN,\
};

BP_CORE_INTERR_TABLE_S *CORE_GetInterTable()
{
	return &gstInterTable;
}

//注册一个软中断


//销毁一个软中断

#if 0
#endif




/* 业务总线 链表/数组*/
//gstAppBus

/* read/write/ioctl 参考linux */

/* 驱动总线 链表/数组*/
//gstDevBus





