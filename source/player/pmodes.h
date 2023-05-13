/*=========================================================================

	pmodes.h

	Author:		PKG
	Created:	
	Project:	Spongebob
	Purpose:	

	Copyright (c) 2001 Climax Development Ltd

===========================================================================*/

#ifndef	__PLAYER_PMODES_H__
#define __PLAYER_PMODES_H__

/*----------------------------------------------------------------------
	Includes
	-------- */

#ifndef _GLOBAL_HEADER_
#include "system\global.h"
#endif

#ifndef __PLAYER_PLAYER_H__
#include "player\player.h"
#endif


/*	Std Lib
	------- */

/*----------------------------------------------------------------------
	Tyepdefs && Defines
	------------------- */

/*----------------------------------------------------------------------
	Structure defintions
	-------------------- */

typedef enum
{
	PM__JUMP_VELOCITY,
	PM__MAX_JUMP_FRAMES,
	PM__MAX_SAFE_FALL_FRAMES,
	PM__MAX_RUN_VELOCITY,
	PM__RUN_SPEEDUP,
	PM__RUN_REVERSESLOWDOWN,
	PM__RUN_SLOWDOWN,
	PM__GRAVITY,
	PM__TERMINAL_VELOCITY,
	PM__BUTT_FALL_VELOCITY,
	PM__HITREACT_XVELOCITY,
	PM__HITREACT_YVELOCITY,
	PM__HITREACT_FRAMES,
		
	NUM_PLAYER_METRICS
}PLAYER_METRIC;

struct PlayerMetrics
{
	s16		m_metric[NUM_PLAYER_METRICS];
};

enum
{
	DEFAULT_PLAYER_JUMP_VELOCITY=4,
	DEFAULT_PLAYER_MAX_JUMP_FRAMES=10,
	DEFAULT_PLAYER_MAX_SAFE_FALL_FRAMES=30,
	DEFAULT_PLAYER_MAX_RUN_VELOCITY=6,
	DEFAULT_PLAYER_RUN_SPEEDUP=2<<2,
	DEFAULT_PLAYER_RUN_REVERSESLOWDOWN=3<<2,
	DEFAULT_PLAYER_RUN_SLOWDOWN=2<<2,
	DEFAULT_PLAYER_PLAYER_GRAVITY=2<<2,
	DEFAULT_PLAYER_TERMINAL_VELOCITY=8,
	DEFAULT_BUTT_FALL_VELOCITY=14,
	DEFAULT_HITREACT_XVELOCITY=5,
	DEFAULT_HITREACT_YVELOCITY=3-1,
	DEFAULT_HITREACT_FRAMES=15,
};



class CPlayerMode
{
public:
	virtual void	initialise(class CPlayer *_player)	{m_player=_player;}
	virtual void	shutdown()							{;}
	virtual void	enter()								{;}
	virtual void	setInitialState(int _state)			{;}
	virtual void	think()								{;}
	virtual void	render(DVECTOR *_pos)				{;}
	virtual void	renderModeUi()						{;}		// Ui specific to this mode (eg: ammo)
	virtual int		canDoLookAround()					{return false;}
	virtual void	springPlayerUp(int _springHeight)	{;}
	virtual void	setFloating()						{;}
	void			inSoakUpState();
	virtual int		canConverse()						{return true;}

	virtual int		setState(int _state)				{return 0;}
	virtual int		getState()							{return STATE_IDLE;}			// ARSE.. states need to go back in CPlayer! (pkg)
	int				getHeightFromGound();

	int				getPadInputHeld();
	int				getPadInputDown();


	virtual ATTACK_STATE	getAttackState()			{return ATTACK_STATE__NONE;}


public:
	DVECTOR	const &getPlayerPos();						// Public so that the states can get the position for bubicle spawners
protected:
	void			setPlayerPos(DVECTOR *_pos);		// Private so that they cannot directly alter it

	void			respawn();

	class CPlayer	*m_player;

};


class CPlayerModeBase : public CPlayerMode
{
public:
	enum
	{
		VELOCITY_SHIFT=4,
	};

	virtual void	enter();
	virtual void	setInitialState(int _state)			{m_currentState=(PLAYER_STATE)_state;}
	virtual void	think();
	virtual void	render()							{;}
	virtual int		canDoLookAround();
	virtual void	springPlayerUp(int _springHeight)	{m_springHeight=_springHeight;setState(STATE_SPRINGUP);}
	virtual void	setFloating()						{setState( STATE_FLOAT );}

	virtual ATTACK_STATE	getAttackState();

	virtual int					canTeeter()				{return m_currentState==STATE_IDLE;}
	virtual int					canFallForever()		{return m_currentState==STATE_BUTTFALL;}

	void						thinkVerticalMovement();
	void						thinkHorizontalMovement();
	void						playerHasHitGround();

	
	virtual const struct PlayerMetrics	*getPlayerMetrics();
	virtual int					setState(int _state);
	virtual int					getState()				{return m_currentState;}
	int							getFacing();
	void						setFacing(int _facing);
	virtual int					getAnimNo();
	virtual void				setAnimNo(int _animNo);
	virtual void				setAnimFrame(int _animFrame);
	virtual int					getAnimFrame();
	virtual int					getAnimFrameCount();
	int							advanceAnimFrameAndCheckForEndOfAnim();
	DVECTOR						getMoveVelocity();
	void						zeroMoveVelocity();
	void						setMoveVelocity(DVECTOR *_moveVel);
	int							isOnEdge();
	int							canMoveLeft();
	int							canMoveRight();
	virtual void				setPlayerCollisionSize(int _x,int _y,int _w,int _h);
	virtual void				getPlayerCollisionSize(int *_x,int *_y,int *_w,int *_h);
	CPlayer						*getPlayer()							{ return( m_player ); }

	int							getIsInWater()							{return m_player->getIsInWater();}
	int							getIsHelmetFullSoICanStopSoakingUp()	{return m_player->getIsHelmetFullSoICanStopSoakingUp();}
	int							getIsHelmetSoFullThatIDontNeedToSoakUp(){return m_player->getIsHelmetSoFullThatIDontNeedToSoakUp();}

	void						moveLeft();
	void						moveRight();
	int							slowdown();
	void						jump();
	void						spring();
	void						jumpback();
	void						fall();
	void						fallToDance();
	void						buttFall();

	int							getSpringHeight()		{return m_springHeight;}


private:
	int							m_fallFrames;
	int							m_springHeight;


protected:
	virtual class CPlayerState	**getStateTable();


private:
	class CPlayerState			*m_currentStateClass;
	PLAYER_STATE				m_currentState;
};


/*----------------------------------------------------------------------
	Globals
	------- */

/*----------------------------------------------------------------------
	Functions
	--------- */

/*---------------------------------------------------------------------- */

#endif	/* __PLAYER_PMODES_H__ */

/*===========================================================================
 end */



