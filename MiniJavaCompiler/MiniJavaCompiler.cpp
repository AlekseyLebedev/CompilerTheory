// MiniJavaCompiler.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\winflexbison\tools\FlexLexer.h"

int yylex();

int main()
{
	yylex();
    return 0;
}

