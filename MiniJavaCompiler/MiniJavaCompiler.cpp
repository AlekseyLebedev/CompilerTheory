// MiniJavaCompiler.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "AbstractTreeGenerator\GraphvizLauncher.h"

int yyparse();
extern FILE* yyin, *yyout;
void yyrestart( FILE * input_file );
extern int row, col;

AbstractTreeGenerator::CProgram* rootNode;

int main( int argc, char** argv )
{
	if( argc == 0 ) {
		yyparse();
	} else {
		std::stringstream buffer;
		for( size_t i = 1; i < argc; i++ ) {
			row = 1;
			col = 1;
			buffer << argv[i];
			std::cout << std::endl << "Processing: " << buffer.str() << std::endl;
			yyin = fopen( buffer.str().c_str(), "r" );
			buffer << "-out.txt";
			yyrestart( yyin );
			yyparse();
			fclose( yyin );
			buffer.str( "" );
			std::shared_ptr<AbstractTreeGenerator::CProgram> root( rootNode ); //set from bison
			GraphvizOutput::CGraphvizLauncher::Launch(root.get());
		}
	}
	return 0;
}

