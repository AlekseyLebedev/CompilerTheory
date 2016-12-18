#include "TypeCheckerVistor.h"
#include "Table.h"
#include <set>
#include <memory>
#include "TypeException.h"
#include <vector>
#include <iostream>

extern std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;
namespace SymbolTable {
	typedef AbstractTreeGenerator::TStandardType stdtype;

	CTypeCheckerVistor::CTypeCheckerVistor( CTable classes_ ) :
		state( TS_None ), lookingType( stdtype::ST_Void ), classes( classes_ ), methodExist( false )
	{

	}


	CTypeCheckerVistor::~CTypeCheckerVistor()
	{
	}


	void CTypeCheckerVistor::visitChild( AbstractTreeGenerator::INode* node )
	{
		if( node != 0 ) {
			node->Accept( this );
		}
	}

	CMethodInfo CTypeCheckerVistor::checkGetField( int varName, AbstractTreeGenerator::IExpression * const expression, int id )
	{
		CVariableInfo varinfo;
		bool assign[4] = { false, false, false, false };
		try {
			varinfo = currentMethod.GetVarInfo( varName, expression );
			assign[0] = true;
		}
		catch( ... ) {

		}
		try {
			varinfo = currentMethod.GetArgInfo( varName, expression );
			assign[1] = true;
		}
		catch( ... ) {

		}
		try {
			varinfo = currentClass.GetVarInfo( varName, expression );
			assign[2] = true;
		}
		catch( ... ) {

		}

		int extend = currentClass.GetExtend();
		while( extend != CClassInfo::NothingExtend ) {
			CClassInfo extendClass = classes.GetClassInfo( extend, expression );
			try {
				varinfo = extendClass.GetVarInfo( varName, expression );
				assign[3] = true;
			}
			catch( std::exception* e ) {
			}
			if( assign[3] ) {
				break;
			}
			extend = extendClass.GetExtend();
		}


		int sum = 0;
		for( int i = 0; i < 4; i++ ) {
			sum += assign[i];
		}
		if( sum == 0 ) {
			throw new CTypeException( expression->GetCol(), expression->GetRow(),
				"No such variable" );
		} else if( sum > 1 ) {
			throw new CTypeException( expression->GetCol(), expression->GetRow(),
				"Multiple declaration" );
		}
		int type = varinfo.GetType();
		return checkMethodExists( type, id, expression );
	}

