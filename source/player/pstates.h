/*=========================================================================

	pstates.h

	Author:		PKG
	Created:	
	Project:	Spongebob
	Purpose:	

	Copyright (c) 2001 Climax Development Ltd

===========================================================================*/

#ifndef	__PLAYER_PSTATES_H__
#define __PLAYER_PSTATES_H__

/*----------------------------------------------------------------------
	Includes
	-------- */

/*	Std Lib
	------- */

/*----------------------------------------------------------------------
	Tyepdefs && Defines
	------------------- */

/*----------------------------------------------------------------------
	Structure defintions
	-------------------- */

class CPlayerState
{
public:
	virtual void				enter(class CPlayerModeBase *_playerMode)		{;}
	virtual void				think(class CPlayerModeBase *_playerMode)		{;}
};


/*----------------------------------------------------------------------
	Globals
	------- */

/*----------------------------------------------------------------------
	Functions
	--------- */

/*---------------------------------------------------------------------- */

#endif	/* __PLAYER_PSTATES_H__ */

/*===========================================================================
 end */


