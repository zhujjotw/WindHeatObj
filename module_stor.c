/*****************************************************************************
                浙江宇视科技有限公司(2013)，版权所有
------------------------------------------------------------------------------
                            module_stor.c
    产品名: UWARE
    模块名:
  生成日期: 2013/12/16
      作者: linyanzhang/w0678
  文件描述: module_stor

------------------------------------------------------------------------------
   修改历史
   日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
/* please include system public header files here */
#include "vmp.h"
#include "vmp_inner.h"
#include "bp_pub_common.h"
#include "drv_pub_common.h"
/* Begin added by luweiqi/lW4442 2017-8-16 for NVR支持GPT分区格式 */
#include "bp_ability.h"
/* End added by luweiqi/lW4442 2017-8-16 for NVR支持GPT分区格式 */

/* please include moudle private header files here */
#include "module.h"
#include "stor_def.h"
#include "module_stor.h"
#include "stor_func.h"
#include "stor_raid_func.h"

/* 仅包含本CPP文件使用的头文件. */
#include "vmp_msg_set_stream_info.h"
#include "vmp_msg_record_ctrl.h"
#include "vmp_msg_record_advanced.h"
#include "vmp_msg_qry_record_status.h"
#include "vmp_msg_set_disk_property.h"
#include "vmp_msg_query_disk_list.h"
#include "vmp_msg_init_disk.h"
/* Added by c00524 2014/11/7 for IVSD14386，存储流切换 */
#include "vmp_msg_set_stor_type_inner.h"
/* Begin added by p01365, 2015-02-07 of IVSD17031 */
#include "vmp_msg_qry_disk_smart_info.h"
#include "vmp_msg_qry_vod_status.h"
/* End added by p01365, 2015-02-07 of IVSD17031 */
/* Begin Added by sunxiaojis01884, 2015/4/14 of 新平台上下行国标 */
#include "vmp_msg_qry_dev_status.h"
/* End Added by sunxiaojis01884, 2015/4/14 of 新平台上下行国标 */
/* Begin added by haoxueliang/02253, 2015-05-21 of 空间独享特性 */
#include "vmp_msg_get_chl_quota_msg.h"
#include "vmp_msg_set_chl_quota_msg.h"
#include "vmp_msg_ipc_add_inner.h"
/* End added by haoxueliang/02253, 2015-05-21 of 空间独享特性 */
#include "vmp_msg_get_all_chl_quota_msg.h"  /* Added by haoxueliang/02253, 2015-07-14 of 存储满即停pc-lint消除告警 */
/* Begin added by haoxueliang/02253, 2015-07-14 of 存储满即停特性 */
#include "vmp_msg_query_full_strategy.h"
#include "vmp_msg_set_full_strategy.h"
/* End added by haoxueliang/02253, 2015-07-14 of 存储满即停特性 */
/* BEGIN: Added by zhuhongyan 00342, 2015/5/21 for RAID特性 */
#include "vmp_msg_config_hotspare_disk.h"
#include "vmp_msg_config_raid_info.h"
#include "vmp_msg_qry_raid_info.h"
#include "vmp_msg_manu_create_array.h"
#include "vmp_msg_onekey_create_array.h"
#include "vmp_msg_del_array.h"
#include "vmp_msg_qry_array_list.h"
#include "vmp_msg_qry_phy_disk_list.h"
#include "vmp_msg_rebuild_array.h"
/* END: Added by zhuhongyan 00342, 2015/5/21 for RAID特性 */
/* Begin added by sunxiaoji 01884 2015-8-18 for RAID特性 */
#include "vmp_msg_qry_phy_disk_info.h"
/* End added by sunxiaoji 01884 2015-8-18 for RAID特性 */
/* Begin Added by haoxueliang02253, 2015-09-05 of 硬盘坏道检测特性 */
#include "vmp_msg_set_disk_smart_info.h"
#include "vmp_msg_qry_smart_fail_enable.h"
#include "vmp_msg_set_smart_fail_enable.h"
#include "vmp_msg_qry_disk_bad_sector.h"
#include "vmp_msg_set_disk_bad_sector.h"
#include "vmp_msg_qry_bad_sector_disk_num.h"
/* End Added by haoxueliang02253, 2015-09-05 of 硬盘坏道检测特性 */
#include "vmp_msg_plan_report_store_inner.h" /* Added by j01376 2016/1/8 for IVSD23715 */
/* Begin Added by yangbing/02874 2015-11-17 for 盘组管理特性 */
#include "vmp_msg_config_diskgroup_status.h"
#include "vmp_msg_get_inuse_diskgroup.h"
#include "vmp_msg_qry_diskgroup_status.h"
/* End Added by yangbing/02874 2015-11-17 for 盘组管理特性 */

/* Begin Added by liujie/03326 2016-09-20 for 告警联动优化特性 */
#include "vmp_msg_event_tag.h"
/* End Added by liujie/03326 2016-09-20 for 告警联动优化特性 */

