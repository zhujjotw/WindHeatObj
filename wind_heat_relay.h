#ifndef _WH_RELAY_H_
#define _WH_RELAY_H_


#ifdef __cplusplus
extern "C"
{
#endif


/* 继电器类 */
typedef struct tagWindHeatRelayClass
{
    U8 u8RelayId;
}WH_REY_CLASS_S;


typedef struct tagRelayCb
{
    //是/否就绪
    BOOL_T bReady;
    //对象
    WH_REY_CLASS_S stRelayObj[BOARD_DISPLAY_NUM];
    //方法
    WH_TSD_METHOD_S stMethod;
}WH_REY_S;



#ifdef __cplusplus
}
#endif

#endif


