/* ���������������������������������������������������������������������������
	File:		GMAIN.C

	Notes:		Main!

	Author:		G Robert Liddon @ 73b

	Created:	Wednesday 27th March 1996

	Copyright (C) 1996 DCI Ltd All rights reserved. 
  ���������������������������������������������������������������������������� */


/* ���������������������������������������������������������������������������
	Glib Includes
	������������� */
#include "gmain.h"
#include "gal.h"
#include "gsys.h"
#include "tick.h"
#include "gutils.h"
				 
/* ���������������������������������������������������������������������������
	Function Prototypes
	������������������� */

/* ���������������������������������������������������������������������������
	Main
	���� */
void main(void)
{
	GSYS_InitMachine();
	GAL_InitModule();
	TICK_InitModule();
	GU_InitModule();

	AppMain();

	while (1)
		{
		}
}	

/* ���������������������������������������������������������������������������
	Ends
	���� */
