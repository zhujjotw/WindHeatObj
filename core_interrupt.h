#ifndef _CORE_INTR_H_
#define _CORE_INTR_H_


#ifdef __cplusplus
extern "C"
{
#endif

typedef INTR_HANDL  void(*pfn)(void);

/* 中断源 */
typedef enum tagInterrputSrc
{
    SRC_KEY_SET = 0,
    SRC_KEY_POW,
    SRC_TIM1,

    SRC_INTR_BUTT
}CORE_INTR_SRC_E;


/* 中断表 */
typedef struct tagInterrputTable
{
    CORE_INTR_SRC_E eCoreIntrSrc; /* 中断源 */
    BOOL_T bHappen;                  /* 中断状态 */
    INTR_HANDL *CoreIntrFn; /* 软中断处理函数 */
}CORE_INTR_TABLE_S;


#ifdef __cplusplus
}
#endif

#endif


