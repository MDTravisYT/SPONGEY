/*=========================================================================

	pickup.h

	Author:		PKG
	Created:	
	Project:	Spongebob
	Purpose:	

	Copyright (c) 2001 Climax Development Ltd

===========================================================================*/

#ifndef	__PICKUPS_PICKUP_H__
#define __PICKUPS_PICKUP_H__

/*----------------------------------------------------------------------
	Includes
	-------- */

#ifndef __THING_THING_H__
#include "thing/thing.h"
#endif

#ifndef __SOUND_SOUND_H__
#include "sound\sound.h"
#endif


/*	Std Lib
	------- */

/*----------------------------------------------------------------------
	Tyepdefs && Defines
	------------------- */

typedef enum
{
	PICKUP__BIG_HEALTH,				// No longer in the game.. Yay(!)
	PICKUP__MEDIUM_HEALTH,			// No longer in the game.. Yay(!)
	PICKUP__SMALL_HEALTH,			// No longer in the game.. Yay(!)
	PICKUP__LIFE,
	PICKUP__SPATULA,
	PICKUP__JELLY_LAUNCHER_AMMO,
	PICKUP__BUBBLE_MIXTURE,
	PICKUP__BUBBLE_WAND,
	PICKUP__NET,
	PICKUP__GLASSES,				// No longer in the game.. Yay(!)
	PICKUP__SQUEAKY_SHOES,
	PICKUP__BALLOON,
	PICKUP__HELMET,
	PICKUP__CORAL_BLOWER,
	PICKUP__QUEST_ITEM,
	PICKUP__BALLOON_AND_SPATULA,
	PICKUP__JELLY_LAUNCHER,
	PICKUP__KELP_TOKEN,
	PICKUP__GLOVE,

	PICKUP__MAX
}
PICKUP_TYPE;


/*----------------------------------------------------------------------
	Structure defintions
	-------------------- */

class CBasePickup : public CPickupThing
{
public:
	enum
	{ // For Dynamic ThingCache
		MAX_SUBTYPE	=PICKUP__MAX,
	};
	virtual void		init();
	virtual void		shutdown();
	virtual void		think(int _frames);
	virtual void		render();

	virtual DVECTOR		getSizeForPlacement()=0;
	void				setPos(const struct DVECTOR *_pos);
	virtual void		collect(class CPlayer *_player);

protected:
	enum
	{
		DEFAULT_VISIBILITY_RADIUS=32,
	};

	virtual int			getVisibilityRadius()				{return DEFAULT_VISIBILITY_RADIUS;}

	virtual void		thinkPickup(int _Frames)			{;}
	virtual void		renderPickup(DVECTOR *_pos)=0;

	virtual void		collidedWith(CThing *_thisThing);


private:
	virtual CSoundMediator::SFXID	sfxToPlayWhenCollected(){return CSoundMediator::SFX_ITEM__ANY_OTHER_ITEM;}

};


class CBaseRespawningPickup : public CBasePickup
{
public:
	virtual void		init();
	virtual void		think(int _frames);
	virtual void		render();

	virtual void		collect(class CPlayer *_player);

protected:
	virtual int			getRespawnTime()=0;
	virtual int			canCollide()						{return m_respawnTime==0;}

private:
	int					m_respawnTime;

};


class CBaseWeaponPickup : public CBasePickup
{
public:
	virtual void		init();
	virtual void		think(int _frames);

	void				setHasBeenCollected()				{m_hasBeenCollected=true;}
	int					getHasBeenCollected()				{return m_hasBeenCollected;}

protected:
	virtual void		collidedWith(CThing *_thisThing);
	int					m_dontAutoPickUpUntilPlayerMovesOffMe;
	int					m_collidedWithPlayer;
	int					m_hasBeenCollected;

private:
	virtual CSoundMediator::SFXID	sfxToPlayWhenCollected(){return CSoundMediator::SFX_ITEM__POWER_UP_ITEM;}

};


class CBaseWeaponSimplePickup : public CBaseWeaponPickup
{
public:
	virtual void		init();
	virtual DVECTOR		getSizeForPlacement();

protected:
	virtual void		renderPickup(DVECTOR *_pos);

	virtual int			getWeaponSpriteFrame()=0;

};


/*----------------------------------------------------------------------
	Globals
	------- */

/*----------------------------------------------------------------------
	Functions
	--------- */

CBasePickup	*createPickup(const PICKUP_TYPE _type,const DVECTOR *_pos);


/*---------------------------------------------------------------------- */

#endif	/* __PICKUPS_PICKUP_H__ */

/*===========================================================================
 end */
