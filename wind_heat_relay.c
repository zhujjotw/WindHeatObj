/* 二值器件 towvaluedev*/

DEV_CLASS gstLedObj;
DEV_CLASS gstKeyObj;
DEV_CLASS gstRelayObj;
DEV_CLASS gstDispObj;



/* 二值设备 */
int TVD_Write(int iFd, char *buff, int size)
{
    U8 u8Major = 0, u8Sub = 0;
    CORE_RslDevId(iFd, &u8Major, &u8Sub);
    
    switch(u8Major)
    {
        case DEV_LED:
        {
            switch(u8Sub)
            {
                case DEV_SUB_LED_GREN:  
                {
                    PIN_LED_GREN = *buff;
                }

                case DEV_SUB_LED_GREN:
                {
                    PIN_LED_RED = *buff
                }
                default: break;
            }
        }

        case DEV_KEY:
        {
            switch(u8Sub)
            {
                case DEV_SUB_KEY_LEFT:  
                {
                    PIN_KEY_LEFT = *buff;
                }

                case DEV_SUB_KEY_RIGT:
                {
                    PIN_KEY_RIGT = *buff
                }
                default: break;
            }
        }

        case DEV_RELAY:
        {
            switch(u8Sub)
            {
                case DEV_SUB_RELAY_1:  
                {
                    PIN_RELAY_1 = *buff;
                    break;
                }

                case DEV_SUB_RELAY_2:
                {
                    PIN_RELAY_2 = *buff
                    break;
                }
                default: break;
            }
        }

        default: break;
    }

    return ZP_SUCCED
}

int TVD_Read(int iFd, char *buff, int size)
{
    U8 u8Major = 0, u8Sub = 0;
    CORE_RslDevId(iFd, &u8Major, &u8Sub);
    
    switch(u8Major)
    {
        case DEV_LED:
        {
            switch(u8Sub)
            {
                case DEV_SUB_LED_GREN:  
                {
                    *buff = PIN_LED_GREN;
                }

                case DEV_SUB_LED_GREN:
                {
                    *buff = PIN_LED_RED;
                }
                default: break;
            }
        }

        case DEV_KEY:
        {
            switch(u8Sub)
            {
                case DEV_SUB_KEY_LEFT:  
                {
                    *buff = PIN_KEY_LEFT;
                }

                case DEV_SUB_KEY_RIGT:
                {
                    *buff = PIN_KEY_RIGT;
                }
                default: break;
            }
        }

        case DEV_RELAY:
        {
            switch(u8Sub)
            {
                case DEV_SUB_RELAY_1:  
                {
                    *buff = PIN_RELAY_1;
                    break;
                }

                case DEV_SUB_RELAY_2:
                {
                    *buff = PIN_RELAY_2 ;
                    break;
                }
                default: break;
            }
        }

        default: break;
    }


    return ZP_SUCCED
}

/* 显示设备 */
int DISP_Write(int iFd, char *buff, int size)
{
    U8 u8Major = 0, u8Sub = 0;
    CORE_RslDevId(iFd, &u8Major, &u8Sub);

    switch(u8Major)
    {
        case DEV_DISPLAY:
        {
            switch(u8Sub)
            {
                case DEV_DISPLAY_1:  
                case DEV_DISPLAY_2:
                case DEV_DISPLAY_3:
                case DEV_DISPLAY_4:
                {
                    /* 显示字符接口 */
                    DRV_DisplayChar(u8Sub, buff, size);
                }
            
                default: break;
            }
         }

         default: break;
     }
}

int DISP_Read(int iFd, char *buff, int size)
{
    return ZP_SUCCED; /* 暂不支持 */
}

int DISP_Ioctl(int iFd, char cmd, void *arg)
{
    /* 实现闪烁 */

}


/* 注册二值设备 */
VOID DEV_RegistTvd(DEV_CLASS *pstClass)
{
    pstClass->stMethod._read = TVD_Read;
    pstClass->stMethod._write = TVD_Write;
    pstClass->stMethod._ioctl = NULL;

    return;
}

/* 注册二值设备 */
VOID DEV_RegistDisp(DEV_CLASS *pstClass)
{
    pstClass->stMethod._read = DISP_Read;
    pstClass->stMethod._write = DISP_Write;
    pstClass->stMethod._ioctl = DISP_Ioctl;

    return;
}

/* 设备初始化，后续可集成成表 */
VOID DEV_Init()
{
    LED_Init();
    //KEY_Init();
    REY_Init();
    DISP_Init();

    /* 注册接口 */
    DEV_RegistTvd(gstLedObj);
    DEV_RegistTvd(gstKeyObj);
    DEV_RegistTvd(gstRelayObj);
    DEV_RegistDisp(gstDispObj);
    

}



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










