/*=========================================================================

	font.h

	Author:  PKG
	Created:
	Project:
	Purpose:

	Copyright (c) 2000

===========================================================================*/

#ifndef __GFX_FONT_H__
#define __GFX_FONT_H__

/*----------------------------------------------------------------------
	Includes
	-------- */

#ifndef __GFX_FDATA_H__
#include "gfx\fdata.h"
#endif

#ifndef __GFX_SPRBANK_H__
#include "gfx\sprbank.h"
#endif


/*----------------------------------------------------------------------
	Tyepdefs && Defines
	------------------- */

/*----------------------------------------------------------------------
	Structure defintions
	-------------------- */

class FontBank
{
public:
	enum Justification
	{
		JUST_LEFT,
		JUST_RIGHT,
		JUST_CENTRE
	};

			FontBank()	{ m_initialised=false; };
	virtual ~FontBank()	{ ASSERT( !m_initialised ); }

	virtual void	initialise( FontData *_fontData );
	void	dump();
	int		isInitialised()				{ return m_initialised; }
	void			print( int _x, int _y, s32 _textId );
	virtual void	print( int _x, int _y, const char *_text );
	int				printTillEndOfLine( int _x, int _y, const char *_text );
	void	setColour( u8 _r, u8 _g, u8 _b );
	void	setJustification( Justification _justification );
	void	setOt( u16 _ot );
	void	setPrintArea( int _x, int _y, int _w, int _h );
	void	setTrans( int _trans );
	void	setSMode( int _sMode );

	virtual int		getCharWidth( char _char );
	virtual int		getCharHeight();
	int		getStringWidth( const char * text );
	int		getStringWidth( s32 _textId );
	int		getStringHeight( const char *_text );
	int		getStringHeight( s32 _textId );

	virtual int		getCharGapX();
	virtual int		getCharGapY();

	int		getStrWrapLen( const char *_text,int _maxWidth );

	void	setWobble(int _wobble)					{m_wobble=_wobble;}

private:
	virtual int		printChar( char _char,int _x,int _y );


	enum {
		DEFAULT_R=128,
		DEFAULT_G=128,
		DEFAULT_B=128,
		DEFAULT_JUSTIFICATION=JUST_LEFT,
		DEFAULT_OT=10,
	};


	static void	think(int _frames);		// Needed for the wobble only.. call once from main loop or summink..
	friend void MainLoop();	

protected:
	FontData		*m_fontData;
	u8				m_r, m_g, m_b;						// Font colour
	Justification	m_justification;
	u16				m_ot;								// Depth
	RECT			m_printArea;
	SpriteBank		m_spriteBank;
	int				m_initialised;

	int				m_trans, m_sMode;

	int				m_wobble;
	static int		s_wobbleValue;

};


class ScalableFontBank : public FontBank
{
public:
	virtual void	initialise( FontData *_fontData );

	void			setScale(int _newScale)				{m_fontScale=_newScale;}

	virtual int		getCharWidth( char _char );
	virtual int		getCharHeight();

	virtual int		getCharGapX();
	virtual int		getCharGapY();

private:
	virtual int		printChar( char _char,int _x,int _y );

	int				m_fontScale;
};


/*---------------------------------------------------------------------- */

#endif	/* __GFX_FONT_H__ */

/*===========================================================================
 end */
