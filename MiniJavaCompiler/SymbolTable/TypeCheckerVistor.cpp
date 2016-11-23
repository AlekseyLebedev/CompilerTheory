#include "TypeCheckerVistor.h"
#include "Table.h"
#include <set>
#include <memory>

extern std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;
namespace SymbolTable {
	typedef AbstractTreeGenerator::TStandardType stdtype;

	CTypeCheckerVistor::CTypeCheckerVistor(CTable classes_):classes(classes_), state(None),lookingType(-4)
	{
	}


	CTypeCheckerVistor::~CTypeCheckerVistor()
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CArgument * const argument)
	{
		// 4. Argument definition
			// b. Availability of classes
		int type = argument->GetType()->GetType();
		if( type >= 0 ) {			
			try {
				classes.GetClass( type );
			}
			catch( std::string& e ) {
				// no such class;
				throw;
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CArgumentList * const args)
	{			
		args->GetArgument()->Accept( this );
		if( args->GetArgumentList() != nullptr ) {
			args->GetArgumentList()->Accept( this );
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CAssignmentListStatement * const statements )
	{
		std::shared_ptr<AbstractTreeGenerator::CIdExpression> assignexp = statements->GetIdExpression();
		std::shared_ptr<AbstractTreeGenerator::IExpression> indexexp = statements->GetExpressionFirst();
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = statements->GetExpressionSecond();
		
		state = LookingType;
		lookingType = stdtype::ST_Int;
		indexexp->Accept( this );

		CVariableInfo varinfo;
		if( currentMethod != nullptr ) {
			varinfo = currentMethod->GetVarInfo( assignexp->GetName() );
		} else {
			varinfo = currentClass->GetVarInfo( assignexp->GetName() );
		}			
		
		int vartype = varinfo.GetType();
		state = LookingType;
		lookingType = vartype;
		exp->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CAssignmentStatement * const statement)
	{
		// 7. Assignment
			// b. both expressions have the same type
		int id = statement->GetIdExpression()->GetName();

		CVariableInfo varinfo;

		if( currentMethod != nullptr ) {
			varinfo = currentMethod->GetVarInfo( id );
		} else {
			varinfo = currentClass->GetVarInfo( id );
		}
		int vartype = varinfo.GetType();
		state = LookingType;
		lookingType = vartype;
		statement->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassDeclaration * const CClass)
	{

		// 3.  method definition
			// a. Multiple method definition
		// maybe it's good to check in first run
		int id = CClass->GetIdExpression()->GetName();
		currentClass = std::make_shared<CClassInfo>(classes.GetClassInfo( id ));
		currentMethod = nullptr;
		std::vector<CMethodInfo> methods_infos = currentClass->GetMethods();
		std::set<CMethodInfo> mi_set;
		for( auto methods_info : methods_infos ) {
			mi_set.insert( methods_info );
		}
		if( methods_infos.size() != mi_set.size() ) {
			throw "Multiple method definition";
		}

		// Class Extend checking(simple)
		int class_extend = CClass->GetClassExtend()->GetIdExpression()->GetName();
		CClassInfo extend_info = classes.GetClassInfo( class_extend );
		if( id == extend_info.GetExtend() ) {
			throw "circular dependency";
		}

		CClass->GetMethodDeclarationList()->Accept( this );
		CClass->GetVarDeclarationList()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassDeclarationList * const classlist )
	{			
		classlist->GetClassDeclaration()->Accept( this );
		if( classlist->GetClassDeclarationList() != nullptr ) {
			classlist->GetClassDeclarationList()->Accept( this );
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassExtend * const classExtend)
	{	
		int id = classExtend->GetIdExpression()->GetName();
		
		try {
			classes.GetClassInfo( id );
		}
		catch( std::string& e ) {
			// no such class;
			throw;
		}		
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CCompoundStatement * const statement)
	{		
		statement->GetStatementList()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CConstructorExpression * const expression )
	{
		// 12. new
			// a.
		int id = expression->GetIdExpression()->GetName();
		CTable classes;
		try {
			classes.GetClass( id );
		}
		catch (std::string& e) {
			// no such class
			throw;
		}
		if( lookingType < 0 ) {
			throw "Incorrect return value: basic type required but method returns custom";
		} else {
			if( classes.GetClass( id ) != lookingType ) {
				throw "Incorrect return value: no such class";
			} else {
				lookingType = -4;
				state = None;
			}
		}		
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CExpressionList * const expressionlist)
	{		
		expressionlist->GetExpression()->Accept( this );
		if( expressionlist->GetExpressionList() != nullptr ) {
			expressionlist->GetExpressionList()->Accept( this );
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIdExpression * const expression)
	{
		int id = expression->GetName();
		if( state != None ) {
			CVariableInfo varinfo;

			if( currentMethod != nullptr ) {
				varinfo = currentMethod->GetVarInfo( id );
			} else {
				varinfo = currentClass->GetVarInfo( id );
			}
			int vartype = varinfo.GetType();
			if( vartype != lookingType ) {
				throw "Incorrect return value";
			} else {
				state = None;
				lookingType = -4;
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIndexExpression * const expression )
	{
		// 10. IndexExpression
			// a. must be int
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = expression->GetExpressionSecond();
		state = LookingType;
		
		lookingType = stdtype::ST_Int;
		exp->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CLastExpressionList * const expression)
	{
		expression->GetExp()->Accept( this );
		if( expression->GetExpression() != nullptr ) {
			expression->GetExpression()->Accept( this );
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CLengthExpression * const expression)
	{
		state = LookingType;
		
		lookingType = stdtype::ST_Intlist;
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CListConstructorExpression * const expression )
	{
		state = LookingType;		
		lookingType = stdtype::ST_Int;
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMainClass * const cclass)
	{
		cclass->GetStatement()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMethodDeclaration * const method)
	{
		// 3. Method definition
			// b. Availability of classes
		if( method->GetType()->GetType() >= 0 ) {			
			int id = method->GetType()->GetType();			
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
		int id = method->GetIdExpression()->GetName();
		CMethodInfo methodinfo = currentClass->GetMethod(id);		
		std::vector<int> args = methodinfo.GetArguments();
		std::set<int> args_set;
		for( auto arg : args ) {
			args_set.insert( arg );
		}
		if( args.size() != args_set.size() ) {
			throw "Multiple argument definition";
		}
		currentMethod = std::make_shared<CMethodInfo>(methodinfo);
		method->GetVarDeclarationList()->Accept( this );
		method->GetStatementList()->Accept( this );

		// Return value type check
		int type = method->GetType()->GetType();
		state = LookingType;
		lookingType = type;
		method->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMethodDeclarationList * const methods)
	{
		methods->GetMethodDeclaration()->Accept( this );
		if( methods->GetMethodDeclarationList() != nullptr ) {
			methods->GetMethodDeclarationList()->Accept( this );
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CNegationExpression * const expression)
	{
		state = LookingType;
		lookingType = stdtype::ST_Bool;
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CNumberExpr * const expression)
	{
		if( state == LookingType ) {
			if( lookingType == stdtype::ST_Int ) {
				// OK
				state = None;
				lookingType;
			} else {
				throw "Incorrect type";
			}
		}		
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::COperationExpression * const operation)
	{
		// checking result type
		typedef AbstractTreeGenerator::COperationExpression::TOperationType OperationType;
		switch( lookingType ) {
			case stdtype::ST_Bool: {
				switch( operation->GetOperationType() ) {
					case OperationType::And: {
						state = LookingType;
						lookingType = stdtype::ST_Bool;
						break;
					}
					case OperationType::Less: {
						state = LookingType;
						lookingType = stdtype::ST_Bool;
						break;
					}
					case OperationType::Mod: {
						state = LookingType;
						lookingType = stdtype::ST_Bool;
						break;
					}
					case OperationType::Or: {
						state = LookingType;
						lookingType = stdtype::ST_Bool;
						break;
					}
					default: {
						throw "Incorrect return value: bool required but method returns int";
					}							
				}
				break;			
			}
			case stdtype::ST_Int: {
				switch( operation->GetOperationType() ) {
					case OperationType::Plus: {
						state = LookingType;
						lookingType = stdtype::ST_Int;
						break;
					}
					case OperationType::Minus: {
						state = LookingType;
						lookingType = stdtype::ST_Int;
						break;
					}
					case OperationType::Times: {
						state = LookingType;
						lookingType = stdtype::ST_Int;
						break;
					}
					case OperationType::Divide: {
						state = LookingType;
						lookingType = stdtype::ST_Int;
						break;
					}
					default: {
						throw "Incorrect return value: int required but method returns bool";
						break;
					}
				}
				break;
			}	
			default: {
				throw "Incorrect return type";
				break;
			}
		}

		// 8. - 9. logical and numerical expressions
		operation->GetLeftOperand()->Accept( this );
		operation->GetRightOperand()->Accept( this );

	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CParenExpression * const expression)
	{
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CPreconditionStatement * const condition)
	{
		// 5. if-while statement
			// a. exp is boolean
		state = LookingType;
		lookingType = stdtype::ST_Bool;
		condition->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CPrintStatement * const statement)
	{
		// 6. print statement
			// a. exp is int
		state = LookingType;
		lookingType = stdtype::ST_Int;
		statement->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CProgram * const program)
	{
		program->GetClassDeclarationList()->Accept( this );
		program->GetMainClass()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CStatementList * const statement)
	{
		statement->GetStatement()->Accept( this );
		statement->GetStatementList()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CBasicType * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIdType * const idType)
	{
		// 2.  Variable definition
			// a. Availability of classes
		int id = idType->GetIdExpression()->GetName();	
		try {
			classes.GetClassInfo( id );
		} catch (std::string& e){
			// no such class;
			throw;
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CVarDeclaration * const var)
	{
		std::shared_ptr<AbstractTreeGenerator::IType> type = var->GetType();
		int id = var->GetIdExpression()->GetName();
		CVariableInfo varinfo;

		if( currentMethod != nullptr ) {
			varinfo = currentMethod->GetVarInfo( id );
		} else {
			varinfo = currentClass->GetVarInfo( id );
		}
		int vartype = varinfo.GetType();
		if( vartype >= 0 ) {			
			int id = vartype;				
			if( lookingType != classes.GetClass( id ) ) {
				throw "Incorrect return value: no such class";
			} else {
				state = None;
				lookingType = -4;
			}
		} 

	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CVarDeclarationList * const vars)
	{
		vars->GetVarDeclaration()->Accept( this );
		if ( vars->GetVarDeclarationList() != nullptr )
			vars->GetVarDeclarationList()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CTrueExpression * const )
	{
		// Checking return value type
		if( state == LookingType ) {
			if( lookingType == stdtype::ST_Bool ) {
				// OK
				state = None;
				lookingType = -4;
			} else {
				"Incorrect return value: method returns bool";
			}
		}		
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CFalseExpression * const )
	{
		// Checking return value type
		if( state == LookingType ) {
			if( lookingType == stdtype::ST_Bool ) {
				// OK
				state = None;
				lookingType = -4;
			} else {
				"Incorrect return value: method returns bool";
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CGetFieldExpression * const expression)
	{
		int id = expression->GetIdExpression()->GetName();
		CVariableInfo varinfo;
		
		varinfo = currentClass->GetVarInfo( id );		
		int vartype = varinfo.GetType();
		if( vartype >= 0 ) {
			int id = vartype;
			CTable classes;
			if( lookingType != classes.GetClass( id ) ) {
				throw "Incorrect return value: no such class";
			} else {
				// OK
				state = None;
				lookingType = -4;
			}
		}
		//expression->GetExpression();
		// TODO: so complex case
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CConditionStatement * const condition )
	{
		// 5. if-while statement
		// a. exp is boolean
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = condition->GetExpression();
		state = LookingType;
		lookingType = stdtype::ST_Bool;
		exp->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CThisExpression * const expression )
	{
		//expression
		// TODO: so complex case
	}
}