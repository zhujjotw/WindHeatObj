

/* set按键软中断处理 */
extern VOID WH_KEY_SET_INTR_FN(VOID);
extern VOID WH_KEY_POW_INTR_FN(VOID);
extern VOID WH_TIM1_INTR_FN(VOID);

/* 中断处理表 */
CORE_INTR_TABLE_S gstInterTable[MAX_INTR_UNIT] = \
{\
    SRC_KEY_SET, FALSE, WH_KEY_SET_INTR_FN,
    SRC_KEY_POW, FALSE, WH_KEY_POW_INTR_FN,
    SRC_TIM1, FALSE, WH_TIM1_INTR_FN,
};

CORE_INTR_TABLE_S *CORE_GetInterTable()
{
	return &gstInterTable;
}

/* 注册一个软中断 */
VOID CORE_RegIntr(U8 u8IntrId, INTR_HANDL *pFn)
{
    return;
}


//销毁一个软中断
VOID CORE_UnRegIntr(U8 u8IntrId)
{
    return;
}


