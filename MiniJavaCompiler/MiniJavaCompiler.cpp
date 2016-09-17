// MiniJavaCompiler.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <FlexLexer.h>

//int yylex();
//FILE* yyin, *yyout;

int main(int argc, char** argv)
{
	if (argc == 0) {
		//yylex();
		yyFlexLexer lexer;
		lexer.switch_streams(&std::cin, &std::cout);
		lexer.yylex();
	}
	else {
		std::stringstream buffer;
		for (size_t i = 1; i < argc; i++)
		{
			buffer << argv[i];
			std::cout << "Processing: " << buffer.str() << std::endl;
			std::ifstream in(buffer.str());
			buffer << "-out.txt";
			std::cout << "Out path: " << buffer.str() << std::endl;
			std::ofstream out(buffer.str().c_str());
			yyFlexLexer lexer;
			lexer.switch_streams(&in, &out);
			lexer.yylex();
			in.close();
			out.flush();
			out.close();
			buffer.clear();
		}
	}
	return 0;
}

