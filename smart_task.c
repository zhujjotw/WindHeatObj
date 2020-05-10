/************************************************************************************
Copyright (c) 2012-2019, Zhejiang Uniview Technologies Co., Ltd. All rights reserved.
-------------------------------------------------------------------------------------
                              smart_task.c
  Project Code: UWARE
   Module Name: DEVICE
  Date Created: 2019/06/15
        Author: chenjun/00385
   Description: 智能任务类
-------------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
-------------------------------------------------------------------------------------
  2019/06/15  chenjun       create(代码重构)
************************************************************************************/
#include "bp_pub_common.h"

#include "smart_task.h"

STATIC U32 __init(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    BP_UNUSED_ARG(pTask);
    BP_UNUSED_ARG(pParam);
    return BP_E_CMD_NOT_SUPPORT;
}

STATIC U32 __destroy(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    BP_UNUSED_ARG(pTask);
    BP_UNUSED_ARG(pParam);
    return BP_E_CMD_NOT_SUPPORT;
}

STATIC U32 __do(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    BP_UNUSED_ARG(pTask);
    BP_UNUSED_ARG(pParam);
    return BP_E_CMD_NOT_SUPPORT;
}

STATIC U32 __start(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    BP_UNUSED_ARG(pTask);
    BP_UNUSED_ARG(pParam);
    return BP_E_CMD_NOT_SUPPORT;
}

STATIC U32 __stop(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    BP_UNUSED_ARG(pTask);
    BP_UNUSED_ARG(pParam);
    return BP_E_CMD_NOT_SUPPORT;
}

/*****************************************************************************
  函 数 名: SMARTTASK_Init
  创建日期: 2019年8月20日
  作    者: chenjun/00385
  函数描述: task类--方法--初始化
  输入参数: IN SMART_TASK_C *pTask
            IN VOID *pParam
  输出参数: 无
    返回值: U32
    注意点:
------------------------------------------------------------------------------
    修改历史
    日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
U32 SMARTTASK_Init(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    return pTask->stSmartTaskIf.pfnInit(pTask, pParam);
}

/*****************************************************************************
  函 数 名: SMARTTASK_Destroy
  创建日期: 2019年8月20日
  作    者: chenjun/00385
  函数描述: task类--方法--释放
  输入参数: IN SMART_TASK_C *pTask
            IN VOID *pParam
  输出参数: 无
    返回值: U32
    注意点:
------------------------------------------------------------------------------
    修改历史
    日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
U32 SMARTTASK_Destroy(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    return pTask->stSmartTaskIf.pfnDestroy(pTask, pParam);
}

/*****************************************************************************
  函 数 名: SMARTTASK_Do
  创建日期: 2019年8月20日
  作    者: chenjun/00385
  函数描述: task类--方法--执行
  输入参数: IN SMART_TASK_C *pTask
            IN VOID *pParam
  输出参数: 无
    返回值: U32
    注意点:
------------------------------------------------------------------------------
    修改历史
    日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
U32 SMARTTASK_Do(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    return pTask->stSmartTaskIf.pfnDo(pTask, pParam);
}

/*****************************************************************************
  函 数 名: SMARTTASK_Start
  创建日期: 2019年8月20日
  作    者: chenjun/00385
  函数描述: task类--方法--启动任务
  输入参数: IN SMART_TASK_C *pTask
            IN VOID *pParam
  输出参数: 无
    返回值: U32
    注意点:
------------------------------------------------------------------------------
    修改历史
    日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
U32 SMARTTASK_Start(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    return pTask->stSmartTaskIf.pfnStart(pTask, pParam);
}

/*****************************************************************************
  函 数 名: SMARTTASK_Stop
  创建日期: 2019年8月20日
  作    者: chenjun/00385
  函数描述: task类--方法--停止任务
  输入参数: IN SMART_TASK_C *pTask
            IN VOID *pParam
  输出参数: 无
    返回值: U32
    注意点:
------------------------------------------------------------------------------
    修改历史
    日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
U32 SMARTTASK_Stop(IN SMART_TASK_C *pTask, IN VOID *pParam)
{
    return pTask->stSmartTaskIf.pfnStop(pTask, pParam);
}

/*****************************************************************************
  函 数 名: SMARTTASK_Create
  创建日期: 2019年8月20日
  作    者: chenjun/00385
  函数描述: task类--创建对象
  输入参数: IN SMART_TASK_C *pTask
  输出参数: 无
    返回值: U32
    注意点:
------------------------------------------------------------------------------
    修改历史
    日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
VOID SMARTTASK_Create(IN SMART_TASK_C *pTask)
{
    pTask->stSmartTaskIf.pfnInit = __init;
    pTask->stSmartTaskIf.pfnDestroy = __destroy;
    pTask->stSmartTaskIf.pfnDo= __do;
    pTask->stSmartTaskIf.pfnStart = __start;
    pTask->stSmartTaskIf.pfnStop= __stop;
} 

