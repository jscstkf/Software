/*****************ͷ�ļ�********************/

#include "DSP2833x_Device.h"     
#include "DSP2833x_Examples.h"

extern struct AD_BUFS                   DataInst;
extern struct AD_BUFS                   DataZero;
extern struct AD_BUFS                   DataBuf;
extern struct AD_BUFS                   DataFactor;
extern struct AD_BUFS                   DataNormal;
extern struct AD_BUFS                   DataMax;

extern union  FLAG_GPIOIN   	 		FlagGpioIn;

extern union  FLAG_SYSTEM_INITERR 		FlagSysInitErr;
extern union  FLAG_SYSTEM_RUNERR 		FlagSysRunErr;
extern union  FLAG_SYSTEM				FlagSystem;
extern union  FLAG_SYSTEM_ALARM			FlagSysAlarm;
extern union  FLAG_SYSTEM_PDPERR		FlagSysPDPErr;

extern struct COUNT_SYSTEM				CountSystem;
extern struct REGS_SYSTEM               RegSystem;
extern enum   SYSTEM_STATE 				SystemState;

extern struct INSTANT_POWER 			PowerInst;
extern struct SVPWM_REGS 				SvpwmReg;
extern struct VVVF_REGS 				VVVFReg;

extern int16  SinTab[1024];
extern int16 *EmDataAddrArray[8];

void 	SaveT1VarToPara(void);								// ���²�����
Uint16  MotorSoftStart(Uint16 channel, struct SPLL_REGS *spllreg, Uint16 init_alpha, int16 step_time);

void InitT1Var(void)
{
    // SVPWM�Ĵ�����ʼ��ֵ
	SvpwmReg.EPwm1TBPRD = EPwm1Regs.TBPRD;
	SvpwmReg.EPwm2TBPRD = EPwm2Regs.TBPRD;
	SvpwmReg.EPwm3TBPRD = EPwm3Regs.TBPRD;

	// ������ʼĴ�����ʼ��ֵ
    PowerInst.Period	= 128;

    // VVVF�Ĵ�����ʼ��ֵ
    VVVFReg.FreNom			= ParaTable.PowerReg.uOutputFre;
    VVVFReg.VolNom			= ParaTable.PowerReg.uOutputVol;
    VVVFReg.AccelerationMax	= 100;
}

#pragma CODE_SECTION(ReadT1VarFromPara, "ramcode")

void  ReadT1VarFromPara(void)
{
	if(ParaTable.EmergencyReg.uEmDataChgEnable == 0x5555)
	{
	    FlagSystem.bit.EmDataChgFlag = 1;
	}
	else
	{
	    FlagSystem.bit.EmDataChgFlag = 0;
	}
}

/*---------------------------------------------------------------------
����ԭ�ͣ�interrupt void ePWM1ISR(void)
�������ƣ�epwm1�ж�
�������ܣ�
��ڲ�������
���ڲ�������
��    �ߣ�
��    �ڣ�
----------------------------------------------------------------------*/
#pragma CODE_SECTION(ePWM1ISR, "ramcode")

