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
		//std::cout << "{" << row << "," << col << "}";
	}
	col += strlen(yytext);
}

void newLine(){
	++row;
	col=1;
	//std::cout<<"\n";
}

void debugOutput(const char* text){
	//std::cout << text;
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
	return T_extends;
}
public {
	debugOutput("PUBLIC");
	updateLocation();
	return T_public;
}
protected {
	debugOutput("PROTECTED");
	updateLocation();
	//return T_protected;
}
private {
	debugOutput("PRIVATE");
	updateLocation();
	return T_private;
}
static {
	debugOutput("STATIC");
	updateLocation();
	return T_static;
}
void {
	debugOutput("VOID");
	updateLocation();
	return T_void;
}
main {
	debugOutput("MAIN");
	updateLocation();
	return T_main;
}
int {
	debugOutput("INT");
	updateLocation();
	return T_int;
}
char {
	debugOutput("CHAR");
	updateLocation();
	//return T_char;
}
boolean {
	debugOutput("BOOLEAN");
	updateLocation();
	return T_boolean;
}
String {
	debugOutput("STRING");
	updateLocation();
	return T_string;
}
if {
	debugOutput("IF");
	updateLocation();
	return T_if;
}
else {
	debugOutput("ELSE");
	updateLocation();
	return T_else;
}
while {
	debugOutput("WHILE");
	updateLocation();
	return T_while;
}
return {
	debugOutput("RETURN");
	updateLocation();
	return T_return;
}
this {
	debugOutput("THIS");
	updateLocation();
	return T_this;
}
new {
	debugOutput("NEW");
	updateLocation();
	return T_new;
}
System.out.println {
	debugOutput("SOP");
	updateLocation();
	return T_sop;
}
length {
	debugOutput("LENGTH");
	updateLocation();
	return T_length;
}
true {
	debugOutput("TRUE");
	updateLocation();
	return T_true;
}
false {
	debugOutput("FALSE");
	updateLocation();
	return T_false;
}
";" {
	debugOutput("SEMI");
	updateLocation();
	return T_semi;
}
{LETTER}({DIGIT}|{LETTER})* {
	yylval.str_val = yytext;	
	debugOutput("ID(");
	debugOutput(yytext);
	debugOutput(")");	
	updateLocation();
	return T_ID;
}
"(" {
	debugOutput("LPAREN");	
	updateLocation();
	return T_lparen;
}
")" {
	debugOutput("RPAREN");	
	updateLocation();
	return T_rparen;
}
"[" {
	debugOutput("LBRACKET");	
	updateLocation();
	return T_lbracket;
}
"]" {
	debugOutput("RBRACKET");	
	updateLocation();
	return T_rbracket;
}
"{" {
	debugOutput("LBRACE");	
	updateLocation();
	return T_lbrace;
}
"}" {
	debugOutput("RBRACE");	
	updateLocation();
	return T_rbrace;
}
"*" {
	debugOutput("STAR");	
	updateLocation();
	return T_times;
}
"%" {
	debugOutput("%");
	updateLocation();
	return T_mod;
}
"\n" {
	newLine();
}
"!" {
	debugOutput("NOT");	
	updateLocation();
	return T_not;
}
"<" {
	debugOutput("LESS");	
	updateLocation();
	return T_less;
}
"=" {
	debugOutput("EQUAL");	
	updateLocation();
	return T_equal;
}
"+" {
	debugOutput("PLUS");	
	updateLocation();
	return T_plus;
}
"-" {
	debugOutput("MINUS");	
	updateLocation();
	return T_minus;
}
"&&" {
	debugOutput("&&");	
	updateLocation();
	return T_and;
}
"||" {
	debugOutput("||");	
	updateLocation();
	return T_or;
}
"," {
	debugOutput("COMMA");	
	updateLocation();
	return T_comma;
}
"." {
	debugOutput(".");	
	updateLocation();
	return T_dot;
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
({DIGIT})({DIGIT})* {
	yylval.int_val = atoi(yytext);
	debugOutput("NUM(");
	debugOutput(yytext);
	debugOutput(")");	
	updateLocation();
	return T_NUM;
}
. {
	std::cerr<<"ERROR IN FLEX:"<<yytext[0]<<std::endl;
  }
%%
//Empty
