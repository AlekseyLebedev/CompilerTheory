%option noyywrap

%{
#include <iostream>
#include <cstring>
#include "syntatic.h"

int col=1;
int row=1;

static void updateLocation(bool needLocation = true)
{
	if(needLocation) {
		std::cout << "{" << row << "," << col << "}";
	}
	col += strlen(yytext);
}

void newLine(){
	++row;
	col=1;
	std::cout<<"\n";
}

void debugOutput(const char* text){
	std::cout << text;
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
"//"(.)*"\n" {
	// Comment: //
	newLine();
}
class {
	debugOutput("CLASS");
	updateLocation();	
	return T_class;
}
extends {
	debugOutput("EXTENDS");
	updateLocation();
}
public {
	debugOutput("PUBLIC");
	updateLocation();
}
protected {
	debugOutput("PROTECTED");
	updateLocation();
}
private {
	debugOutput("PRIVATE");
	updateLocation();
}
static {
	debugOutput("STATIC");
	updateLocation();
}
void {
	debugOutput("VOID");
	updateLocation();
}
main {
	debugOutput("MAIN");
	updateLocation();
}
int {
	debugOutput("INT");
	updateLocation();
}
char {
	debugOutput("CHAR");
	updateLocation();
}
boolean {
	debugOutput("BOOLEAN");
	updateLocation();
}
String {
	debugOutput("STRING");
	updateLocation();
}
if {
	debugOutput("IF");
	updateLocation();
}
else {
	debugOutput("ELSE");
	updateLocation();
}
while {
	debugOutput("WHILE");
	updateLocation();
}
return {
	debugOutput("RETURN");
	updateLocation();
}
this {
	debugOutput("THIS");
	updateLocation();
}
new {
	debugOutput("NEW");
	updateLocation();
}
System.out.println {
	debugOutput("SOP");
	updateLocation();
}
length {
	debugOutput("LENGTH");
	updateLocation();
}
true {
	debugOutput("TRUE");
	updateLocation();
}
false {
	debugOutput("TRUE");
	updateLocation();
}
";" {
	debugOutput("SEMI");
	updateLocation();
}
{LETTER}({DIGIT}|{LETTER})* {
	debugOutput("ID(");
	debugOutput(yytext);
	debugOutput(")");	
	updateLocation();
}
"(" {
	debugOutput("LPAREN");	
	updateLocation();
}
")" {
	debugOutput("RPAREN");	
	updateLocation();
}
"[" {
	debugOutput("LBRACKET");	
	updateLocation();
}
"]" {
	debugOutput("RBRACKET");	
	updateLocation();
}
"{" {
	debugOutput("LBRACE");	
	updateLocation();
}
"}" {
	debugOutput("RBRACE");	
	updateLocation();
}
"*" {
	debugOutput("STAR");	
	updateLocation();
}
"%" {
	debugOutput("%");
	updateLocation();
}
"\n" {
	newLine();
}
"!" {
	debugOutput("BANG");	
	updateLocation();
}
"<" {
	debugOutput("LESS");	
	updateLocation();
}
"=" {
	debugOutput("EQUAL");	
	updateLocation();
}
"+" {
	debugOutput("PLUS");	
	updateLocation();
}
"-" {
	debugOutput("MINUS");	
	updateLocation();
}
"&&" {
	debugOutput("&&");	
	updateLocation();
}
"||" {
	debugOutput("||");	
	updateLocation();
}
"," {
	debugOutput("COMMA");	
	updateLocation();
}
"." {
	debugOutput(".");	
	updateLocation();
}
(" ")* {
	debugOutput(yytext);
	updateLocation(false);
}
("\t")* {
	debugOutput(yytext);
	updateLocation(false);
}
"\r" {
	debugOutput(yytext);
	updateLocation(false);
}
({DIGIT}|"-"{DIGIT})({DIGIT})* {
	debugOutput("NUM(");
	debugOutput(yytext);
	debugOutput(")");	
	updateLocation();
}
. {
	std::cerr<<"ERROR IN FLEX:"<<yytext[0]<<std::endl;
  }
%%
//Empty
