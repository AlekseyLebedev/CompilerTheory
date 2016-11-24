// MiniJavaCompiler.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "AbstractTreeGenerator\GraphvizLauncher.h"
#include "AbstractTreeGenerator\StringTable.h"
#include <assert.h>
#include "SymbolTable\FillTableVisitor.h"
#include "SymbolTable\TypeCheckerVistor.h"

int yyparse();
extern FILE* yyin, *yyout;
void yyrestart( FILE * input_file );
extern int row, col;

std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;

AbstractTreeGenerator::CProgram* rootNode;

int main( int argc, char** argv )
{
	if( argc == 0 ) {
		yyparse();
	} else {
		std::stringstream buffer;
		for( size_t i = 1; i < argc; i++ ) {
			glabalStringTable = std::make_shared<AbstractTreeGenerator::CStringTable>();
			assert( glabalStringTable->insert( "main" ) == 0 );
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
			SymbolTable::CFillTableVisitor fillTable;
			fillTable.visit( root.get() );
			try {
				SymbolTable::CTypeCheckerVistor typeChecker( fillTable.GetTable() );
				typeChecker.visit( root.get() );
				GraphvizOutput::CGraphvizLauncher::Launch( root.get(), i );
			}
			catch( std::exception e ) {
				std::cerr << e.what() << std::endl;
			}
		}
	}
	return 0;
}

