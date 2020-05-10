#include "board.h"
#include "wind_heat_display.h"


WH_DISPLAY_S gstDisplayCb;

/* 驱动不分文件写了，避免生成文件过大 */

#if 0
#endif


/* 获取数码管方法
 * 参数:NONE
*/
WH_DISPLAY_OBJ_S *WH_DISP_MethodGet()
{
    return &gstDisplayCb.stMethod;
}


/* 方法-闪烁 
 * 参数:数码管ID
*/
VOID WH_DISP_Twinkle(U8 u8DisplayId)
{


}


/* 方法-闪烁 
 * 参数:数码管ID\显示内容
*/
VOID WH_DISP_Output(U8 u8DisplayId, CHAR cCh)
{


}


#if 0
#endif


/* 注册数码管业务
 * 参数:数码管ID\显示内容
*/