/* Begin added by yangbing/02874 2017-06-01 for 人脸20G文件系统 */
#include "vmp_msg_get_disk_mode.h"
#include "vmp_msg_set_disk_mode.h"
/* End added by yangbing/02874 2017-06-01 for 人脸20G文件系统 */
/* Begin Added by qulei/W4082 2017-7-11 for 硬盘休眠定制特性 */
#include "vmp_msg_get_disk_sleep_info.h"
#include "vmp_msg_set_disk_sleep_info.h"
/* End Added by qulei/W4082 2017-7-11 for 硬盘休眠定制特性 */

/* Begin Added by wanglixin/W6226 2018-10-12 for 苏州监狱查询阵列整改特性，根据磁盘类型查询磁盘信息 */
#include "vmp_msg_qry_disk_list_by_type.h"
/* End Added by wanglixin/W6226 2018-10-12 for 苏州监狱查询阵列整改特性，根据磁盘类型查询磁盘信息 */

/* Begin added by liangzhiwei/lW5741 2019.3.14 of IVSD42944 for SHM合主线 */
#include "vmp_msg_qry_disk_shm_ability.h"
#include "vmp_msg_qry_disk_shm_info.h"
/* End added by liangzhiwei/lW5741 2019.3.14 of IVSD42944 for SHM合主线 */

/* Begin added by huanglingfeng/h06787 2019.9.30 for 存储容错及提示问题优化特性 */
#include "vmp_msg_qry_stor_rec_snap_inner.h"
/* End added by huanglingfeng/h06787 2019.9.30 for 存储容错及提示问题优化特性  */

/* Begin added by huanglingfeng/06787 2019-08-08 for 易用性七期 */
#include "vmp_msg_qry_disk_key_info.h"
/* End added by huanglingfeng/06787 2019-08-08 for 易用性七期 */
#include "vmp_msg_get_smtb_upgrade_ability.h"
#include "vmp_msg_smtb_cap_expands.h"
/* Begin added by huanglingfeng/06787 2019-12-10 for 易用性八期 */
#include "vmp_msg_qry_disk_remain_time_info.h"
/* End added by huanglingfeng/06787 2019-12-10 for 易用性八期 */

/* please define all global variables here */

/* Begin Added by zhengguoqiang/z03968, 2018-3-12 of IVSD37963 for 盘组裁剪 */
/* 初始化代码宏 */
#ifdef WIN32
#define MOD_STOR_INIT
#else
#define MOD_STOR_INIT BP_INIT_FUN
#endif
/* End Added by zhengguoqiang/z03968, 2018-3-12 of IVSD37963 for 盘组裁剪 */

/* Begin Modified by yangbing/02874 2016-6-3 for IVSD28780 NVR支持NAS存储设备 */
EXTERN MOD_FUNC_OPTIONAL_S gastStorModFuncOpt[];
/* End Modified by yangbing/02874 2016-6-3 for IVSD28780 NVR支持NAS存储设备 */

/* Begin Added by huanglingfeng/h06787, 2019-9-9 of 存储容错及提示问题优化特性 */
MODULE_STOR_CLS *gpstModuleStor = NULL;
/* End Added by huanglingfeng/h06787, 2019-9-9 of 存储容错及提示问题优化特性 */

