// MiniJavaCompiler.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cassert>
#include "Graphwiz\GraphvizLauncher.h"
#include "Graphwiz\DotOutputVisitor.h"
#include "AbstractTreeGenerator\StringTable.h"
#include "SymbolTable\FillTableVisitor.h"
#include "SymbolTable\TypeCheckerVistor.h"
#include "IRTree\IRTBuilderVisitor.h"
#include "IRTree\IRTreeVisitor.h"

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
		int fileIndex = 0;
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
				// AST
				GraphvizOutput::CGraphvizLauncher::Launch<GraphvizOutput::CDotOutputVisitor,
					AbstractTreeGenerator::CProgram>( root.get(), fileIndex++, L"AST" );
			}
			catch( std::exception* e ) {
				std::cerr << e->what() << std::endl;
			}
			try {
				IRTree::IRTBuilderVisitor irtree( &fillTable.GetTable() );
				irtree.visit( root.get() );
				std::wstringstream headerBuilder;
				std::shared_ptr<IRTree::CCodeFragment> currentCodeFragment = irtree.GetCode();
				while( currentCodeFragment != 0 ) {
					headerBuilder << argv[i] << ", " << reinterpret_cast<size_t>(currentCodeFragment.get());
					std::wcout << L"Printing: " << headerBuilder.str() << std::endl;
					GraphvizOutput::CGraphvizLauncher::Launch<IRTree::IRTreeVisitor, const IRTree::IRTStatement>(
						currentCodeFragment->GetTree().get(), fileIndex++, headerBuilder.str() );
					currentCodeFragment = currentCodeFragment->GetNext();
					headerBuilder.str( L"" );
				}
			}
			catch( std::exception* e ) {
				std::cerr << e->what() << std::endl;

			}

		}
	}
	return 0;
}

