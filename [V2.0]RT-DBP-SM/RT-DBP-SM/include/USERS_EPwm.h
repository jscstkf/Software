#ifndef  _USERS_EPWM_H_
#define  _USERS_EPWM_H_
#include "DSP2833x_Device.h"     
#include "DSP2833x_Examples.h"

#define EPWM_CH1		1
#define EPWM_CH2		2
#define EPWM_CH3		3
#define EPWM_CH4		4
#define EPWM_CH5		5
#define EPWM_CH6		6
#define EPWM_CH123		7
#define EPWM_CH46		8
#define EPWM_CH56		9
#define EPWM_ALL		10

/*---------------------------------------------------------------------
函数原型：void InitEPWM(void)
函数名称：初始化EPWM模块
函数功能：
入口参数：无                    
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
void InitEPWM(void);

/*---------------------------------------------------------------------
函数原型：void EnableTZ(void)
函数名称：使能TZ1
函数功能：
入口参数：无                    
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
void EnableTZ(void);

/*---------------------------------------------------------------------
函数原型：void Disable_TZ(void)
函数名称：禁止TZ1
函数功能：
入口参数：无                    
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
void Disable_TZ(void);

/*---------------------------------------------------------------------
函数原型：void EnablePWM(char channel)
函数名称：打开PWM
函数功能：
入口参数：channel---通道号	EPWM_CH1	通道1
						......
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
void EnablePWM(char channel);

/*---------------------------------------------------------------------
函数原型：void DisablePWM(char channel)
函数名称：设置输出为高电平：就是禁止PWM输出；
函数功能：
入口参数：channel---通道号	EPWM_CH1	通道1
						......
出口参数：无
作    者：
日    期：
----------------------------------------------------------------------*/
void DisablePWM(char channel);

#endif

