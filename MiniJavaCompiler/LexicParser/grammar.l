%option noyywrap

%{
#include <iostream>
#include <cstring>

%}

DIGIT [0-9]
LETTER [a-zA-Z]
	int col = 1;
	int row = 1;
%%
"/*"((("*"[^/])?)|[^*])*"*/"	{ std::cout << "comment"; }
class {
	std::cout << "CLASS";

}
int {
	std::cout << "INT";
	std::cout << "{" << row << "," << col << "} ";
	col+=3;
}
char {
	std::cout << "CHAR";
	std::cout << "{" << row << "," << col << "} ";
	col+= 4;
}
if {
	std::cout << "IF";
	std::cout << "{" << row << "," << col << "} ";
	col+= 2;
}
else {
	std::cout << "ELSE";
	std::cout << "{" << row << "," << col << "} ";
	col+= 4;
}
return {
	std::cout << "RETURN";
	std::cout << "{" << row << "," << col << "} ";
	col+= 6;
}
";" {
	std::cout << "SEMI";
	std::cout << "{" << row << "," << col << "} ";
	col+= 1;
}
{LETTER}({DIGIT}|{LETTER})* {
	std::cout << "ID(" << yytext << ")";	
	std::cout << "{" << row << "," << col << "} ";
	col+= strlen(yytext);	
}
"(" {
	std::cout << "LPAREN";	
	std::cout << "{" << row << "," << col << "} ";
	col+= 1;	
}
")" {
	std::cout << "RPAREN";	
	std::cout << "{" << row << "," << col << "} ";
	col+= 1;
}
"*" {
	std::cout << "STAR";	
	std::cout << "{" << row << "," << col << "} ";
	col+= 1;
}
"\n" {	
	row++;
	col = 1;
}
"{" {
	std::cout << "LBRACE";	
	std::cout << "{" << row << "," << col << "} ";
	col+= 1;
}
"}" {
	std::cout << "RBRACE";	
	std::cout << "{" << row << "," << col << "} ";
	col+= 1;
}
"!" {
	std::cout << "BANG";	
	std::cout << "{" << row << "," << col << "} ";
	col+= 1;
}
"," {
	std::cout << "COMMA";	
	std::cout << "{" << row << "," << col << "} ";
	col+= 1;
}
(" ")* {	
	col+=1;
}
("\t")* {	
	col+=1;
}
"\""({DIGIT}|{LETTER}|".")*"\"" {
	std::cout << "STRING(" << yytext << ")";	
	std::cout << "{" << row << "," << col << "} ";
	col+= strlen(yytext);
}
({DIGIT}|"-"{DIGIT})({DIGIT})* {
	std::cout << "NUM(" << yytext << ")";	
	std::cout << "{" << row << "," << col << "} ";
	col+= strlen(yytext);
}

. { return yytext[0]; }
%%
//123
