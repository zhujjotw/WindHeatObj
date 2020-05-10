/************************************************************************************
Copyright (c) 2012-2019, Zhejiang Uniview Technologies Co., Ltd. All rights reserved.
-------------------------------------------------------------------------------------
                              smart_task.h
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
#ifndef _SMART_TASK_H_
#define _SMART_TASK_H_


#ifdef  __cplusplus
    extern "C"{
#endif

struct tagSmartTask;

typedef struct tagSmartTask SMART_TASK_C;

typedef U32 (*PF_TASK_FUNC_PARAM)(IN SMART_TASK_C *pTask, IN VOID *pParam);

/**
* @struct tagSmartTaskStatus
* @brief 智能任务类型
* @attention
*/
typedef enum tagSmartTaskType
{
    EN_SMART_TASK_TYPE_ONCE,    /** 单次 */

    EN_SMART_TASK_TYPE_LOOP,    /** 循环 */
}EN_SMART_TASK_TYPE_E;

/**
* @struct tagSmartTaskStatus
* @brief 智能任务状态
* @attention
*/
typedef enum tagSmartTaskStatus
{
   EN_SMART_TASK_STATUS_RUN,     /** 运行 */

   EN_SMART_TASK_STATUS_STOP,    /** 停止 */
}EN_SMART_TASK_STATUS_E;

/**
* @struct tagSmartTaskOpt
* @brief 智能任务接口
* @attention
*/
typedef struct tagSmartTaskOpt
{
    PF_TASK_FUNC_PARAM  pfnInit;    /** 初始化 */

    PF_TASK_FUNC_PARAM pfnDestroy;  /** 释放 */

    PF_TASK_FUNC_PARAM pfnDo;       /** 执行 */

    PF_TASK_FUNC_PARAM pfnStart;    /** 启动 */

    PF_TASK_FUNC_PARAM pfnStop;     /** 停止 */

}SMART_TASK_OPT_IF;

/**
* @struct tagSmartTask
* @brief 智能任务类--基类
* @attention
*/
struct tagSmartTask
{
    SMART_TASK_OPT_IF stSmartTaskIf;      /** 接口 */

    EN_SMART_TASK_TYPE_E enTaskType;      /** 任务类型 */

    EN_SMART_TASK_STATUS_E enTaskStatus;  /** 任务状态 */

};

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
U32 SMARTTASK_Init(IN SMART_TASK_C *pTask, IN VOID *pParam);

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
U32 SMARTTASK_Destroy(IN SMART_TASK_C *pTask, IN VOID *pParam);

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
U32 SMARTTASK_Do(IN SMART_TASK_C *pTask, IN VOID *pParam);

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
U32 SMARTTASK_Start(IN SMART_TASK_C *pTask, IN VOID *pParam);

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
U32 SMARTTASK_Stop(IN SMART_TASK_C *pTask, IN VOID *pParam);

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
VOID SMARTTASK_Create(IN SMART_TASK_C *pTask);

#ifdef __cplusplus
}
#endif

#endif 

