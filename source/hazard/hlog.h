/*=========================================================================

	hlog.h

	Author:		CRB
	Created: 
	Project:	Spongebob
	Purpose: 

	Copyright (c) 2001 Climax Development Ltd

===========================================================================*/

#ifndef __HAZARD_HLOG_H__
#define __HAZARD_HLOG_H__

#ifndef __HAZARD_HAZARD_H__
#include "hazard\hazard.h"
#endif

class CNpcLogHazard : public CNpcHazard
{
public:
	void				init();
	void				setWaypoints( sThingHazard *ThisHazard );
protected:
	void				processMovement( int _frames );

	s32					m_velocity;
	s32					m_height;
};

#endif