/*=========================================================================

	prepro.h

	Author:		PKG
	Created:
	Project:	Spongebob
	Purpose:

	Copyright (c) 2000 Climax Development Ltd

===========================================================================*/

#ifndef __PREPRO_H__
#define	__PREPRO_H__

/*----------------------------------------------------------------------
	Includes
	-------- */

/*	Std Lib
	------- */

/*----------------------------------------------------------------------
	Tyepdefs && Defines
	------------------- */

// lookupMacro results
enum
{
	UNKNOWN_MACRO,
	POSSIBLE_KNOWN_MACRO,
	KNOWN_MACRO,
};

/*----------------------------------------------------------------------
	Structure defintions
	-------------------- */

/*----------------------------------------------------------------------
	Globals
	------- */

/*----------------------------------------------------------------------
	Functions
	--------- */

extern int preprocessorCmd(char *_cmd);

extern char *lookupMacro(char *_name,int *_result);


/*---------------------------------------------------------------------- */

#endif	/* __PREPRO_H__ */

/*===========================================================================
 end */