#ifdef  __cplusplus
extern "C"{
#endif

#ifdef COMPILE_MT
/*****************************************************************************
*    Func Name : __mod_reg_mt
*  Date Created: 2014/2/28
*       Author : Sunbing/01391
*  Description : stor模块，mt注册
*        Input : MODULE_CLS  *pstModuleCls
*       Output :
*       Return : U32
*      Caution :
*-----------------------------------------------------------------------------
*   Modification History
*   DATE        NAME             DESCRIPTION
*-----------------------------------------------------------------------------
*
******************************************************************************/
/* Begin added by yangbing/02874 2017-09-20 for IVSD35080 */
STATIC  U32 __mod_reg_mt
(
    BP_MOD_HANDLE  hModHdl
)
{
    U32 u32Ret;
    MT_CMD_ELEMENT_S stStatus;
    MT_CMD_ELEMENT_S stCmdId;
    MT_CMD_ELEMENT_S stDev;
    /* Begin added by liangzhiwei/lW5741 2019.3.4 of IVSD42944 for SHM合主线 */
    MT_CMD_ELEMENT_S stSHMAbility;
    MT_CMD_ELEMENT_S stSHMInfo;
    /* End added by liangzhiwei/lW5741 2019.3.4 of IVSD42944 for SHM合主线 */
    MT_CMD_ELEMENT_S stDiskMod;
    //MT_CMD_ELEMENT_S stParam;

    stStatus = MT_TITLE_CMD_ELEM_INIT(MT_CMD_ID_INVAL, "status", "To Display stor status info");
    stCmdId  = BP_MT_INT_CMD_ELEM_INIT(MT_CMD_ID_VAL, "Channel ID (0 - print all)", 0, BP_U32_MAX);
    u32Ret   = BP_MT_RegMtCmd(hModHdl, STOR_DispStatus_mt, MT_CMD_DISP_ELEM, &stStatus, &stCmdId, NULL);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_MT_RegMtCmd set failed.");
        return u32Ret;
    }

    stDev = MT_TITLE_CMD_ELEM_INIT(MT_CMD_ID_INVAL, "clear", "To clear 20G part");
    u32Ret = BP_MT_RegMtCmd(hModHdl, STOR_Clear_20G_Part_mt, MT_CMD_SET_ELEM, &stDev, NULL, NULL);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_MT_RegMtCmd set failed.");
        return u32Ret;
    }

    /* Begin added by mawenlong/05264 2018-08-16 for IVSD40211 */
    stDev     = MT_TITLE_CMD_ELEM_INIT(MT_CMD_ID_INVAL, "diskmod", "Set disk mode");
    stDiskMod = BP_MT_INT_CMD_ELEM_INIT(MT_CMD_ID_VAL, "2:old disk mod 3:New 20G disk mod", UW_DISK_MODE_OLD_NO20G, UW_DISK_MODE_NEW_20G);
    u32Ret    = BP_MT_RegMtCmd(hModHdl, STOR_Disk_Mod_mt, MT_CMD_SET_ELEM, &stDev, &stDiskMod, NULL);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_MT_RegMtCmd set failed.");
        return u32Ret;
    }
    /* End added by mawenlong/05264 2018-08-16 for IVSD40211 */

    /* Begin added by liangzhiwei/lW5741 2019.3.4 of IVSD42944 for SHM合主线 */
    stSHMAbility = MT_TITLE_CMD_ELEM_INIT(MT_CMD_ID_INVAL, "shmability", "To display disk which support shm feature.");
    u32Ret       = BP_MT_RegMtCmd(hModHdl, STOR_QryDiskSHMAbility_mt, MT_CMD_SET_ELEM, &stSHMAbility, NULL, NULL);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_MT_RegMtCmd dis failed.");
        return u32Ret;
    }

    stSHMInfo = MT_TITLE_CMD_ELEM_INIT(MT_CMD_ID_INVAL, "shminfo", "To get disk shm infomation.");
    u32Ret    = BP_MT_RegMtCmd(hModHdl, STOR_QryDiskSHMInfo_mt, MT_CMD_SET_ELEM, &stSHMInfo, NULL, NULL);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_MT_RegMtCmd dis failed.");
        return u32Ret;
    }

 stSHMInfo = MT_TITLE_CMD_ELEM_INIT(MT_CMD_ID_INVAL, "Allshminfo", "To get all disk shm infomation.");
    u32Ret    = BP_MT_RegMtCmd(hModHdl, STOR_QryAllDiskSHMInfo_mt, MT_CMD_SET_ELEM, &stSHMInfo, NULL, NULL);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_MT_RegMtCmd dis failed.");
        return u32Ret;
    }
    /* End added by liangzhiwei/lW5741 2019.3.4 of IVSD42944 for SHM合主线 */

    return u32Ret;
}
/* End added by yangbing/02874 2017-09-20 for IVSD35080 */

