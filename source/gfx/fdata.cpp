/*=========================================================================

	fdata.cpp

	Author:		PKG
	Created: 
	Project:	PRLSR
	Purpose: 

	Copyright (c) 2000 Climax Development Ltd

===========================================================================*/


/*----------------------------------------------------------------------
	Includes
	-------- */

#include "gfx\fdata.h"

#ifndef		__FILE_EQUATES_H__
#include	"biglump.h"
#endif

#ifndef __SPR_SPRITES_H__
#include <sprites.h>
#endif


/*	Std Lib
	------- */

/*----------------------------------------------------------------------
	Tyepdefs && Defines
	------------------- */

/*----------------------------------------------------------------------
	Structure defintions
	-------------------- */

/*----------------------------------------------------------------------
	Positional Vars
	--------------- */

/*----------------------------------------------------------------------
	Function Prototypes
	------------------- */

/*----------------------------------------------------------------------
	Vars
	---- */

s16	standardFontTab[]=
{
							-1		,FRM__ERROR,-1	  ,-1      ,-1      ,-1      ,-1      ,-1      ,
							-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
							-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
							-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/*   ! " # $ % & ' */	      -1,FRM__33 ,FRM__34 ,-1      ,-1      ,FRM__37 ,-1      ,FRM__39 ,
	/* ( ) * + , - . / */	FRM__40 ,FRM__41 ,FRM__42 ,FRM__43 ,FRM__44 ,FRM__45 ,FRM__46 ,FRM__47 ,
	/* 0 1 2 3 4 5 6 7 */	FRM__48 ,FRM__49 ,FRM__50 ,FRM__51 ,FRM__52 ,FRM__53 ,FRM__54 ,FRM__55 ,
	/* 8 9 : ; < = > ? */	FRM__56 ,FRM__57 ,FRM__58 ,-1      ,FRM__60 ,FRM__61 ,FRM__62 ,FRM__63 ,
	/* @ A B C D E F G */	-1      ,FRM__65 ,FRM__66 ,FRM__67 ,FRM__68 ,FRM__69 ,FRM__70 ,FRM__71 ,
	/* H I J K L M N O */	FRM__72 ,FRM__73 ,FRM__74 ,FRM__75 ,FRM__76 ,FRM__77 ,FRM__78 ,FRM__79 ,
	/* P Q R S T U V W */	FRM__80 ,FRM__81 ,FRM__82 ,FRM__83 ,FRM__84 ,FRM__85 ,FRM__86 ,FRM__87 ,
	/* X Y Z [ \ ] ^ _ */	FRM__88 ,FRM__89 ,FRM__90 ,-1      ,-1      ,-1      ,-1      ,FRM__95 ,
	/* ` a b c d e f g */	-1      ,FRM__97 ,FRM__98 ,FRM__99 ,FRM__100,FRM__101,FRM__102,FRM__103,
	/* h i j k l m n o */	FRM__104,FRM__105,FRM__106,FRM__107,FRM__108,FRM__109,FRM__110,FRM__111,
	/* p q r s t u v w */	FRM__112,FRM__113,FRM__114,FRM__115,FRM__116,FRM__117,FRM__118,FRM__119,
	/* x y z { | } ~ . */	FRM__120,FRM__121,FRM__122,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	-1      ,FRM__39 ,FRM__39 ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,-1      ,
	/* � � � � � � � � */	FRM__192,FRM__193,FRM__194,FRM__195,FRM__196,FRM__197,FRM__198,FRM__199,
	/* � � � � � � � � */	FRM__200,FRM__201,FRM__202,FRM__203,FRM__204,FRM__205,FRM__206,FRM__207,
	/* � � � � � � � � */	FRM__208,      -1,FRM__210,FRM__211,FRM__212,FRM__213,FRM__214,      -1,
	/* � � � � � � � � */	FRM__216,FRM__217,FRM__218,FRM__219,FRM__220,FRM__221,FRM__222,FRM__223,
	/* � � � � � � � � */	FRM__224,FRM__225,FRM__226,FRM__227,FRM__228,      -1,FRM__230,      -1,
	/* � � � � � � � � */	FRM__232,FRM__233,FRM__234,FRM__235,FRM__236,FRM__237,FRM__238,FRM__239,
	/* � � � � � � � � */	      -1,      -1,FRM__242,FRM__243,FRM__244,FRM__245,FRM__246,      -1,
	/* � � � � � � � � */	      -1,FRM__249,FRM__250,FRM__251,FRM__252,FRM__253,      -1,FRM__255,
};
FontData	standardFont( SPRITES_SPRITES_SPR,	standardFontTab,	13,	0,1, 4 );

/*----------------------------------------------------------------------
	Function:
	Purpose:
	Params:
	Returns:
  ---------------------------------------------------------------------- */
FontData::FontData( FileEquate _fontFileId, s16 *_fontTab, s16 _charHeight, s16 _charGapX, s16 _charGapY, s16 _spaceWidth )
{
	fontFileId=_fontFileId;
	fontTab=_fontTab;
	charHeight=_charHeight;
	charGapX=_charGapX;
	charGapY=_charGapY;
	spaceWidth=_spaceWidth;
}


/*===========================================================================
 end */