/* ���������������������������������������������������������������������������
	File:			LL.C

	Notes:			General Link List Handling Code
	
	Author:			G Robert Liddon @ Croydon
	Created:		Wednesday 6th October 1994

	Copyright (C) 1994 G Robert Liddon
	All rights reserved. 
  ��������������������������������������������������������������������������� */

/* ���������������������������������������������������������������������������
	Includes
	�������� */
#include "ll.h"

/* ���������������������������������������������������������������������������
	Defines
	������� */

/* ���������������������������������������������������������������������������
	Detach from a list
	������������������ */
void LL_DetachFromList(LinkList **Head,LinkList *ThisObj)
{
	if (ThisObj->Prev)
		ThisObj->Prev->Next=ThisObj->Next;
	else
		*Head=ThisObj->Next;

	if (ThisObj->Next)
		ThisObj->Next->Prev=ThisObj->Prev;
}

/* ���������������������������������������������������������������������������
	Add To A List
	������������� */
void LL_AddToList(LinkList **Head,LinkList *ThisObj)
{
	ThisObj->Prev=NULL;

	if ((ThisObj->Next=*Head))
		ThisObj->Next->Prev=ThisObj;

	*Head=ThisObj;
}


/* ���������������������������������������������������������������������������
	ends
	���� */
