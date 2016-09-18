%option noyywrap

%{
#include <iostream>
#include <cstring>

int col = 1;
int row = 1;
bool needLocation = true;

static void updateLocation()
{
	if(needLocation) {
		std::cout << "{" << row << "," << col << "}";
	}
	col += strlen(yytext);
	needLocation = true;
}

#define YY_USER_ACTION updateLocation();

%}

DIGIT [0-9]
LETTER [a-zA-Z]

%%

"/*"((("*"[^/])?)|[^*])*"*/" { 
	//Comment
}

class {
	std::cout << "CLASS";
}
int {
	std::cout << "INT";
}
char {
	std::cout << "CHAR";
}
if {
	std::cout << "IF";
}
else {
	std::cout << "ELSE";
}
return {
	std::cout << "RETURN";
}
";" {
	std::cout << "SEMI";
}
{LETTER}({DIGIT}|{LETTER})* {
	std::cout << "ID(" << yytext << ")";	
}
"(" {
	std::cout << "LPAREN";	
}
")" {
	std::cout << "RPAREN";	
}
"*" {
	std::cout << "STAR";	
}
"\n|(\n\r)" {	
	row++;
	col = 1;
	std::cout << yytext;
	needLocation = false;
}
"{" {
	std::cout << "LBRACE";	
}
"}" {
	std::cout << "RBRACE";	
}
"!" {
	std::cout << "BANG";	
}
"," {
	std::cout << "COMMA";	
}
(" ")* {	
	std::cout << yytext;
	needLocation = false;
}
("\t")* {	
	std::cout << yytext;
	needLocation = false;
}
"\""({DIGIT}|{LETTER}|".")*"\"" {
	std::cout << "STRING(" << yytext << ")";	
}
({DIGIT}|"-"{DIGIT})({DIGIT})* {
	std::cout << "NUM(" << yytext << ")";	
}

. { return yytext[0]; }
%%
//Empty
