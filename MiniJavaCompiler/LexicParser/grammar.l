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

void newLine(){
	++row;
	col=1;
	std::cout<<"\n";
}
%}

DIGIT [0-9]
LETTER [_a-zA-Z]

%%


"\""({DIGIT}|{LETTER}|"."|"\\")*"\"" {
	std::cout << "STR(" << yytext << ")";	
	updateLocation();
}
"/*"((("*"[^/])?)|[^*])*"*/" { 
	//Comment
	updateLocation(false);
}
"//"(.)*"\n" {
	//Comment
	newLine();
}
class {
	std::cout << "CLASS";
	updateLocation();
}
public {
	std::cout << "PUBLIC";
	updateLocation();
}
protected {
	std::cout << "PROTECTED";
	updateLocation();
}
private {
	std::cout << "PRIVATE";
	updateLocation();
}
static {
	std::cout << "STATIC";
	updateLocation();
}
void {
	std::cout << "VOID";
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
boolean {
	std::cout << "BOOLEAN";
	updateLocation();
}
String {
	std::cout << "STRING";
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
while {
	std::cout << "WHILE";
	updateLocation();
}
return {
	std::cout << "RETURN";
	updateLocation();
}
this {
	std::cout << "THIS";
	updateLocation();
}
new {
	std::cout << "NEW";
	updateLocation();
}
";" {
	std::cout << " SEMI";
	updateLocation();
}
{LETTER}({DIGIT}|{LETTER})* {
	std::cout << "ID(" << yytext << ")";	
	updateLocation();
}
"(" {
	std::cout << " LPAREN";	
	updateLocation();
}
")" {
	std::cout << " RPAREN";	
	updateLocation();
}
"[" {
	std::cout << "LBRACKET";	
	updateLocation();
}
"]" {
	std::cout << "RBRACKET";	
	updateLocation();
}
"*" {
	std::cout << "STAR";	
	updateLocation();
}
"\n" {	
	row++;
	newLine();
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
"<" {
	std::cout << "LESS";	
	updateLocation();
}
"=" {
	std::cout << "EQUAL";	
	updateLocation();
}
"+" {
	std::cout << "PLUS";	
	updateLocation();
}
"-" {
	std::cout << "MINUS";	
	updateLocation();
}
"&" {
	std::cout << "&";	
	updateLocation();
}
"|" {
	std::cout << "|";	
	updateLocation();
}
"," {
	std::cout << "COMMA";	
	updateLocation();
}
"." {
	std::cout << ".";	
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
"\r" {	
	std::cout << yytext;
	updateLocation(false);
}
({DIGIT}|"-"{DIGIT})({DIGIT})* {
	std::cout << "NUM(" << yytext << ")";	
	updateLocation();
}
. { return yytext[0]; }
%%
//Empty
