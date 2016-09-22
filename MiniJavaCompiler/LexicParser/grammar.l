%option noyywrap

%{
#include <iostream>
#include <cstring>

int col=1;
int row=1;

static void updateLocation(bool needLocation = true)
{
	if(needLocation) {
		std::cout << "{" << row << "," << col << "}";
	}
	col += strlen(yytext);
}

void newLine() {
	++row;
	col=1;
	std::cout<<"\n";
}

void printText(char* text, bool needLocation = true) {
	std::cout << text;
	updateLocation(needLocation);
}

%}

DIGIT [0-9]
LETTER [_a-zA-Z]

%%


"\""({DIGIT}|{LETTER}|"."|"\\"|"\/"|"*")*"\"" {
	std::cout << "STR(" << yytext << ")";	
	updateLocation();
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
class {
	printText("CLASS");
}
extends {
	printText("EXTENDS");
}
public {
	printText("PUBLIC");
}
protected {
	printText("PROTECTED");
}
private {
	printText("PRIVATE");
}
static {
	printText("STATIC");
}
void {
	printText("VOID");
}
main {
	printText("MAIN");
}
int {
	printText("INT");
}
char {
	printText("CHAR");
}
boolean {
	printText("BOOLEAN");
}
String {
	printText("STRING");
}
if {
	printText("IF");
}
else {
	printText("ELSE");
}
while {
	printText("WHILE");
}
return {
	printText("RETURN");
}
this {
	printText("THIS");
}
new {
	printText("NEW");
}
System.out.println {
	printText("SOP");
}
length {
	printText("LENGTH");
}
true {
	printText("TRUE");
}
false {
	printText("FALSE");
}
";" {
	printText("SEMI");
}
{LETTER}({DIGIT}|{LETTER})* {
	std::cout << "ID(" << yytext << ")";	
	updateLocation();
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
(" ")* {
	printText(yytext, false);
}
("\t")* {
	printText(yytext, false);
}
"\r" {
	printText(yytext, false);
}
({DIGIT}|"-"{DIGIT})({DIGIT})* {
	std::cout << "NUM(" << yytext << ")";	
	updateLocation();
}
. { return yytext[0]; }
%%
//Empty