#endif
/*****************************************************************************
  函 数 名: __mod_reg
  函数描述: 模块注册入口
  输入参数: MODULE_CLS* pstModule
*****************************************************************************/
STATIC U32 __mod_reg(MODULE_CLS* pstModule)
{
    U32 u32Ret;
    EVENT_REG_PARAM_S stEventReg; /* Modified by sunxiaojis01884, 2016/4/18 of IVSD26635 消除Lint告警 */
    /* Begin Added by huanglingfeng/h06787, 2019.12.13 for 易用性八期 */
    BP_TMR_SETTING_S        stTimerMinInfo;
    BP_TMR_SETTING_S        stTimerDayInfo;
    /* End Added by huanglingfeng/h06787, 2019.12.13 for 易用性八期 */
    
    u32Ret = BP_ModInit(&pstModule->stRegParam, &pstModule->hModHdl);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_ModInit fail.");
        return u32Ret;
    }

    u32Ret = BP_GetModuleID(pstModule->hModHdl, MOD_CORE_STOR, &pstModule->u32ModuleID);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_GetModuleID fail.");
        return u32Ret;
    }

    u32Ret = BP_RegMsgProc(pstModule->hModHdl, VmpMsgProc, pstModule);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_RegMsgProc fail.");
        return u32Ret;
    }

    /* Begin Modified by zhengguoqiang/z03968 2018-3-14, of IVSD37813 for 磁盘上线无操作日志记录 */
    /* 向驱动注册磁盘上线事件 */
    stEventReg.enEvTypeMajor        = EVENT_TYPE_MAJOR_PERI_WARN;
    stEventReg.u32EvTypeMinorSets   = (U32)EV_PERI_WARN_DISK_ONLINE | (U32)EV_PERI_WARN_DISK_HM;
    stEventReg.pfnEventProc         = STOR_EventDisk;
    stEventReg.pParam               = NULL;
    u32Ret = BP_RegEvent(pstModule->hModHdl, &stEventReg);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_RegEvent fail.");
        return u32Ret;
    }
    /* End Modified by zhengguoqiang/z03968 2018-3-14, of IVSD37813 for 磁盘上线无操作日志记录 */

    /* 存储模块的初始化函数 */
    /* Modified by c00524 2014/11/26 for IVSD14386，存储流切换 */
    u32Ret = STOR_Init(pstModule->hModHdl, pstModule->u32ModuleID);
    if(BP_E_SUCCEED != u32Ret)
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "STOR_Init failed.");
        return u32Ret;
    }

    /* 设备删除 */
    BP_memzero(&stEventReg, sizeof(EVENT_REG_PARAM_S)); /* Modified by sunxiaojis01884, 2016/4/18 of IVSD26635 消除Lint告警 */

    stEventReg.enEvTypeMajor        = EVENT_TYPE_MAJOR_SYS;
    stEventReg.u32EvTypeMinorSets   = EV_SYS_DEV_DELETE;
    stEventReg.pfnEventProc         = STOR_EventDelIPC;
    stEventReg.pParam               = NULL;
    u32Ret = BP_RegEvent(pstModule->hModHdl, &stEventReg);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_RegEvent fail.");
        return u32Ret;
    }

    /* Begin:Added by hechengcheng 00275,  2015-01-23 of IVSD16313 */
    /* 设备删除 */
    stEventReg.enEvTypeMajor        = EVENT_TYPE_MAJOR_MEDIA;
    stEventReg.u32EvTypeMinorSets   = (U32)EV_MEDIA_SR_NORMAL | (U32)EV_MEDIA_SR_ABNORMAL;    /* Modified by sunxiaojis01884, 2016/4/18 of IVSD26635 消除Lint告警 */
    stEventReg.pfnEventProc         = STOR_ProcUBSSysEvent;/* Modified by 张强, 2015-6-12 of IVSD19576，主线Pclint消除 */
    stEventReg.pParam               = NULL;
    u32Ret = BP_RegEvent(pstModule->hModHdl, &stEventReg);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "BP_RegEvent fail.");
        return u32Ret;
    }
    /* End:Added by hechengcheng 00275,  2015-01-23 of IVSD16313 */

    /* Begin added by huanglingfeng 06787 2019-9-30 for 存储容错及提示问题优化特性 */
    #ifdef CONFIG_CORE_MODULE_RAID
    stEventReg.enEvTypeMajor = EVENT_TYPE_MAJOR_MD_STAT;
    stEventReg.u32EvTypeMinorSets = (U32)EV_MD_STAT_DEFAULT;
    stEventReg.pfnEventProc = STOR_RAID_ProcRAIDEvent;
    stEventReg.pParam = (VOID *)pstModule;

    u32Ret = BP_RegEvent(pstModule->hModHdl, &stEventReg);
    if (BP_IS_ERR(u32Ret))
    {
        return u32Ret;
    }
    #endif
    /* End added by huanglingfeng 06787 2019-9-30 for 存储容错及提示问题优化特性 */

#ifdef COMPILE_MT
    u32Ret = __mod_reg_mt(pstModule->hModHdl);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "__mod_reg_mt fail.");
        return u32Ret;
    }
#endif

    /* Begin Added by huanglingfeng/h06787, 2019.12.13 for 易用性八期 */
    /* 注册周期定时器，周期为10分钟 */
    BP_memzero(&stTimerMinInfo, sizeof(BP_TMR_SETTING_S));

    stTimerMinInfo.u32TimerInterval = 1000 * 60 * 10;
    stTimerMinInfo.enTMRType       = TMR_TYPE_CYCLE;
    stTimerMinInfo.pfnTimerProcCb  = STOR_QryRemainTimeBy10min;
    stTimerMinInfo.pParam          = NULL;

    u32Ret = BP_TMR_RegTimerProc(pstModule->hModHdl, &stTimerMinInfo);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "Failed to reg timer");
        return u32Ret;
    }
    BP_memzero(&stTimerDayInfo, sizeof(BP_TMR_SETTING_S));

    stTimerDayInfo.u32TimerInterval = 1000 * 60 * 60 * 24;
    stTimerDayInfo.enTMRType       = TMR_TYPE_CYCLE;
    stTimerDayInfo.pfnTimerProcCb  = STOR_QryRemainTimeByDay;
    stTimerDayInfo.pParam          = (VOID*)&stTimerMinInfo.ulTimerId;

    u32Ret = BP_TMR_RegTimerProc(pstModule->hModHdl, &stTimerDayInfo);
    if (BP_IS_ERR(u32Ret))
    {
        UW_CORE_LOG(LOG_RUNNING_LEVEL_ERR, u32Ret, "Failed to reg timer");
        return u32Ret;
    }
    /* End Added by huanglingfeng/h06787, 2019.12.13 for 易用性八期 */
    
    return u32Ret;
}

