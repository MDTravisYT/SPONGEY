/************************************************************
yycsyner.cpp
This file can be freely modified for the generation of
custom code.

Copyright (c) 1999 Bumble-Bee Software Ltd.
************************************************************/

#include "cyacc.h"

void yyparser::yysyntaxerror(void)
{
	yyerror("syntax error");
}
