// 用户程序
// 更新：2015-12
//###########################################################################
//
// 文件:	USERS_Protects.c
//
// 标题:	系统保护函数
//
// 描述:	包含系统切换模式选择函数和系统保护子函数
//				
//########################################################################### 
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

extern struct AD_BUFS                   DataBuf;
extern union  FLAG_GPIOIN   	 		FlagGpioIn;
extern union  FLAG_SYSTEM_INITERR 		FlagSysInitErr;
extern union  FLAG_SYSTEM_RUNERR 		FlagSysRunErr;
extern union  FLAG_SYSTEM_ALARM			FlagSysAlarm;
extern union  FLAG_SYSTEM				FlagSystem;
extern union  STATE_SYSTEM				StateSystem;
extern struct COUNT_SYSTEM				CountSystem;
extern struct REGS_SYSTEM               RegSystem;
extern struct SPLL_REGS 				SpllRegOut;

/*---------------------------------------------------------------------
函数原型：void PhaseLackProtect(void)
函数名称：系统保护类型--缺相保护
函数功能：
入口参数：无
出口参数：无
作    者：
日    期：2018年07月
----------------------------------------------------------------------*/
void PhaseLackProtect(void)
{
/**************************** 输出缺相判断 ***************************/
//	if((RegSystem.OutVolRms > ParaTable.RunCtrlReg.uVolOutLPLow)
//	&& (RegSystem.OutVolRms < ParaTable.RunCtrlReg.uVolOutLPUp))
//	{
//		if(++CountSystem.DelayOutInLP >= ParaTable.RunCtrlReg.uVolOutLPDelay)
//		{
//			CountSystem.DelayOutInLP = ParaTable.RunCtrlReg.uVolOutLPDelay;
//			FlagSysAlarm.bit.OutPhaseLose = 1;
//		}
//	}
//	else
//	{
//		if(--CountSystem.DelayOutInLP <= 0)
//		{
//			CountSystem.DelayOutInLP = 0;
//			FlagSysAlarm.bit.OutPhaseLose = 0;
//		}
//	}
}

/*---------------------------------------------------------------------
函数原型：void InVolProtect(void)
函数名称：系统保护类型--输入电压保护(低压、高压保护)
函数功能：
入口参数：无
出口参数：无
作    者：
日    期：2015年12月
----------------------------------------------------------------------*/
void InVolProtect(void)
{
//	if(RegSystem.OutVolRms < ParaTable.RunCtrlReg.uOutVolLower)
//	{
//		if(++CountSystem.OutUrmsLow > ParaTable.RunCtrlReg.uOutVolLowDelay)
//		{
//			CountSystem.OutUrmsLow = ParaTable.RunCtrlReg.uOutVolLowDelay;
//			FlagSysAlarm.bit.OutVolLowAlarm = 1;
//		}
//	}
//	else if(RegSystem.OutVolRms > ParaTable.RunCtrlReg.uOutVolUpper)
//	{
//		if(++CountSystem.OutUrmsHigh > ParaTable.RunCtrlReg.uOutVolUpDelay)
//		{
//			CountSystem.OutUrmsHigh = ParaTable.RunCtrlReg.uOutVolUpDelay;
//			FlagSysAlarm.bit.OutVolHighAlarm = 1;
//		}
//	}
//	else if((RegSystem.OutVolRms >= ParaTable.RunCtrlReg.uOutVolLower + AC_VOL_RESUM5)
//	&& (RegSystem.OutVolRms <= ParaTable.RunCtrlReg.uOutVolUpper - AC_VOL_RESUM5))
//	{
//		CountSystem.OutUrmsLow 				= 0;
//		CountSystem.OutUrmsHigh 			= 0;
//		FlagSysAlarm.bit.OutVolLowAlarm 	= 0;
//		FlagSysAlarm.bit.OutVolHighAlarm 	= 0;
//	}
}

