#include "TypeCheckerVistor.h"
#include "Table.h"
#include <set>
#include <memory>

extern std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;
namespace SymbolTable {

	CTypeCheckerVistor::CTypeCheckerVistor()
	{
	}


	CTypeCheckerVistor::~CTypeCheckerVistor()
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CArgument * const argument)
	{
		argument->
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CArgumentList * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CAssignmentListStatement * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CAssignmentStatement * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassDeclaration * const CClass)
	{
		// 3.  method definition
			// a. Multiple method definition
		// maybe it's good to check in first run
		CClass->GetIdExpression()->GetName();
		CTable classes;		
		CClassInfo clinfo = classes.GetClassInfo( id );
		std::vector<CMethodInfo> methods_infos = clinfo.GetMethods();		
		std::set<CMethodInfo> mi_set;
		for( auto methods_info : methods_infos ) {
			mi_set.insert( methods_info );
		}
		if( methods_infos.size() != mi_set.size() ) {
			throw "Multiple method definition";
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassDeclarationList * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassExtend * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CCompoundStatement * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CConstructorExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CExpressionList * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIdExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIndexExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CLastExpressionList * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CLengthExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CListConstructorExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMainClass * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMethodDeclaration * const method)
	{
		// 3. Method definition
			// b. Availability of classes
		if( method->GetType()->GetType() == "POD" ) {
			std::shared_ptr<AbstractTreeGenerator::CIdType> type =
				std::dynamic_pointer_cast<AbstractTreeGenerator::CIdType>(method->GetType());
			int id = type->GetIdExpression()->GetName();
			CTable classes;
			try {
				classes.GetClassInfo( id );
			}
			catch( std::string& e ) {
				// no such class;
				throw;
			}
		}

		// 4.  Arguments definition
			// a. Multiple arguments definition
		// maybe it's good to check in first run
		method->GetIdExpression()->GetName();
		CMethodInfo methodinfo;
		std::vector<int> args = methodinfo.GetArguments();
		std::set<int> args_set;
		for( auto arg : args ) {
			args_set.insert( arg );
		}
		if( args.size() != args_set.size() ) {
			throw "Multiple argument definition";
		}
		
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMethodDeclarationList * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CNegationExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CNumberExpr * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::COperationExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CParenExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CPreconditionStatement * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CPrintStatement * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CProgram * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CStatementList * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CBasicType * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIdType * const idType)
	{
		// 2.  Variable definition
			// a. Availability of classes
		int id = idType->GetIdExpression()->GetName();	
		CTable classes;
		try {
			classes.GetClassInfo( id );
		} catch (std::string& e){
			// no such class;
			throw;
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CVarDeclaration * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CVarDeclarationList * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CTrueExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CFalseExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CGetFieldExpression * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CConditionStatement * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CThisExpression * const )
	{
	}

}