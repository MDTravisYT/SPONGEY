/* ���������������������������������������������������������������������������
	File:		GUTILS.C

	Notes:		Machine indepnant util code

	Author:		G Robert Liddon @ 73b

	Project:	NBA Hang Time PSX

	Copyright (C) 1996 DCI Ltd All rights reserved. 
  ���������������������������������������������������������������������������� */


/* ���������������������������������������������������������������������������
	Includes
	�������� */

/*	Glib 
	���� */
#include "gsys.h"
#include "gdebug.h"

/*	Game
	���� */
#include "gutils.h"


/* ���������������������������������������������������������������������������
	Function Prototypes
	������������������� */

/* ���������������������������������������������������������������������������
	Vars
	���� */
U32 RndTabs[6];

/* ���������������������������������������������������������������������������
	Tables
	������ */
U32 DefaultRnd[6]=
{
	0xabcd1234,
	0xffde1534,
	0xffde1534,
	0x001a1010,
	0xf61a1890,
	0x00000002,
};


/* ���������������������������������������������������������������������������
	Init the general utilities module
	��������������������������������� */
BOOL GU_InitModule(void)
{
	GU_SetRndSeed(DefaultRnd);
	return(TRUE);
}	


/* ���������������������������������������������������������������������������
	Init the general utilities module
	��������������������������������� */
void GU_SetRndSeed(U32 *Tab)
{
	int		f;

	for (f=0;f<6;f++)
		RndTabs[f]=Tab[f];
}	

/* ���������������������������������������������������������������������������
	Get a random 32 bit unsigned number
	����������������������������������� */
U32 GU_GetRnd(void)
{
	U32		RetVal;

	RetVal=RndTabs[1]+RndTabs[4];

	if (RetVal< RndTabs[1] && RetVal < RndTabs[4])
		RetVal++;

	RetVal++;

	RndTabs[0]=RetVal;

	RndTabs[5]=RndTabs[4];
	RndTabs[4]=RndTabs[3];
	RndTabs[3]=RndTabs[2];
	RndTabs[2]=RndTabs[1];
	RndTabs[1]=RndTabs[0];

	return(RndTabs[0]);
}

/* ���������������������������������������������������������������������������
	Function:		S32 GU_GetSRnd(void)
	Notes:			Get a signed random number
	Returns:		Signed Number
	�������������������������������������������������������������������������� */
S32 GU_GetSRnd(void)
{
	return((S32)GU_GetRnd());
}	

/* ���������������������������������������������������������������������������
	Function:		U32 GU_GetRndRange(UINT Range)
	Notes:			Returns a number between 0 and Range-1
	Params:			Range	->	Max number returned -1
	Returns:		unsigned number
	�������������������������������������������������������������������������� */
U32 GU_GetRndRange(UINT Range)
{
	return(GU_GetRnd()%Range);
}	

/* ���������������������������������������������������������������������������
	Function:		UINT GU_AlignVal(UINT w,UINT round)
	Notes:			Align a value to a boundary (7 round to boundaries of 4 = 8)
	Params:			w =	Value to align
					round =	Boundaries to align it to			
	Returns:		Aligned number
	�������������������������������������������������������������������������� */
UINT GU_AlignVal(UINT w,UINT round)
{
	w += round - 1;
	return (w - w % round);
}	

/* ���������������������������������������������������������������������������
	ends */
