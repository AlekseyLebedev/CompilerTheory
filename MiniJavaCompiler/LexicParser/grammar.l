%option noyywrap

%{
#include <iostream>
#include <cstring>

int col = 1;
int row = 1;

static void updateLocation(bool needLocation = true)
{
	if(needLocation) {
		std::cout << "{" << row << "," << col << "}";
	}
	col += strlen(yytext);
	needLocation = true;
}
%}

DIGIT [0-9]
LETTER [a-zA-Z]

%%

"/*"((("*"[^/])?)|[^*])*"*/" { 
	//Comment
	updateLocation();
}

class {
	std::cout << "CLASS";
	updateLocation();
}
int {
	std::cout << "INT";
	updateLocation();
}
char {
	std::cout << "CHAR";
	updateLocation();
}
if {
	std::cout << "IF";
	updateLocation();
}
else {
	std::cout << "ELSE";
	updateLocation();
}
return {
	std::cout << "RETURN";
	updateLocation();
}
";" {
	std::cout << "SEMI";
	updateLocation();
}
{LETTER}({DIGIT}|{LETTER})* {
	std::cout << "ID(" << yytext << ")";	
	updateLocation();
}
"(" {
	std::cout << "LPAREN";	
	updateLocation();
}
")" {
	std::cout << "RPAREN";	
	updateLocation();
}
"*" {
	std::cout << "STAR";	
	updateLocation();
}
"\r" {	
	std::cout << yytext;
	updateLocation(false);
}
"\n" {	
	row++;
	col = 1;
	updateLocation(false);
	col = 1;
	std::cout << yytext;
}
"{" {
	std::cout << "LBRACE";	
	updateLocation();
}
"}" {
	std::cout << "RBRACE";	
	updateLocation();
}
"!" {
	std::cout << "BANG";	
	updateLocation();
}
"," {
	std::cout << "COMMA";	
	updateLocation();
}
(" ")* {	
	std::cout << yytext;
	updateLocation(false);
}
("\t")* {	
	std::cout << yytext;
	updateLocation(false);
}
"\""({DIGIT}|{LETTER}|".")*"\"" {
	std::cout << "STRING(" << yytext << ")";	
	updateLocation();
}
({DIGIT}|"-"{DIGIT})({DIGIT})* {
	std::cout << "NUM(" << yytext << ")";	
	updateLocation();
}

. { return yytext[0]; }
%%
//Empty