/*****************************************************************************
  函 数 名: __mod_init
  函数描述: 存储模块初始化函数
  输入参数: MODULE_CLS* pstModule
            CHAR *pcModuleName
*****************************************************************************/
STATIC U32 __mod_init(MODULE_CLS* pstModule, CHAR *pcModuleName)
{
    /* 存储模块初始化 */
    MODULE_STOR_CLS *pstModuleStor = (MODULE_STOR_CLS *)pstModule;

    pstModuleStor->stBase.ifOpt.mod_reg = __mod_reg;
    BP_strncpy(pstModuleStor->stBase.stRegParam.szModName, pcModuleName,
               sizeof(pstModuleStor->stBase.stRegParam.szModName));

    pstModuleStor->stBase.stRegParam.u32ThrNum = 1;

    pstModuleStor->stBase.stRegParam.u32RegOpt = MOD_REG_ALL;

    /* Begin added by huanglingfeng/h06787 2019.9.9 of 存储容错及提示问题优化特性 */
    gpstModuleStor = pstModuleStor;
    /* End added by huanglingfeng/h06787 2019.9.9 of 存储容错及提示问题优化特性 */

    return BP_E_SUCCEED;
}



/*****************************************************************************
  函 数 名: __mod_recv
  函数描述: 存储模块消息接收函数
  输入参数: MODULE_CLS* pstModule
            VMP_MSG_S *pstVmpMsg
*****************************************************************************/
STATIC VMP_MSG_CLS* __mod_recv(MODULE_CLS* pstModule, VMP_MSG_S *pstVmpMsg)
{
    VMP_MSG_CLS *pstMsg = NULL; /* Modified by haoxueliang02253, 2016-01-15 of IVSD24409 缓存补录pclint消除 */

    switch (pstVmpMsg->stMsgHdr.u16Command)
    {
        /* 流参数配置 */
        case VMP_MSG_SET_STREAM_INFO :
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetStreamInfoMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                               STOR_ProcSetStreamInfo);
            break;
        }
        /* 存储启停消息  */
        case VMP_MSG_RECORD:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateRecordCtrlMsg(pstModule->u32ModuleID,
                                                            (CHAR *) pstVmpMsg, STOR_ProcAlarmStor);
            break;
        }
        /* Begin Added by liujie/03326 2016-09-14 for 告警联动优化特性 */
        /* 打印标签消息 */
        case VMP_MSG_EVENT_TAG_INNER:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateEventTagMsg(pstModule->u32ModuleID,
                                                               (CHAR *) pstVmpMsg, STOR_ProcEventTag);
            break;
        }
        /* End Added by liujie/03326 2016-09-14 for 告警联动优化特性 */

        /* 存储计划消息 */
        case VMP_MSG_PLAN_REPORT_STORE_INNER:
        {
            /* Modified by j01376 2016/1/8 for IVSD23715 */
            pstMsg = (VMP_MSG_CLS *)VMP_CreatePlanRecordCtrlReqMsg(pstModule->u32ModuleID,
                                                            (CHAR *) pstVmpMsg, STOR_ProcStorSchedule);
            break;
        }
        /* 录像高级配置参数:警前警后+ 是否冗余存储*/
        case VMP_MSG_RECORD_ADVANCED_INNER:
        {
            /* Begin Modified by yangbing/02874 2015-11-17 for  盘组管理特性*/
            pstMsg = (VMP_MSG_CLS *)VMP_CreateRecordAdvancedMsg(pstModule->u32ModuleID,
                                                                (CHAR *) pstVmpMsg, STOR_ProcRecordAdvanced);
            /* End Modified by yangbing/02874 2015-11-17 for  盘组管理特性*/
            break;
        }
        /* 查询录像状态 */
        case VMP_MSG_QUERY_RECORD_STATUS:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryRecordStatusMsg(pstModule->u32ModuleID,
                                                                (CHAR *) pstVmpMsg, STOR_ProcQueryRecordStatus);
            break;
        }

        /* 磁盘初始化 */
        case VMP_MSG_INIT_DISK:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateInitDiskMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                          STOR_ProcInitDisk);
            break;
        }

        /* 设置磁盘属性 */
        case VMP_MSG_SET_DISK_PROPERTY:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetDiskPropertyMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                 STOR_ProcSetDiskProperty);
            break;
        }
        /* 磁盘信息列表 */
        case VMP_MSG_QUERY_DISK_LIST:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskListMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                             STOR_ProcQueryDiskList);
            break;
        }

        /* BEGIN: Added by c00524 2014/11/7 for IVSD14386，存储流切换 */
        case VMP_MSG_SET_STOR_TYPE_INNER:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetStorTypeInnerMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                  STOR_ProcSetStorTypeMsg);

            break;
        }
        /* END: Added by c00524 2014/11/7 for IVSD14386，存储流切换 */
        /* Begin added by p01365, 2015-02-07 of IVSD17031 */
        case VMP_MSG_QRY_DISK_SMART_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskSmartInfoMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                  STOR_ProcQryDiskSmartInfo);

            break;
        }

        case VMP_MSG_QUERY_VOD_STATUS:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryVodStatusMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                              STOR_ProcQryVodStatus);

            break;
        }
        /* End added by p01365, 2015-02-07 of IVSD17031 */
        /* Begin Added by sunxiaojis01884, 2015/4/14 of 新平台上下行国标 */
        case VMP_MSG_QRY_DEV_STATUS:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDevStatusMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                              STOR_ProcDevStatus);
            break;
        }
        /* End Added by sunxiaojis01884, 2015/4/14 of 新平台上下行国标 */

        /* Begin added by haoxueliang/02253, 2015-05-21 of 空间独享特性 */
        case VMP_MSG_GET_CHL_QUOTA_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateGetChlQuotaMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                            STOR_ProcGetChlQuotaInfo);

            break;
        }

        case VMP_MSG_SET_CHL_QUOTA_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetChlQuotaMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                            STOR_ProcSetChlQuotaInfo);

            break;
        }
        /* End added by haoxueliang/02253, 2015-05-21 of 空间独享特性 */
        /* Begin add by wuweiping/01403, 2015-06-08 of 空间独享特性 */
        case VMP_MSG_GET_ALL_CHL_QUOTA_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateGetAllChlQuotaMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                            STOR_ProcGetAllChlQuotaInfo);
            break;
        }
        /* End add by wuweiping/01403, 2015-06-08 of 空间独享特性 */
        /* Begin add by haoxueliang/02253, 2015-06-29 of 空间独享特性 */
        case VMP_MSG_ADD_IPC_INNER:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateIpcAddInnerMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                            STOR_ProcAddIpcMsg);

            break;
        }
        /* End add by haoxueliang/02253, 2015-06-29 of 空间独享特性 */
        /* Begin add by haoxueliang/02253, 2015-07-04 of 存储满即停特性 */
        case VMP_MSG_QRY_FULL_STRATEGY_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryFullStgyMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                            STOR_ProcQryFullStgy);

            break;
        }

        case VMP_MSG_SET_FULL_STRATEGY_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetFullStgyMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                            STOR_ProcSetFullStgy);

            break;
        }
        /* End add by haoxueliang/02253, 2015-07-04 of 存储满即停特性 */
        /* Begin added by sunxiaoji 01884 2015-8-18 for RAID特性 */
        case VMP_MSG_QRY_HD_DISK_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryPhyDiskInfoMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                STOR_ProcQryHDDiskInfo);
            break;
        }
        /* End added by sunxiaoji 01884 2015-8-18 for RAID特性 */
        /* Begin added by zhuhongyan 00342 2015-5-21 for RAID特性 */
        #ifdef CONFIG_CORE_MODULE_RAID
        case VMP_MSG_QRY_PHY_DISK_LIST:            /* 查询物理磁盘列表 */
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryPhyDiskListMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                STOR_RAID_ProcQryPhyDiskList);
            break;
        }
        case VMP_MSG_CFG_HOTSPARE_DISK:            /* 配置热备盘 */
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateCfgHotspareDiskMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                 STOR_RAID_ProcCfgHotspareDisk);
            break;
        }
        case VMP_MSG_MANU_CREATE_ARRAY:             /* 手动创建阵列 */
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateManuCreateArrayMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                 STOR_RAID_ProcManuCreateArray);
            break;
        }
        case VMP_MSG_ONEKEY_CREATE_ARRAY:           /* 一键创建阵列 */
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateOneKeyCreateArrayMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                   STOR_RAID_ProcOneKeyCreateArray);
            break;
        }
        case VMP_MSG_QUERY_ARRAY_LIST:              /* 查询阵列列表 */
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryArrayListMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                              STOR_RAID_ProcQryArrayList);
            break;
        }
        case VMP_MSG_REBUILD_ARRAY:                 /* 重键阵列 */
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateRebuildArrayMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                              STOR_RAID_ProcRebuildArray);
            break;
        }
        case VMP_MSG_DEL_ARRAY:                     /* 删除阵列 */
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateDelArrayMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                          STOR_RAID_ProcDelArray);
            break;
        }
        case VMP_MSG_QRY_RAID_INFO:                 /* 查询RAID状态 */
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryRAIDInfoMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                             STOR_RAID_ProcQryRAIDInfo);
            break;
        }
        case VMP_MSG_CONFIG_RAID_INFO:              /*  配置RAID状态*/
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateCfgRAIDInfoMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                             STOR_RAID_ProcCfgRAIDInfo);
            break;
        }

        /* Begin added by wanglixin/w6226 2018-10-12 of 苏州监狱查询阵列整改特性，根据磁盘类型查询磁盘信息 */
        case VMP_MSG_QRY_DISK_LIST_BY_TYPE:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskListByTypeMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                   STOR_RAID_ProcQryDiskListByType);
            break;
        }
        /* End added by wanglixin/w6226 2018-10-12 of 苏州监狱查询阵列整改特性，根据磁盘类型查询磁盘信息 */

        #endif
        /* End added by zhuhongyan 00342 2015-5-21 for RAID特性 */
        /* Begin Added by haoxueliang02253, 2015-08-24 of 硬盘坏道检测特性 */
        case VMP_MSG_SET_DISK_SMART_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetDiskSmartMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                             STOR_ProcSetDiskSmartInfo);

            break;
        }

        case VMP_MSG_QRY_SMART_FAIL_ENABLE:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQrySmartFailEnableMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                   STOR_ProcQrySmartChkEnable);

            break;
        }

        case VMP_MSG_SET_SMART_FAIL_ENABLE:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetSmartFailEnableMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                   STOR_ProcSetSmartChkEnable);

            break;
        }

        case VMP_MSG_QRY_DISK_BAD_SECTOR_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskBadSectorMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                 STOR_ProcQryDiskBadSector);

            break;
        }

        case VMP_MSG_SET_DISK_BAD_SECTOR_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetDiskBadSectorMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                 STOR_ProcSetDiskBadSector);

            break;
        }

        case VMP_MSG_QRY_BAD_SECTOR_DISK_NUM:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryBadSectDiskNumMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                 STOR_ProcQryBadSectDiskNum);

            break;
        }
        /* End Added by haoxueliang02253, 2015-08-24 of 硬盘坏道检测特性 */
        /* Begin Added by yangbing/02874 2015-11-17 for  盘组管理特性*/
        case VMP_MSG_QRY_DISKGROUP_STATUS:                    /* 查询盘组状态*/
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskGrpStatusMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                  STOR_ProcQryDiskGrpStatus);
            break;
        }
        case VMP_MSG_CONFIG_DISKGROUP_STATUS:                 /* 配置盘组状态*/
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetDiskGrpStatusMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                  STOR_ProcSetDiskGrpStatus);
            break;
        }
        case VMP_MSG_GET_INUSE_DISKGROUP:                     /* 查询可用 (已配有磁盘/阵列)磁盘组*/
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateGetInuseDiskGrpMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                  STOR_ProcGetInuseDiskGrp);
            break;
        }
        /* End Added by yangbing/02874 2015-11-17 for  盘组管理特性*/

        /* Begin Modified by yangbing/02874 2016-6-3 for IVSD28780 NVR支持NAS存储设备 */
        /* Begin Added by haoxueliang02253, 2015-11-09 of 缓存补录 */
        /* 缓存补录存储控制 */
        case VMP_MSG_ANR_STOR_CTRL_INNER:
        case VMP_MSG_QRY_ALARM_BEGIN_TIME_INNER:
        {
            if (!BP_IS_NULL(gastStorModFuncOpt[STOR_ANR_MODULE].pfnVmpProc))
            {
                pstMsg = (VMP_MSG_CLS *)gastStorModFuncOpt[STOR_ANR_MODULE].pfnVmpProc(pstModule->u32ModuleID, pstVmpMsg);
            }

            break;
        }
        /* End Added by haoxueliang02253, 2015-11-09 of 缓存补录 */
        /* End Modified by yangbing/02874 2016-6-3 for IVSD28780 NVR支持NAS存储设备 */
        /* Begin Added by yangbing/02874 2016-6-3 for IVSD28780 NVR支持NAS存储设备 */
        /* Added by zhengguoqiang/w2874 2017-02-09 for IVSD31894 ESATA特性 */
        case VMP_MSG_SET_ESATA_DISK:
        case VMP_MSG_SEARCH_EXTDISK:
        case VMP_MSG_ADD_EXTDISK:
        case VMP_MSG_DEL_EXTDISK:
        {
            if (!BP_IS_NULL(gastStorModFuncOpt[STOR_EXTDISK_MODULE].pfnVmpProc))
            {
                pstMsg = (VMP_MSG_CLS *)gastStorModFuncOpt[STOR_EXTDISK_MODULE].pfnVmpProc(pstModule->u32ModuleID, pstVmpMsg);
            }

            break;
        }
        /* End Added by yangbing/02874 2016-6-3 for IVSD28780 NVR支持NAS存储设备 */
        /* Begin added by yangbing/02874 2017-06-01 for 人脸20G文件系统 */
        case VMP_MSG_GET_DISK_MODE:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateGetDiskModeClsMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                STOR_ProcGetDiskMode);
            break;
        }
        case VMP_MSG_SET_DISK_MODE:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetDiskModeClsMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                STOR_ProcSetDiskMode);
            break;
        }
        /* End added by yangbing/02874 2017-06-01 for 人脸20G文件系统 */
  /* Begin Added by qulei/W4082 2017-7-11 for 硬盘休眠定制特性 */
        case VMP_MSG_GET_DISK_SLEEP_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateGetDiskSleepInfoClsMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                STOR_ProcGetDiskSleepInfo);
            break;
        }
        case VMP_MSG_SET_DISK_SLEEP_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSetDiskSleepInfoClsMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                STOR_ProcSetDiskSleepInfo);
            break;
        }
        /* End Added by qulei/W4082 2017-7-11 for 硬盘休眠定制特性 */
        /* Begin added by liangzhiwei/lW5741 2019.3.4 of IVSD42944 for SHM合主线 */
        case VMP_MSG_QRY_DISK_SHM_ABILITY:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskSHMAbilityMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                STOR_ProcQryDiskSHMAblity);
            break;
        }
        case VMP_MSG_QRY_DISK_SHM_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskSHMInfoMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                STOR_ProcQryDiskSHMInfo);
            break;
        }
        /* End added by liangzhiwei/lW5741 2019.3.4 of IVSD42944 for SHM合主线 */

        /* Begin added by huanglingfeng/h06787 2019.9.30 for 存储容错及提示问题优化特性 */
        case VMP_MSG_QRY_REC_SNAP_ALARM_INNER:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryStorRecSnapInnerMsg(pstModule->u32ModuleID, (CHAR *)pstVmpMsg,
                                                                STOR_ProcQryStorRecSnap);
            break;
        }
        /* End added by huanglingfeng/h06787 2019.9.30 for 存储容错及提示问题优化特性 */

        /* Begin added by huanglingfeng/06787 2019-08-05 for 易用性七期 */
        case VMP_MSG_QRY_DISK_KEY_INFO:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskKeyInfoMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                 STOR_ProcQryDiskKeyInfo);
            break;
        }
        /* End added by huanglingfeng/06787 2019-08-05 for 易用性七期 */
        /* Begin Added by zhengguoqiang/z03968, 20200303 of IVSD51671 for ubs底图兼容性升级 */
        case VMP_MSG_GET_SMTB_UPGRADE_ABILITY:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateGetSmtbUpgradeAbilityClsMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                 STOR_ProcGetSmtbAbility);
            break;
        }
        case VMP_MSG_SMTB_CAP_EXPANDS:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateSmtbCapExpandClsMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                  STOR_ProcSmtbCapExpand);
            break;  
        }
        /* End Added by zhengguoqiang/z03968, 20200303 of IVSD51671 for ubs底图兼容性升级 */
        /* Begin added by huanglingfeng/06787 2019-12-19 for 易用性八期 */
        
        case VMP_MSG_QRY_DISK_REAMIN_TIME:
        {
            pstMsg = (VMP_MSG_CLS *)VMP_CreateQryDiskRemainTimeInfoMsg(pstModule->u32ModuleID, (CHAR *) pstVmpMsg,
                                                                 STOR_ProcQryDiskRemainTimeInfo);
            break;
        }
        /* End added by huanglingfeng/06787 2019-12-19 for 易用性八期 */
        
        default:
        {
            return NULL;
        }
    }

    return pstMsg;
}

