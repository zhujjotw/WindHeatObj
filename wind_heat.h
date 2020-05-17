#ifndef _WH_H_
#define _WH_H_


#ifdef __cplusplus
extern "C"
{
#endif

#define LP_SET_MAX    4



typedef struct tagWHClass
{
    U8 u8DlTime;                  /* 系统当前的DL时间 */
    
    U8 au8LpTimerId[LP_SET_MAX];  /* LP模式下保存的定时器ID */
    U8 u8LpNum;

    U8 u8SetClockCnt;            /* 时钟设置时的位数 */
    U8 u8ClockTimerId;           /* 时钟设置注册定时器 */
    U8 u8ClockBit[4];            /* 对应到四个数码管显示位 */

}WH_CLASS;
















#ifdef __cplusplus
}
#endif

#endif