/*---------------------------------------------------------------------
函数原型：void InCurProtect(void)
函数名称：系统保护类型--输出过流保护
函数功能：
入口参数：无
出口参数：无
作    者：
日    期：2015年12月
----------------------------------------------------------------------*/
void InCurProtect(void)
{
//	if(RegSystem.NO2IRms > ParaTable.RunCtrlReg.uNO2CurAlarm)
//	{
//		if(++CountSystem.NO2CurHighAlarm > ParaTable.RunCtrlReg.uNO2CurAlarmDelay)
//		{
//			CountSystem.NO2CurHighAlarm = ParaTable.RunCtrlReg.uNO2CurAlarmDelay;
//			FlagSysAlarm.bit.NO2InCurHighAlarm = 1;
//		}
//		if(RegSystem.NO2IRms > ParaTable.RunCtrlReg.uNO2CurCut)
//		{
//			if(++CountSystem.NO2CurHighCut > ParaTable.RunCtrlReg.uNO2CurCutDelay)
//			{
//				CountSystem.NO2CurHighCut = ParaTable.RunCtrlReg.uNO2CurCutDelay;
//				FlagSysRunErr.bit.NO2InCurHighCut = 1;
//			}
//		}
//		else
//		{
//			CountSystem.NO2CurHighCut = 0;
//		}
//	}
//	else if((RegSystem.NO2IRms <= ParaTable.RunCtrlReg.uNO2CurAlarm - AC_CUR_RUSUM5))
//	{
//		FlagSysAlarm.bit.NO2InCurHighAlarm 	= 0;
//		FlagSysRunErr.bit.NO2InCurHighCut 	= 0;
//		CountSystem.NO2CurHighAlarm 		= 0;
//		CountSystem.NO2CurHighCut 			= 0;
//	}
}

/*---------------------------------------------------------------------
函数原型：void TempProtect(void)
函数名称：系统保护类型--温度保护
函数功能：
入口参数：无
出口参数：无
作    者：
日    期：2015年12月
----------------------------------------------------------------------*/
void TempProtect(void)
{
//    Uint16 TempMax;
//
//    // 温度取最大值
//    if (ParaTable.Timer1Reg.uModATemp >= ParaTable.Timer1Reg.uModBTemp)
//    {
//        TempMax = ParaTable.Timer1Reg.uModATemp;
//    }
//    else
//    {
//        TempMax = ParaTable.Timer1Reg.uModBTemp;
//    }
//
//    if (ParaTable.Timer1Reg.uModCTemp >= TempMax)
//    {
//        TempMax = ParaTable.Timer1Reg.uModCTemp;
//    }
//
//    // 根据温度开启风扇
//    if (TempMax > ParaTable.RunCtrlReg.uFanOpenTemp)
//    {
//
//    }
//    else if (TempMax <= (ParaTable.RunCtrlReg.uFanOpenTemp - TEMP_RESUM5))
//    {
//
//    }
//
//    // 过温保护
//    if(TempMax > ParaTable.RunCtrlReg.uTempAlarm)
//    {
//        if(++CountSystem.DelayTempAlarm > 1000)     // 延迟3S报警
//        {
//            CountSystem.DelayTempAlarm = 1000;
//            FlagSysAlarm.bit.OverTempAlarm = 1;
//        }
//    }
//    else if(TempMax > ParaTable.RunCtrlReg.uTempCut)
//    {
//        if(++CountSystem.DelayTempCut > 1000)       // 延迟3S保护
//        {
//            CountSystem.DelayTempCut = 1000;
//            FlagSysRunErr.bit.OverTempCut = 1;
//        }
//    }
//    else if (TempMax < ParaTable.RunCtrlReg.uTempCut - TEMP_RESUM5)
//    {
//        CountSystem.DelayTempCut      = 0;
//        FlagSysRunErr.bit.OverTempCut = 0;
//    }
//    else if (TempMax < ParaTable.RunCtrlReg.uTempAlarm - TEMP_RESUM5)
//    {
//        CountSystem.DelayTempAlarm     = 0;
//        FlagSysAlarm.bit.OverTempAlarm = 0;
//    }
}

/*---------------------------------------------------------------------
函数原型：void PDPClearFunc(Uint16 ClearTime)
函数名称：
函数功能：清除PDP故障
入口参数：ClearTime 延迟清除故障时间 @3ms
出口参数：PDPFlag 故障清除标记： 0-清除  1-未清除
作    者：
日    期：2017年05月03日
----------------------------------------------------------------------*/
void PDPClearFunc(Uint16 ClearTime)
{
	static Uint16 PDPCountTemp = 0;
	Uint16 PDPErrTemp;

	if (++PDPCountTemp >= ClearTime)
	{
		ClrCPLDSTS();           				//清除硬件故障；
		PDPCountTemp = 0;
		PDPErrTemp = ReadCPLDSTS();          	//读取Error_Status；
		if((PDPErrTemp & 0xff) == 0xff)
		{
			FlagSysRunErr.bit.FlagPDP = 0;
			PieCtrlRegs.PIEIER2.bit.INTx1 = 1;
		}
	}
}

