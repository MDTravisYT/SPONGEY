/*=========================================================================

	tfemit.h

	Author:		PKG
	Created:	
	Project:	Spongebob
	Purpose:	

	Copyright (c) 2001 Climax Development Ltd

===========================================================================*/

#ifndef	__TRIGGERS_TFEMIT_H__
#define __TRIGGERS_TFEMIT_H__

/*----------------------------------------------------------------------
	Includes
	-------- */

#ifndef __THING_THING_H__
#include "thing/thing.h"
#endif

#ifndef __TRIGGER_TRIGGER_HEADER__
#include "triggers\trigger.h"
#endif

#include "fx\fx.h"
#include "fx\fxbaseanim.h"

/*	Std Lib
	------- */

/*----------------------------------------------------------------------
	Tyepdefs && Defines
	------------------- */

/*----------------------------------------------------------------------
	Structure defintions
	-------------------- */

class CFlameEmitterTrigger : public CTrigger
{
public:
	virtual void		setPositionAndSize(int _x,int _y,int _w,int _h);
	void				setHeading(int newHeading);
	void				setSize( int _w, int _h );
protected:
	virtual void		collidedWith(CThing *_thisThing);
	CFX					*m_effect;
};

/*----------------------------------------------------------------------
	Globals
	------- */

/*----------------------------------------------------------------------
	Functions
	--------- */

/*---------------------------------------------------------------------- */

#endif

/*===========================================================================
 end */
