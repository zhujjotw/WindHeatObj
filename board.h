/**
 * 各硬件能力
 */



#define BOARD_SUPPORT_DISPLAY   1
#define BOARD_DISPLAY_NUM       4  /* 4个单独控制数码管 */

#define BOARD_RELAY_NUM         2  /* 继电器数目 */
#define BOARD_LED_NUM           2  /* LED灯数目 */
#define BOARD_KEY_NUM           2  /* 2个触摸按键 */
#define BOARD_DISP_NUM          4  /* 4个数码管对象 */



/* 使用主类型和次类型 */

/* devid table */
enum
{
    DEV_LED      = 0, /* 二值设备 */
    DEV_KEY,
    DEV_RELAY ,
    DEV_DISPLAY, /* 显示设备 */
    DEV_SUM,     
    /* ----以下的模块即裁剪------ */
    
    DEV_BUTT
};

enum
{
    DEV_SUB_LED_GREN = 0,
    DEV_SUB_LED_RED  = 1,
    DEV_SUB_KEY_LEFT = 2,
    DEV_SUB_KEY_RIGT = 3,
    DEV_SUB_RELAY_1  = 4,
    DEV_SUB_RELAY_2  = 5,
    DEV_DISPLAY_1    = 6,
    DEV_DISPLAY_2    = 7,
    DEV_DISPLAY_3    = 8,
    DEV_DISPLAY_4    = 9,

    DEV_SUB_BUTT,
}



























