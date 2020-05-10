/*****************************************************************************
                浙江宇视科技有限公司(2013)，版权所有
------------------------------------------------------------------------------
                            module.h
    产品名: UWARE
    模块名:
  生成日期: 2013/11/18
      作者: chenjun 00385
  文件描述: module.c 的头文件

------------------------------------------------------------------------------
   修改历史
   日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
#ifndef _MODULE_H_
#define _MODULE_H_

#include "bp_pub_common.h"
#include "vmp_msg.h"

#ifdef  __cplusplus
extern "C"{
#endif

/* Begin Added by taiguangzong/W6152,2018-8-29 of IVSD40668 GDPR法案隐私声明特性 */
/* 初始化代码宏 --pclint告警消除*/
#ifdef WIN32
#define MAIN_DEV_NONMODABILITY_INIT
#else
#define MAIN_DEV_NONMODABILITY_INIT BP_INIT_FUN
#endif
/* End Added by taiguangzong/W6152,2018-8-29 of IVSD40668 GDPR法案隐私声明特性 */

struct tagModule;

typedef struct tagModule MODULE_CLS;

/** 模块基类接口 */
typedef struct tagModuleOpt
{
    U32 (*mod_init)(MODULE_CLS* pstModule, CHAR *pcModuleName);

    U32 (*mod_reg)(MODULE_CLS* pstModule);

    U32 (*mod_unreg)(MODULE_CLS* pstModule);

    U32 (*mod_start)(MODULE_CLS* pstModule);

    U32 (*mod_stop)(MODULE_CLS* pstModule);

    VMP_MSG_CLS* (*mod_recv)(MODULE_CLS* pstModule, VMP_MSG_S *pstVmpMsg);

}MODULE_OPT_IF;

/** 模块基类定义 */
struct tagModule
{
    MODULE_OPT_IF ifOpt;

    CHAR szModuleName[32];

    U32 u32ModuleID;

    BP_MOD_HANDLE hModHdl;

    BP_MOD_REG_PARAM_S stRegParam;

};

/* Begin added by z00348 for IVSD19232 上行onvif裁剪特性 */

/** 模块初始化函数指针 */
typedef MODULE_CLS *  (*MOD_INIT_PF)(CHAR *);  /* Modified by wuxiangbing01294, 2015-05-07 for 新平台上下行国标 */

/** 模块去初始化函数指针 */
typedef VOID (*MOD_DEINIT_PF)(VOID);

/** 模块初始化结构体 */
typedef struct tagModInitCb
{
    BP_DLIST_HEAD_S stNode;
    MOD_INIT_PF     pfnInit;
    MOD_DEINIT_PF   pfnDeInit;
    CHAR            *szName;
}MOD_INIT_CB_S;

/*****************************************************************************
*    Func Name : MOD_RegInitCb
*  Date Created: 2015/5/30
*       Author : zhaoguoing 00348
*  Description : 模块注册
*        Input : IN MOD_INIT_CB_S *pstInitCb 模块信息
*       Output :
*       Return : U32
*      Caution :
*-----------------------------------------------------------------------------
*   Modification History
*   DATE        NAME             DESCRIPTION
*-----------------------------------------------------------------------------
*
******************************************************************************/
EXTERN VOID MOD_RegInitCb
(
    IN MOD_INIT_CB_S *pstInitCb
);
/* End added by z00348 for IVSD19232 上行onvif裁剪特性 */

