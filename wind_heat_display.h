#ifndef _WH_DISPLAY_H_
#define _WH_DISPLAY_H_


#ifdef __cplusplus
extern "C"
{
#endif


/* 数码管类 */
typedef struct DisplayClass
{
    //属性
    U8 u8Attr;
}WH_DISPLAY_CLASS_S;


/* 数码管方法 */
typedef struct DisplayObj
{
    //属性
    VOID (*twinkle)(U8);
    VOID (*outprint)(U8, CHAR);
}WH_DISPLAY_OBJ_S;


typedef struct tagDisplayCb
{
    //对象
    WH_DISPLAY_CLASS_S stDisplayObj[BOARD_DISPLAY_NUM];
    
    //方法-闪烁;显示字符
    WH_DISPLAY_OBJ_S stMethod;
}WH_DISPLAY_S;




#ifdef __cplusplus
}
#endif

#endif





