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
std::ostream* globalOut = &std::cout;

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
			std::cout << "Processing: " << buffer.str() << std::endl;
			yyin = fopen(buffer.str().c_str(), "r");
			buffer << "-out.txt";
			std::cout << "Out path: " << buffer.str() << std::endl;
			std::ofstream fout(buffer.str());
			globalOut = &fout;
			yyrestart(yyin);
			yylex();
			fclose(yyin);
			fout.close();
			buffer.str("");
		}
	}
	return 0;
}

