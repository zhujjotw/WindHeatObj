#include "wind_heat_relay.h"

/* LED业务 */
WH_REY_S gstLed[BOARD_LED_NUM];


#if 0
#endif

/* 获取LED方法
 * 参数:NONE
*/
WH_TSD_METHOD_S *WH_LED_MethodGet()
{
    return &gstLed.stMethod;
}


/* 方法:开 
 * 参数:LEDID
*/
VOID WH_LED_Open(U8 u8LedId)
{


}


/* 方法:关 
 * 参数:LEDID
*/
VOID WH_LED_Close(U8 u8LedId)
{


}


#if 0
#endif

/*
 * LED注册（小内存可以直接调用）
 */






