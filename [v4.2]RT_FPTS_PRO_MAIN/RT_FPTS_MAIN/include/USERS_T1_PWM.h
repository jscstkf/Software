#ifndef _USERS_T1_PWM_H_
#define _USERS_T1_PWM_H_

#include "DSP2833x_Device.h"     
#include "DSP2833x_Examples.h"

/*---------------------------------------------------------------------
函数原型：interrupt void ePWM1ISR(void)
函数名称：EPWM1中断
函数功能：
入口参数：无
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
interrupt void ePWM1ISR(void);

/*---------------------------------------------------------------------
函数原型：interrupt void TZ1_ISR(void)
函数名称：TZ1中断
函数功能：
入口参数：无
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
interrupt void TZ1_ISR(void);

/*---------------------------------------------------------------------
函数原型：void InitT1Var(void)
函数名称：T1中断中变量初始化
函数功能：
入口参数：无
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
void InitT1Var(void);

/*---------------------------------------------------------------------
函数原型：void ReadT1VarFromPara(void)
函数名称：从参数表中读取数据
函数功能：
入口参数：无
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
void ReadT1VarFromPara(void);

#endif
