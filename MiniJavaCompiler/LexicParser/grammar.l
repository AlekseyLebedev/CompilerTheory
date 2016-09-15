%{
#include <iostream>
%}

DIGIT [0-9]
LETTER [a-zA-Z]
%%
"class" std::cout<<"CLASS";
%%
//123
int yywrap()
{
	return 1;
}