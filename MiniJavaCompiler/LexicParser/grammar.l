%option noyywrap

%{
#include <iostream>

static void updateLocation()
{
	std::cout << "Hello, world!";
}
#define YY_USER_ACTION updateLocation();
%}

DIGIT [0-9]
LETTER [a-zA-Z]
%%
"/*"((("*"[^/])?)|[^*])*"*/"	{ std::cout << "comment"; }
. { return yytext[0]; }
%%
//123
