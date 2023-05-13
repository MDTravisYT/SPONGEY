/*=========================================================================

	twindup.cpp

	Author:		Charles Blair
	Created:	
	Project:	Spongebob
	Purpose:	

	Copyright (c) 2001 Climax Development Ltd

===========================================================================*/

#ifndef	__TRIGGERS_TWINDUP_H__
#include "triggers\twindup.h"
#endif

#ifndef	__PLAYER_PLAYER_H__
#include "player\player.h"
#endif

#ifndef __SYSTEM_GSTATE_H__
#include "system\gstate.h"
#endif


void	CWindUpTrigger::collidedWith(CThing *_thisThing)
{
	switch( _thisThing->getThingType() )
	{
		case TYPE_PLAYER:
		{
			CPlayer *player = (CPlayer *) _thisThing;

			DVECTOR move;
			move.vx = 0;
			move.vy = -4 * GameState::getFramesSinceLast();

			player->shove( move );
			move.vx = player->getMoveVelocity()->vx;
			player->setMoveVelocity( &move );
			player->setFloating();

			break;
		}

		default:
			break;
	}
}

