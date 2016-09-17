// MiniJavaCompiler.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

int yylex();
extern FILE* yyin, *yyout;
void yyrestart(FILE * input_file);

int main(int argc, char** argv)
{
	if (argc == 0) {
		yylex();
	}
	else {
		std::stringstream buffer;
		for (size_t i = 1; i < argc; i++)
		{

			buffer << argv[i];
			std::cout << std::endl << "Processing: " << buffer.str() << std::endl;
			yyin = fopen(buffer.str().c_str(), "r");
			buffer << "-out.txt";
			yyrestart(yyin);
			yylex();
			fclose(yyin);
			buffer.str("");
		}
	}
	return 0;
}