	CMethodInfo CTypeCheckerVistor::checkMethodExists( int classname, int id, const AbstractTreeGenerator::IExpression* expression )
	{
		int currentClass = classname;
		while( currentClass != CClassInfo::NothingExtend ) {
			CClassInfo cl = classes.GetClassInfo( currentClass, expression );
			try {
				return cl.GetMethodInfo( id, expression );
			}
			catch( ... ) {
				currentClass = cl.GetExtend();
			}
		}
		throw new CTypeException( expression->GetCol(), expression->GetRow(), "Method doesn't exist." );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CArgument * const argument )
	{
		// 4. Argument definition
			// b. Availability of classes
		int type = argument->GetType()->GetType();
		if( type >= 0 ) {
			try {
				classes.GetClassInfo( type, argument );
			}
			catch( std::exception& e ) {
				// no such class;
				throw;
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CArgumentList * const args )
	{
		args->GetArgument()->Accept( this );
		visitChild( args->GetArgumentList().get() );

	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CAssignmentListStatement * const statement )
	{
		std::shared_ptr<AbstractTreeGenerator::CIdExpression> assignexp = statement->GetIdExpression();
		std::shared_ptr<AbstractTreeGenerator::IExpression> indexexp = statement->GetExpressionFirst();
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = statement->GetExpressionSecond();

		// Checking index type is int

		TypeCheckerState oldState = state;
		state = TS_LookingType;
		lookingType = stdtype::ST_Int;
		indexexp->Accept( this );
		state = oldState;

		// Trying getting variable type
		CVariableInfo varinfo;
		if( methodExist ) {
			bool assign = false;
			try {
				varinfo = currentMethod.GetVarInfo( assignexp->GetName(), statement );
				assign = true;
			}
			catch( std::exception* e ) {
				varinfo = currentClass.GetVarInfo( assignexp->GetName(), statement );
			}
			if( assign ) {
				bool bothassign = false;
				try {
					currentClass.GetVarInfo( assignexp->GetName(), statement );
					bothassign = true;
				}
				catch( ... ) {

				}
				if( bothassign ) {
					throw new CTypeException( statement->GetCol(), statement->GetRow(),
						"Multiple definition" );
				}
			}
		} else {
			varinfo = currentClass.GetVarInfo( assignexp->GetName(), statement );
		}
		int vartype = varinfo.GetType();
		if( vartype == stdtype::ST_Intlist ) {
			TypeCheckerState oldState = state;
			state = TS_LookingType;
			lookingType = stdtype::ST_Int;
			exp->Accept( this );
			state = oldState;
		} else {
			throw new CTypeException( statement->GetCol(), statement->GetRow(),
				"Not Int list" );
		}

	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CAssignmentStatement * const statement )
	{
		// 7. Assignment
			// b. both expressions have the same type
		int id = statement->GetIdExpression()->GetName();
		CVariableInfo varinfo;
		bool assign[3] = { false,false, false };
		if( methodExist ) {
			try {
				varinfo = currentMethod.GetVarInfo( id, statement );
				assign[0] = true;
			}
			catch( ... ) {

			}
		}
		try {
			varinfo = currentClass.GetVarInfo( id, statement );
			assign[1] = true;
		}
		catch( ... ) {

		}

		int extend = currentClass.GetExtend();
		while( extend != CClassInfo::NothingExtend ) {
			CClassInfo extendClass = classes.GetClassInfo( extend, statement );
			try {
				varinfo = extendClass.GetVarInfo( id, statement );
				assign[2] = true;
			}
			catch( std::exception* e ) {
				extend = extendClass.GetExtend();
			}
			if( assign[2] ) {
				break;
			}
		}

		int sum = 0;
		for( int i = 0; i < 3; i++ ) {
			sum += assign[i];
		}
		if( sum == 0 ) {
			throw new CTypeException( statement->GetCol(), statement->GetRow(),
				"No such variable" );
		} else if( sum > 1 ) {
			throw new CTypeException( statement->GetCol(), statement->GetRow(),
				"Multiple declaration" );
		}

		int vartype = varinfo.GetType();
		TypeCheckerState oldState = state;
		state = TS_LookingType;
		lookingType = vartype;
		statement->GetExpression()->Accept( this );
		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassDeclaration * const CClass )
	{

		// 3.  method definition
			// a. Multiple method definition
		// maybe it's good to check in first run
		int id = CClass->GetIdExpression()->GetName();
		currentClass = classes.GetClassInfo( id, CClass );
		currentClassId = id;
		methodExist = false;
		std::vector<CMethodInfo> methods_infos = currentClass.GetMethods();
		if( methods_infos.size() != currentClass.GetUniqueMethodsCount() ) {
			throw new CTypeException( CClass->GetCol(), CClass->GetRow(), "Multiple method definition" );
		}

		// Class Extend checking
		int current = id;
		std::vector<int> lastId;
		while( current != CClassInfo::NothingExtend ) {
			for( size_t i = 0; i < lastId.size(); i++ ) {
				if( lastId[i] == current ) {
					throw new CTypeException( CClass->GetCol(), CClass->GetRow(), "Circular dependency in extend class" );
				}
			}
			lastId.push_back( current );
			current = classes.GetClassInfo( current, CClass ).GetExtend();
		}

		visitChild( CClass->GetMethodDeclarationList().get() );
		visitChild( CClass->GetVarDeclarationList().get() );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassDeclarationList * const classlist )
	{
		classlist->GetClassDeclaration()->Accept( this );
		visitChild( classlist->GetClassDeclarationList().get() );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassExtend * const classExtend )
	{
		int id = classExtend->GetIdExpression()->GetName();

		try {
			classes.GetClassInfo( id, classExtend );
		}
		catch( std::exception& e ) {
			// no such class;
			throw;
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CCompoundStatement * const statement )
	{
		statement->GetStatementList()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CConstructorExpression * const expression )
	{
		// 12. new
			// a.
		int id = expression->GetIdExpression()->GetName();
		try {
			classes.GetClassInfo( id, expression );
		}
		catch( std::exception& e ) {
			// no such class
			throw;
		}
		if( lookingType < 0 ) {
			throw new CTypeException( expression->GetCol(), expression->GetRow(),
				"Incorrect return value: basic type required but method returns custom" );
		} else {
			if( id != lookingType ) {
				throw new CTypeException( expression->GetCol(), expression->GetRow(),
					"Incorrect return value: no such class" );
			} else {
				lookingType = -4;
				state = TS_None;
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CExpressionList * const expressionlist )
	{
		expressionlist->GetExpression()->Accept( this );
		visitChild( expressionlist->GetExpressionList().get() );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIdExpression * const expression )
	{
		int id = expression->GetName();
		if( state != TS_None ) {
			CVariableInfo varinfo;
			bool assign[4] = { false, false, false, false };
			if( methodExist ) {
				try {
					varinfo = currentMethod.GetVarInfo( id, expression );
					assign[0] = true;
				}
				catch( ... ) {

				}
			}

			try {
				varinfo = currentMethod.GetArgInfo( id, expression );
				assign[1] = true;
			}
			catch( ... ) {

			}
			try {
				varinfo = currentClass.GetVarInfo( id, expression );
				assign[2] = true;
			}
			catch( ... ) {

			}

			int extend = currentClass.GetExtend();
			while( extend != CClassInfo::NothingExtend ) {
				CClassInfo extendClass = classes.GetClassInfo( extend, expression );
				try {
					varinfo = extendClass.GetVarInfo( id, expression );
					assign[3] = true;
				}
				catch( std::exception* e ) {
					extend = extendClass.GetExtend();
				}
				if( assign[3] ) {
					break;
				}
			}

			int sum = 0;
			for( int i = 0; i < 4; i++ ) {
				sum += assign[i];
			}
			if( sum == 0 ) {
				throw new CTypeException( expression->GetCol(), expression->GetRow(),
					"No such variable" );
			} else if( sum > 1 ) {
				throw new CTypeException( expression->GetCol(), expression->GetRow(),
					"Multiple declaration" );
			}

			if( state == TS_LookingType ) {
				int vartype = varinfo.GetType();
				bool f;
				while( vartype != lookingType ) {
					int extend = classes.GetClassInfo( vartype, expression ).GetExtend();
					if( extend == CClassInfo::NothingExtend ) {
						throw new CTypeException( expression->GetCol(), expression->GetRow(),
							"Incorrect return value" );
					} else {
						vartype = extend;
					}
				}
				state = TS_None;
				lookingType = -4;
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIndexExpression * const expression )
	{
		// 10. IndexExpression
			// a. must be int
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = expression->GetExpressionSecond();

		TypeCheckerState oldState = state;
		state = TS_LookingType;

		lookingType = stdtype::ST_Int;
		exp->Accept( this );
		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CLastExpressionList * const expression )
	{
		expression->GetExp()->Accept( this );
		visitChild( expression->GetExpression().get() );

	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CLengthExpression * const expression )
	{

		TypeCheckerState oldState = state;
		state = TS_LookingType;

		lookingType = stdtype::ST_Intlist;
		expression->GetExpression()->Accept( this );
		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CListConstructorExpression * const expression )
	{
		TypeCheckerState oldState = state;
		state = TS_LookingType;
		lookingType = stdtype::ST_Int;
		state = oldState;
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMainClass * const cclass )
	{
		cclass->GetStatement()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMethodDeclaration * const method )
	{
		// 3. Method definition
			// b. Availability of classes
		if( method->GetType()->GetType() >= 0 ) {
			int id = method->GetType()->GetType();
			try {
				classes.GetClassInfo( id, method );
			}
			catch( std::exception& e ) {
				// no such class;
				throw;
			}
		}

		// 4.  Arguments definition
			// a. Multiple arguments definition
		// maybe it's good to check in first run
		int id = method->GetIdExpression()->GetName();
		currentMethod = currentClass.GetMethodInfo( id, method );
		methodExist = true;
		if( currentMethod.GetAllArgsCount() != currentMethod.GetUniqueArgsCount() ) {
			throw new CTypeException( method->GetCol(), method->GetRow(), "Multiple argument definition" );
		}

		visitChild( method->GetVarDeclarationList().get() );
		visitChild( method->GetStatementList().get() );

		// Return value type check
		int type = method->GetType()->GetType();
		TypeCheckerState oldState = state;
		state = TS_LookingType;
		lookingType = type;
		method->GetExpression()->Accept( this );
		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMethodDeclarationList * const methods )
	{
		methods->GetMethodDeclaration()->Accept( this );
		visitChild( methods->GetMethodDeclarationList().get() );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CNegationExpression * const expression )
	{
		TypeCheckerState oldState = state;
		state = TS_LookingType;
		lookingType = stdtype::ST_Bool;
		expression->GetExpression()->Accept( this );
		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CNumberExpr * const expression )
	{
		if( state == TS_LookingType ) {
			if( lookingType == stdtype::ST_Int ) {
				// OK
				state = TS_None;
				lookingType;
			} else {
				throw new CTypeException( expression->GetCol(), expression->GetRow(),
					"Incorrect type" );
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::COperationExpression * const operation )
	{
		// checking result type
		typedef AbstractTreeGenerator::COperationExpression::TOperationType OperationType;

		TypeCheckerState oldState = state;
		state = TS_LookingType;
		switch( lookingType ) {
			case stdtype::ST_Bool: {
				switch( operation->GetOperationType() ) {
					case OperationType::And: {
						lookingType = stdtype::ST_Bool;
						break;
					}
					case OperationType::Less: {
						lookingType = stdtype::ST_Int;
						break;
					}
					case OperationType::Mod: {
						lookingType = stdtype::ST_Int;
						break;
					}
					case OperationType::Or: {
						lookingType = stdtype::ST_Bool;
						break;
					}
					default: {
						throw new CTypeException( operation->GetCol(), operation->GetRow(),
							"Incorrect return value: bool required but method returns int" );
					}
				}
				break;
			}
			case stdtype::ST_Int: {
				switch( operation->GetOperationType() ) {
					case OperationType::Plus: {
						lookingType = stdtype::ST_Int;
						break;
					}
					case OperationType::Minus: {
						lookingType = stdtype::ST_Int;
						break;
					}
					case OperationType::Times: {
						lookingType = stdtype::ST_Int;
						break;
					}
					case OperationType::Divide: {
						lookingType = stdtype::ST_Int;
						break;
					}
					default: {
						throw new CTypeException( operation->GetCol(), operation->GetRow(),
							"Incorrect return value: int required but method returns bool" );
						break;
					}
				}
				break;
			}
			default: {
				throw new CTypeException( operation->GetCol(), operation->GetRow(), "Incorrect return type" );
				break;
			}
		}

		// 8. - 9. logical and numerical expressions
		operation->GetLeftOperand()->Accept( this );
		operation->GetRightOperand()->Accept( this );

		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CParenExpression * const expression )
	{
		// what is this?
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CPreconditionStatement * const condition )
	{
		// 5. if-while statement
			// a. exp is boolean

		TypeCheckerState oldState = state;
		state = TS_LookingType;
		lookingType = stdtype::ST_Bool;
		condition->GetExpression()->Accept( this );
		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CPrintStatement * const statement )
	{

		TypeCheckerState oldState = state;
		// 6. print statement
			// a. exp is int
		state = TS_LookingType;
		lookingType = stdtype::ST_Int;
		statement->GetExpression()->Accept( this );
		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CProgram * const program )
	{
		visitChild( program->GetClassDeclarationList().get() );
		program->GetMainClass()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CStatementList * const statement )
	{
		statement->GetStatement()->Accept( this );
		visitChild( statement->GetStatementList().get() );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CBasicType * const )
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIdType * const idType )
	{
		// 2.  Variable definition
			// a. Availability of classes
		int id = idType->GetIdExpression()->GetName();
		try {
			classes.GetClassInfo( id, idType );
		}
		catch( std::exception& e ) {
			// no such class;
			throw;
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CVarDeclaration * const var )
	{
		std::shared_ptr<AbstractTreeGenerator::IType> type = var->GetType();
		int vartype = type->GetType();

		if( vartype >= 0 ) {
			classes.GetClassInfo( vartype, var );
		} else {
			if( vartype <= stdtype::ST_Void ) {
				throw new CTypeException( var->GetCol(), var->GetRow(), "Wrong type" );
			}
		}

	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CVarDeclarationList * const vars )
	{
		vars->GetVarDeclaration()->Accept( this );
		visitChild( vars->GetVarDeclarationList().get() );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CTrueExpression * const expression )
	{
		// Checking return value type
		if( state == TS_LookingType ) {
			if( lookingType == stdtype::ST_Bool ) {
				// OK
				state = TS_None;
				lookingType = -4;
			} else {
				throw new CTypeException( expression->GetCol(), expression->GetRow(),
					"Incorrect return value: method returns bool" );
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CFalseExpression * const expression )
	{
		// Checking return value type
		if( state == TS_LookingType ) {
			if( lookingType == stdtype::ST_Bool ) {
				// OK
				state = TS_None;
				lookingType = -4;
			} else {
				throw new CTypeException( expression->GetCol(), expression->GetRow(),
					"Incorrect return value: method returns bool" );
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CGetFieldExpression * const expression )
	{
		int id = expression->GetIdExpression()->GetName();
		CMethodInfo methinfo;
		std::shared_ptr<AbstractTreeGenerator::CIdExpression> idVar
			= std::dynamic_pointer_cast<AbstractTreeGenerator::CIdExpression>(expression->GetExpression());
		if( idVar == nullptr ) {
			std::shared_ptr<AbstractTreeGenerator::CThisExpression> thisVar
				= std::dynamic_pointer_cast<AbstractTreeGenerator::CThisExpression>(expression->GetExpression());
			if( thisVar ) {
				methinfo = checkMethodExists( currentClassId, id, expression );
			} else {
				std::shared_ptr<AbstractTreeGenerator::CConstructorExpression> ctorVar
					= std::dynamic_pointer_cast<AbstractTreeGenerator::CConstructorExpression>(expression->GetExpression());
				if( ctorVar != 0 ) {
					int classname = ctorVar->GetIdExpression()->GetName();
					methinfo = checkMethodExists( classname, id, expression );
				} else {
					TypeCheckerState oldState = state;
					state = TS_LookingGet;
					int oldLookingGet = lookingGet;
					lookingGet = expression->GetIdExpression()->GetName();

					try {
						visitChild( expression->GetExpression().get() );
						methinfo = returnMethodInfo;
						state = oldState;
						lookingGet = oldLookingGet;
					}
					catch( ... ) {
						state = oldState;
						lookingGet = oldLookingGet;
						throw;
					}
				}

			}
		} else {
			int	varName = idVar->GetName();
			methinfo = checkGetField( varName, expression, id );
		}
		// Checking return value
		if( state == TS_LookingType ) {
			if( lookingType != methinfo.GetReturnType() ) {
				throw new CTypeException( expression->GetCol(), expression->GetRow(),
					"Bad return value" );
			}
		}
		if( state == TypeCheckerState::TS_LookingGet ) {
			int type = methinfo.GetReturnType();
			returnMethodInfo = checkMethodExists( type, lookingGet, expression );
		}
		int i = 0;

		for( std::shared_ptr<AbstractTreeGenerator::CExpressionList> arg = expression->GetExpressionList(); arg; arg = arg->GetExpressionList() ) {
			if( i >= methinfo.GetAllArgsCount() ) {
				throw new CTypeException( expression->GetCol(), expression->GetRow(), "Too much argumentas in method call" );
			}
			TypeCheckerState oldState = state;
			state = TypeCheckerState::TS_LookingType;
			int oldLookingType = lookingType;
			lookingType = methinfo.GetArgType( i );
			visitChild( arg->GetExpression().get() );
			lookingType = oldLookingType;
			state = oldState;
			++i;
		}
		if( i < methinfo.GetAllArgsCount() ) {
			throw new CTypeException( expression->GetCol(), expression->GetRow(), "Not enough argumentas in method call" );
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CConditionStatement * const condition )
	{
		// 5. if-while statement
		// a. exp is boolean
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = condition->GetExpression();
		std::shared_ptr<AbstractTreeGenerator::IStatement> stfirst = condition->GetStatementFirst();
		std::shared_ptr<AbstractTreeGenerator::IStatement> stsecond = condition->GetStatementSecond();

		TypeCheckerState oldState = state;
		state = TS_LookingType;
		lookingType = stdtype::ST_Bool;
		exp->Accept( this );
		stfirst->Accept( this );
		stsecond->Accept( this );
		state = oldState;
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CThisExpression * const expression )
	{
		if( state == TypeCheckerState::TS_LookingType ) {
			int currtype = currentClassId;
			while( currtype != CClassInfo::NothingExtend ) {
				if( currtype == lookingType ) {
					state == TypeCheckerState::TS_None;
					lookingType = stdtype::ST_Void;
					return;
				}
				currtype = classes.GetClassInfo( currtype, expression ).GetExtend();
			}
			throw new CTypeException( expression->GetCol(), expression->GetRow(), "Invalide type" );
		}
	}
}