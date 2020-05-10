/* 继电器业务 */
WH_REY_S gstRey[BOARD_RELAY_NUM];


#if 0
#endif

/* 获取继电器方法
 * 参数:NONE
*/
WH_TSD_METHOD_S *WH_REY_MethodGet()
{
    return &gstRey.stMethod;
}


/* 方法:开 
 * 参数:继电器ID
*/
VOID WH_REY_Open(U8 u8RelayId)
{


}


/* 方法:关 
 * 参数:继电器ID
*/
VOID WH_REY_Close(U8 u8RelayId)
{


}


#if 0
#endif

/*
 * 继电器注册（小内存可以直接调用）
 */

//总线注册，方法注册，不使用链表不好注册，使用数组只能是通过表










