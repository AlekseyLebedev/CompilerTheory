%option noyywrap

%{
#include <iostream>
#include <cstring>
#include <string>

#include <algorithm>

int col=1;
int row=1;

static void updateLocation(bool needLocation = true)
{
	if (needLocation ) {
		std::cout << "{" << row << "," << col << "}";
	}
	col += strlen(yytext);
}

void newLine() {
	++row;
	col=1;
	std::cout<<"\n";
}

void printText( char* text = "", bool isValue = false, bool needLocation = true) {
	
	if( strcmp(text, "") == 0 ) {
		std::string str = yytext;
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	
		std::cout << str;
	} else {
		std::cout << text;
		if( isValue ) {
			std::cout << "(" << yytext << ")";
		}
	}
	updateLocation(needLocation);
}

%}

DIGIT [0-9]
LETTER [_a-zA-Z]

%%


"\""({DIGIT}|{LETTER}|"."|"\\"|"\/"|"*")*"\"" {
	printText("STR", true);
}
"/*"((("*"[^/])?)|[^*])*"*/" {
	// Comment: /**/

	int countOf = 0;
	for (int i = 0; i < strlen(yytext); ++i) {
		if ((yytext[i] == '\r') || (yytext[i] == '\n')) {
			countOf = i;
			++row;
			col = 1;
		}
	}
	col = -countOf;
	updateLocation(false);
}
"//""//"(.)*"\n" {
	// Comment: //
	newLine();
}
class|public|private|protected|static|extends {
	printText();
}
void|int|char|String|boolean {
	printText();
}
if|else|while|do {
	printText();
}
main|length|return|this|new|true|false {
	printText();
}
System.out.println {
	printText("SOP");
}
";" {
	printText("SEMI");
}
{LETTER}({DIGIT}|{LETTER})* {
	printText("ID", true);
}
"(" {
	printText("LPAREN");
}
")" {
	printText("RPAREN");
}
"[" {
	printText("LBRACKET");
}
"]" {
	printText("RBRACKET");
}
"{" {
	printText("LBRACE");
}
"}" {
	printText("RBRACE");
}
"*" {
	printText("STAR");
}
"%" {
	printText("PERCENT");
}
"\n" {
	newLine();
}
"!" {
	printText("NOT");
}
"<" {
	printText("LESS");
}
"=" {
	printText("EQUAL");
}
"+" {
	printText("PLUS");
}
"-" {
	printText("MINUS");
}
"&&" {
	printText("AND");
}
"||" {
	printText("OR");
}
"," {
	printText("COMMA");
}
"." {
	printText("DOT");
}
(" ")*|("\t")*|"\r" {
	printText(yytext, false, false);
}
({DIGIT}|"-"{DIGIT})({DIGIT})* {
	printText("NUM", true);
}
. { return yytext[0]; }
%%
//Empty