MODULE_STOR_CLS* Module_CreateStor(CHAR *pcModuleName)
{
    /* Modified by z01877 2015/3/27 for IVSD18087，代码Review修改 */
    Module_Create(MODULE_STOR_CLS)
}

/* Added by zhengguoqiang/z03968, 2018-3-12 of IVSD37963 for 盘组裁剪 */
/*****************************************************************************
  函 数 名: Module_Stor_Reg
  生成日期: 2018/3/12
  作    者: zhengguoqiang/z03968
  函数描述: Stor模块是否裁剪相关
  输入参数: VOID
  输出参数: 无
    返回值: VOID
    注意点:
------------------------------------------------------------------------------
    修改历史
    日期        姓名             描述
  --------------------------------------------------------------------------

*****************************************************************************/
MOD_STOR_INIT VOID Module_Stor_Reg(VOID)
{
    U32 u32Ret = BP_E_SUCCEED;

    /* 盘组裁剪 */
    if (CFG_DISK_NUM > 1)
    {
        u32Ret = BP_Ability_Set(ABILITY_DISK_GRP_CMD);
        if (BP_IS_ERR(u32Ret))
        {
           printf("Disk Grp ability set fail,u32Ret = %u.\n", u32Ret);
        }
    }

    /* GPT分区裁剪 */
    u32Ret = DEV_GET_SUPORT_GPT();
    if ( 0 < u32Ret )
    {
        u32Ret = BP_Ability_Set(ABILITY_GPT_CMD);
        if (BP_IS_ERR(u32Ret))
        {
            printf("GPT set ability failed.u32Ret = %u\n", u32Ret);
        }
    }

    return;
}
/* End Added by zhengguoqiang/z03968, 2018-3-12 of IVSD37963 for 盘组裁剪 */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */ 