interrupt void ePWM1ISR(void)
{
	int16 i, temp;
    int16 *pDataBuf, *pDataInst, *pDataZero, *pDataFactor;

	DINT;
	EPwm1Regs.ETCLR.bit.INT = 1;					// �����ʱ��INT��ʶ
	PieCtrlRegs.PIEACK.all  = PIEACK_GROUP3;		// ���INT3Ӧ��
	CpuTimer2Regs.TIM.all	= CpuTimer2Regs.PRD.all;

	/**********************��Ŀ����*********************/

    // AD�������ݶ�ȡ������
    ADSampleOfDMA();
    ReadT1VarFromPara();

    // ԭʼ���ݱ��ۼ���
    pDataBuf  = (int16 *)&DataBuf;
    pDataInst = (int16 *)&DataInst;
    pDataZero = (int16 *)&DataZero;
    pDataFactor = (int16 *)&DataFactor;
    for (i = 0; i < 10; i++, pDataBuf++, pDataInst++, pDataZero++, pDataFactor++)
    {
        temp = (int32)(*pDataInst - *pDataZero) * (*pDataFactor) >> 9;      // Q11 * Q10 >> 9 = Q12
        *pDataBuf = ((int32)*pDataBuf * 3 + temp) >> 2;
    }

    SaveT1VarToPara();
    T1VarSave();
    T1EmergencySave(FlagSysRunErr.bit.FlagPDP);

    /*----------------------�㷨д��������-------------------------*/
// 1������V/F���ߡ�SVPWM����
    VVVFCal(&VVVFReg, RegSystem.VVVFVfSet, RegSystem.OutVolWeRef, RegSystem.SpeedRatio);

	RegSystem.OutVolWeReal = VVVFReg.WeReal;							// ��Ƶ�ʸ�ֵ
	RegSystem.OutVolThetaSum += RegSystem.OutVolWeReal;
	RegSystem.OutVolTheta = ((int32)RegSystem.OutVolThetaSum >> 8) & 0x03ff;
	if (RegSystem.OutVolTheta < 0)
	{
		RegSystem.OutVolTheta = RegSystem.OutVolTheta + 1024;
	}

	RegSystem.OutVolSina = SinTab[RegSystem.OutVolTheta];               	// sinֵ	Q12
	RegSystem.OutVolCosa = SinTab[(RegSystem.OutVolTheta + 256) & 0x03ff];

	svpwm(&SvpwmReg, VVVFReg.Uref, 0, RegSystem.OutVolSina, RegSystem.OutVolCosa);
	EPwm1Regs.CMPA.half.CMPA = SvpwmReg.T_CMPR1;
	EPwm2Regs.CMPA.half.CMPA = SvpwmReg.T_CMPR2;
	EPwm3Regs.CMPA.half.CMPA = SvpwmReg.T_CMPR3;

// 2������ÿ·ģ���¶�ֵ
//	RegSystem.TempARms = URmsCalc(DataBuf.TempA , &ModATempRegs, 128);
//	RegSystem.TempBRms = URmsCalc(DataBuf.TempB , &ModBTempRegs, 128);

	if (SystemState == SystemRun)	// �ж�ռ��̫��ʱ�䣬�����޷�����SCI�����жϣ���Ҫ�ڲ���ʱ���Ρ�
	{
		// 3����������й����޹�
		PowerCal(&PowerInst, RegSystem.OutVolTheta, DataBuf.Uab, DataBuf.Ubc, DataBuf.Ia, DataBuf.Ic);

		// 4����PWM����
		EnablePWM(EPWM_CH123);
		GPIOOutOfDSP(EN_DRIVER, 1);

		CountSystem.T1Cycle = (CpuTimer2Regs.PRD.all - CpuTimer2Regs.TIM.all) * 0.0066;			// us
		EINT;
	}
	else
	{
		DisablePWM(EPWM_ALL);
		GPIOOutOfDSP(EN_DRIVER, 0);

		VVVFReg.WeReal = 20;
	}

	/*************************END**********************/

	CountSystem.T1Cycle = (CpuTimer2Regs.PRD.all - CpuTimer2Regs.TIM.all) * 0.0066;			// us

	EINT;
}

/*---------------------------------------------------------------------
����ԭ�ͣ�interrupt void TZ1ISR(void)
�������ƣ�TZ1�ж�
�������ܣ�
��ڲ�������
���ڲ�������
��    �ߣ�
��    �ڣ�
----------------------------------------------------------------------*/
interrupt void TZ1ISR(void)
{
   	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

   	FlagSysRunErr.bit.FlagPDP = 1;
	DisablePWM(EPWM_ALL);              	// close all the pwm pulse;

	FlagSysPDPErr.all = (~ReadCPLDSTS()) & 0xff;

	EALLOW;
   	EPwm1Regs.TZCLR.all = 0x07;
    EPwm2Regs.TZCLR.all = 0x07;
    EPwm3Regs.TZCLR.all = 0x07;
    EPwm4Regs.TZCLR.all = 0x07;
    EPwm5Regs.TZCLR.all = 0x07;
    EPwm6Regs.TZCLR.all = 0x07;
	EDIS;

	// Enable PIE: Group 2 interrupt 1
	PieCtrlRegs.PIEIER2.bit.INTx1 = 0;
}

/*---------------------------------------------------------------------
����ԭ�ͣ�void SaveT1VarToPara(void)
�������ƣ�����PWM�ж�������������
�������ܣ�
��ڲ�����
���ڲ�������
��    �ߣ�
��    �ڣ�2015��12��
----------------------------------------------------------------------*/
#pragma CODE_SECTION(SaveT1VarToPara, "ramcode")