/*****************************************************************************
  函 数 名: Module_Init
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块初始化接口
  输入参数: MODULE_CLS* pstModule
  输出参数: 无
    返回值: void
    注意点:
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
U32 Module_Init( MODULE_CLS* pstModule, CHAR *pcModuleName);

/*****************************************************************************
  函 数 名: Module_Reg
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块注册接口
  输入参数: MODULE_CLS* pstModule
  输出参数: 无
    返回值: void
    注意点:
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
U32 Module_Reg(MODULE_CLS *pstModule);

/*****************************************************************************
  函 数 名: Module_Start
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块启动接口
  输入参数: MODULE_CLS* pstModule
  输出参数: 无
    返回值: void
    注意点:
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
U32 Module_Start(MODULE_CLS *pstModule);

/*****************************************************************************
  函 数 名: Module_Stop
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块停止接口
  输入参数: MODULE_CLS* pstModule
  输出参数: 无
    返回值: void
    注意点:
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
U32 Module_Stop(MODULE_CLS *pstModule);

/*****************************************************************************
  函 数 名: Module_Unreg
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块注销接口
  输入参数: MODULE_CLS* pstModule
  输出参数: 无
    返回值: void
    注意点:
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
U32 Module_Unreg(MODULE_CLS *pstModule);

/*****************************************************************************
  函 数 名: Module_Start
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块消息处理函数
  输入参数: MODULE_CLS* pstModule
  输出参数: 无
    返回值: void
    注意点:
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
VOID VmpMsgProc(VMP_MSG_S *pstVmpMsg, void* pUserData);


/*****************************************************************************
  函 数 名: Module_Recv
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块消息接收函数
  输入参数: MODULE_CLS* pstModule
            VMP_MSG_S *pstVmpMsg
  输出参数: 无
    返回值: VMP_MSG_CLS*
    注意点:
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
VMP_MSG_CLS* Module_Recv(MODULE_CLS *pstModule, VMP_MSG_S *pstVmpMsg);


/*****************************************************************************
  函 数 名: Module_CreateBase
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块基类构造函数
  输入参数: MODULE_CLS* pstModule
  输出参数: 无
    返回值: void
    注意点: 基类构造函数，不能直接调用
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
VOID Module_CreateBase(MODULE_CLS *pstModule);


/*****************************************************************************
  函 数 名: Module_Create
  创建日期: 2013年11月18日
  作    者: chenjun 00385
  函数描述: 模块构造函数
  输入参数: moduleclass 模块类结构
  输出参数: 无
    返回值: void
    注意点: 基类构造函数，不能直接调用
------------------------------------------------------------------------------
    修改历史                                                                  
    日期        姓名             描述                                        
  --------------------------------------------------------------------------
                                                                              
*****************************************************************************/
#define Module_Create(moduleclass) \
    U32 u32Ret; \
    \
    moduleclass* pstModule = (moduleclass*)BP_malloc(0, sizeof(moduleclass)); \
    if (BP_IS_NULL(pstModule)) \
    { \
        return NULL; \
    } \
    BP_memzero(pstModule, sizeof(moduleclass)); \
    \
    Module_CreateBase((MODULE_CLS*)pstModule); \
    pstModule->stBase.ifOpt.mod_init = __mod_init; \
    pstModule->stBase.ifOpt.mod_recv = __mod_recv; \
    \
    u32Ret = Module_Init((MODULE_CLS*)pstModule, pcModuleName); \
    if (BP_IS_ERR(u32Ret)) \
    { \
        BP_free(pstModule); \
        return NULL; \
    } \
    return pstModule;

#define __Module_Create(moduleclass) \
    {U32 u32Ret; \
    \
    moduleclass* pstModule = (moduleclass*)BP_malloc(0, sizeof(moduleclass)); \
    if (BP_IS_NULL(pstModule)) \
    { \
        NULL; \
    } \
    BP_memzero(pstModule, sizeof(moduleclass)); \
    \
    Module_CreateBase((MODULE_CLS*)pstModule); \
    pstModule->stBase.ifOpt.mod_init = __mod_init; \
    pstModule->stBase.ifOpt.mod_recv = __mod_recv; \
    \
    u32Ret = Module_Init((MODULE_CLS*)pstModule, pcModuleName); \
    if (BP_IS_ERR(u32Ret)) \
    { \
        BP_free(pstModule); \
        NULL; \
    } \
    pstModule;}

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MODULE_H_ */ 

