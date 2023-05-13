/* ���������������������������������������������������������������������������
	File:			TICK.C

	Notes:			Game Frame Clock stuff
	
	Author:			G Robert Liddon @ Croydon
	Created:		Monday 2nd October 1995

	Copyright (C) 1994/1995 G Robert Liddon
	All rights reserved. 
  ��������������������������������������������������������������������������� */


/* ���������������������������������������������������������������������������
	Glib Includes
	������������� */

/* ���������������������������������������������������������������������������
	Includes
	�������� */
#include "tick.h"

/* ���������������������������������������������������������������������������
	Vars
	���� */
U32 GazTick;

/* ���������������������������������������������������������������������������
	Intialise the module
	�������������������� */
void TICK_InitModule(void)
{
	TICK_Set(0);
}	


/* ���������������������������������������������������������������������������
	Set the current tick value
	�������������������������� */
void TICK_Set(U32 Val)
{
	GazTick=Val;
}	

/* ���������������������������������������������������������������������������
	Set the current tick value
	�������������������������� */
U32 TICK_Get(void)
{
	return(GazTick);
}	


/* ���������������������������������������������������������������������������
	Update Tick
	����������� */
void TICK_Update(void)
{
	GazTick++;
}	

/* ���������������������������������������������������������������������������
	Get the frames passed since last tick
	������������������������������������� */
U32 TICK_GetAge(U32 OldTick)
{
	return(TICK_Get()-OldTick);
}	

const char * TICK_GetDateString(void)
{
	return(__DATE__);
}	

const char * TICK_GetTimeString(void)
{
	return(__TIME__);
}	


/* ���������������������������������������������������������������������������
	ends */