void SaveT1VarToPara(void)
{
	ParaTable.PWMReg.uInVol 	    = DataBuf.Udc1;
	ParaTable.PWMReg.uInCur 	    = DataBuf.Udc2;
	ParaTable.PWMReg.uBoost1Cur	    = 0;
	ParaTable.PWMReg.uBoost2Cur		= 0;
	ParaTable.PWMReg.uBoost3Cur		= 0;
	ParaTable.PWMReg.uOutUab		= DataBuf.Uab;
	ParaTable.PWMReg.uOutUbc      	= DataBuf.Ubc;
	ParaTable.PWMReg.uOutIAl      	= DataBuf.Ia;
	ParaTable.PWMReg.uOutIBl      	= 0;
	ParaTable.PWMReg.uOutICl 	    = DataBuf.Ic;

	ParaTable.PWMReg.uOutIAc 	    = DataBuf.Iu;
	ParaTable.PWMReg.uOutIBc 	    = 0;
	ParaTable.PWMReg.uOutICc	    = DataBuf.Iw;
	ParaTable.PWMReg.uOutUd		    = PowerInst.IinstReg.UsdFine;
	ParaTable.PWMReg.uOutUq		    = PowerInst.IinstReg.UsqFine;
	ParaTable.PWMReg.uOutTheta		= RegSystem.OutVolTheta;

	ParaTable.PWMReg.uOutInstActivePower 	= PowerInst.PowerInstP;
	ParaTable.PWMReg.uOutInstReactivePower 	= PowerInst.PowerInstQ;
	ParaTable.PWMReg.uOutAvgActivePower 	= PowerInst.PowerAvgP;
	ParaTable.PWMReg.uOutAvgReactivePower 	= PowerInst.PowerAvgQ;

	ParaTable.PWMReg.uModATemp 	    = 255;
	ParaTable.PWMReg.uModBTemp 	    = 222;
	ParaTable.PWMReg.uT1UseTime	    = CountSystem.T1Cycle;

    ParaTable.PWMReg.uActiveReg0    = VVVFReg.WeReal;
	ParaTable.PWMReg.uActiveReg1    = VVVFReg.Uref;
	ParaTable.PWMReg.uActiveReg2    = RegSystem.OutVolWeRef;
	ParaTable.PWMReg.uActiveReg3    = 0;
	ParaTable.PWMReg.uActiveReg4    = 0;
	ParaTable.PWMReg.uActiveReg5    = 0;
	ParaTable.PWMReg.uActiveReg6    = 0;
	ParaTable.PWMReg.uActiveReg7    = 0;
	ParaTable.PWMReg.uActiveReg8    = 0;
	ParaTable.PWMReg.uActiveReg9    = 0;

/*----------------------------------------------------------*
*                   ����Ϊ��Ҫ���ݵ��籣�棬�������޸�               *
*-----------------------------------------------------------*/
	ParaTable.EmergencyReg.uEmCountBlock = EmgcRamReg.CountBlock;
	ParaTable.EmergencyReg.uEmCountRam   = EmgcRamReg.CountRam;
	ParaTable.EmergencyReg.uEmData0Addr  = (int16)((int32)EmDataAddrArray[0] & 0x0000ffff);
	ParaTable.EmergencyReg.uEmData1Addr  = (int16)((int32)EmDataAddrArray[1] & 0x0000ffff);
	ParaTable.EmergencyReg.uEmData2Addr  = (int16)((int32)EmDataAddrArray[2] & 0x0000ffff);
	ParaTable.EmergencyReg.uEmData3Addr  = (int16)((int32)EmDataAddrArray[3] & 0x0000ffff);
	ParaTable.EmergencyReg.uEmData4Addr  = (int16)((int32)EmDataAddrArray[4] & 0x0000ffff);
	ParaTable.EmergencyReg.uEmData5Addr  = (int16)((int32)EmDataAddrArray[5] & 0x0000ffff);
	ParaTable.EmergencyReg.uEmData6Addr  = (int16)((int32)EmDataAddrArray[6] & 0x0000ffff);
	ParaTable.EmergencyReg.uEmData7Addr  = (int16)((int32)EmDataAddrArray[7] & 0x0000ffff);
	ParaTable.EmergencyReg.uEmDataChgFlag        = FlagSystem.bit.EmDataChgFlag;
	ParaTable.EmergencyReg.uEmDataSaveFinishFlag = EmgcRamReg.FlagDataSaveFinish;
	ParaTable.EmergencyReg.uEmDataFlashWriteOK   = FlagSystem.bit.EmDataFlashWriteOK;
}