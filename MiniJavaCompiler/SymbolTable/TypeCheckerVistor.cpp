#include "TypeCheckerVistor.h"
#include "Table.h"
#include <set>
#include <memory>

extern std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;
namespace SymbolTable {

	CTypeCheckerVistor::CTypeCheckerVistor()
	{
		state = None;
		lookingClass = -1;
	}


	CTypeCheckerVistor::~CTypeCheckerVistor()
	{
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CArgument * const argument)
	{
		// 4. Argument definition
			// b. Availability of classes
		if( argument->GetType()->GetType() == "POD" ) {
			std::shared_ptr<AbstractTreeGenerator::CIdType> type =
				std::dynamic_pointer_cast<AbstractTreeGenerator::CIdType>(argument->GetType());
			int id = type->GetIdExpression()->GetName();
			CTable classes;
			try {
				classes.GetClass( id );
			}
			catch( std::string& e ) {
				// no such class;
				throw;
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CArgumentList * const args)
	{
		std::shared_ptr<AbstractTreeGenerator::CArgument> arg = args->GetArgument();
		std::shared_ptr<AbstractTreeGenerator::CArgumentList> leftargs = args->GetArgumentList();
		arg->Accept( this );
		leftargs->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CAssignmentListStatement * const statements )
	{
		std::shared_ptr<AbstractTreeGenerator::CIdExpression> assignexp = statements->GetIdExpression();
		std::shared_ptr<AbstractTreeGenerator::IExpression> indexexp = statements->GetExpressionFirst();
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = statements->GetExpressionSecond();

		state = LookingForInt;
		indexexp->Accept( this );

		CVariableInfo varinfo;

		if( currentMethod != nullptr ) {
			varinfo = currentClass->GetVarInfo( assignexp->GetName() );
		} else {
			varinfo = currentClass->GetVarInfo( assignexp->GetName() );
		}			
		
		std::shared_ptr<AbstractTreeGenerator::IType> vartype = varinfo.GetType();
		if( vartype->GetType() != "POD" ) {
			std::shared_ptr<AbstractTreeGenerator::CBasicType> vartypebasic = 
				std::dynamic_pointer_cast<AbstractTreeGenerator::CBasicType>(vartype);
			typedef AbstractTreeGenerator::TStandardType stdtype;
			stdtype tp = vartypebasic->GetValue();
			switch( tp ) {
				case stdtype::ST_Int: {
					state = LookingForInt;
					exp->Accept( this );
					break;
				}
				case stdtype::ST_Bool: {
					state = LookingForBool;
					exp->Accept( this );
					break;
				}
				case stdtype::ST_Intlist: {
					state = LookingForIntList;
					exp->Accept( this );
				}
			}
		} else {
			std::shared_ptr<AbstractTreeGenerator::CIdType> vartypebasic =
				std::dynamic_pointer_cast<AbstractTreeGenerator::CIdType>(vartype);
			int id = vartypebasic->GetIdExpression()->GetName();
			CTable classes;
			lookingClass = classes.GetClass( id );
			state=LookingForCustom;
			exp->Accept( this );
		}			
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CAssignmentStatement * const statement)
	{
		// 7. Assignment
			// b. both expressions have the same type
		std::shared_ptr<AbstractTreeGenerator::CIdExpression> assignexp = statement->GetIdExpression();
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = statement->GetExpression();
		int id = assignexp->GetName();

		CVariableInfo varinfo;

		if( currentMethod != nullptr ) {
			varinfo = currentMethod->GetVarInfo( assignexp->GetName() );
		} else {
			varinfo = currentClass->GetVarInfo( assignexp->GetName() );
		}
		std::shared_ptr<AbstractTreeGenerator::IType> vartype = varinfo.GetType();
		if( vartype->GetType() != "POD" ) {
			std::shared_ptr<AbstractTreeGenerator::CBasicType> vartypebasic =
				std::dynamic_pointer_cast<AbstractTreeGenerator::CBasicType>(vartype);
			typedef AbstractTreeGenerator::TStandardType stdtype;
			stdtype tp = vartypebasic->GetValue();
			switch( tp ) {
				case stdtype::ST_Int: {
					state = LookingForInt;
					exp->Accept( this );
					break;
				}
				case stdtype::ST_Bool: {
					state = LookingForBool;
					exp->Accept( this );
					break;
				}
				case stdtype::ST_Intlist: {
					state = LookingForIntList;
					exp->Accept( this );
				}
			}
		} else {
			std::shared_ptr<AbstractTreeGenerator::CIdType> vartypebasic =
				std::dynamic_pointer_cast<AbstractTreeGenerator::CIdType>(vartype);
			int id = vartypebasic->GetIdExpression()->GetName();
			CTable classes;
			lookingClass = classes.GetClass( id );
			state = LookingForCustom;
			exp->Accept( this );
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassDeclaration * const CClass)
	{

		// 3.  method definition
			// a. Multiple method definition
		// maybe it's good to check in first run
		int id = CClass->GetIdExpression()->GetName();
		CTable classes;		
		currentClass = std::make_shared<CClassInfo>(classes.GetClassInfo( id ));
		std::vector<CMethodInfo> methods_infos = currentClass->GetMethods();
		std::set<CMethodInfo> mi_set;
		for( auto methods_info : methods_infos ) {
			mi_set.insert( methods_info );
		}
		if( methods_infos.size() != mi_set.size() ) {
			throw "Multiple method definition";
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassDeclarationList * const classlist )
	{
		std::shared_ptr<AbstractTreeGenerator::CClassDeclaration> Cclass = classlist->GetClassDeclaration();
		std::shared_ptr<AbstractTreeGenerator::CClassDeclarationList> leftclasses= classlist->GetClassDeclarationList();
		Cclass->Accept( this );
		leftclasses->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CClassExtend * const classExtend)
	{	
		int id = classExtend->GetIdExpression()->GetName();
		CTable classes;
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
		std::shared_ptr<AbstractTreeGenerator::CStatementList> statementlist = statement->GetStatementList();
		statementlist->Accept( this );
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
		switch( state ) {
			case LookingForBool: { 
				throw "Incorrect return value: bool required but method returns custom";
				break;
			}
			case LookingForInt: {
				throw "Incorrect return value: int required but method returns custom";
				break;
			}
			case LookingForIntList: {
				throw "Incorrect return value: int list required but method returns custom";
				break;
			}
			case LookingForCustom: {
				if( classes.GetClass(id) != lookingClass) {
					throw "Incorrect return value: no such class";					
				} else {
					lookingClass = -1;
					state = None;
				}
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CExpressionList * const expressionlist)
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = expressionlist->GetExpression();
		std::shared_ptr<AbstractTreeGenerator::CExpressionList> leftexp = expressionlist->GetExpressionList();
		exp->Accept( this );
		leftexp->Accept( this );
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
			std::shared_ptr<AbstractTreeGenerator::IType> vartype = varinfo.GetType();
			if( vartype->GetType() != "POD" ) {
				std::shared_ptr<AbstractTreeGenerator::CBasicType> vartypebasic =
					std::dynamic_pointer_cast<AbstractTreeGenerator::CBasicType>(vartype);
				typedef AbstractTreeGenerator::TStandardType stdtype;
				stdtype tp = vartypebasic->GetValue();
				switch( tp ) {
					case stdtype::ST_Int: {
						if( state != LookingForInt ) {
							throw "Incorrect return value";
						}			
						break;
					}
					case stdtype::ST_Bool: {
						if( state != LookingForBool ) {
							throw "Incorrect return value";
						}
						break;
					}
					case stdtype::ST_Intlist: {
						if( state != LookingForIntList ) {
							throw "Incorrect return value";
						}
						break;
					}
				}
			} else {
				std::shared_ptr<AbstractTreeGenerator::CIdType> vartypebasic =
					std::dynamic_pointer_cast<AbstractTreeGenerator::CIdType>(vartype);
				int id = vartypebasic->GetIdExpression()->GetName();
				CTable classes;
				if( state != LookingForCustom ) {
					throw "Incorrect return value";
				}
				if( lookingClass != classes.GetClass( id ) ) {
					throw "Incorrect return value: no such class";
				}
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CIndexExpression * const expression )
	{
		// 10. IndexExpression
			// a. must be int
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = expression->GetExpressionSecond();
		state = LookingForInt;
		exp->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CLastExpressionList * const expression)
	{
		expression->GetExp()->Accept( this );
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CLengthExpression * const expression)
	{
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CListConstructorExpression * const expression )
	{
		state = LookingForInt;
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

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CMethodDeclarationList * const methods)
	{
		methods->GetMethodDeclaration()->Accept( this );
		methods->GetMethodDeclarationList()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CNegationExpression * const expression)
	{
		state = LookingForBool;
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CNumberExpr * const expression)
	{
		switch( state ) {
			case LookingForBool: {
				throw "Incorrect return value: bool required but method returns int";
				break;
			}
			case LookingForCustom: {
				throw "Incorrect return value: custom required but method returns int";
				break;
			}
			case LookingForIntList: {
				throw "Incorrect return value: int list required but method returns int";
				break;
			}
			case LookingForInt: {
				// OK
				state = None;
				break;
			}
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::COperationExpression * const operation)
	{
		// checking result type
		typedef AbstractTreeGenerator::COperationExpression::TOperationType OperationType;
		switch( state ) {
			case LookingForBool: {
				switch( operation->GetOperationType() ) {
					case OperationType::And: {
						state = LookingForBool;
						break;
					}
					case OperationType::Less: {
						state = LookingForBool;
						break;
					}
					case OperationType::Mod: {
						state = LookingForBool;
						break;
					}
					case OperationType::Or: {
						state = LookingForBool;
						break;
					}
					default: {
						throw "Incorrect return value: bool required but method returns int";
					}							
				}
				break;			
			}
			case LookingForInt: {
				switch( operation->GetOperationType() ) {
					case OperationType::Plus: {
						state = LookingForInt;
						break;
					}
					case OperationType::Minus: {
						state = LookingForInt;
						break;
					}
					case OperationType::Times: {
						state = LookingForInt;
						break;
					}
					case OperationType::Divide: {
						state = LookingForInt;
						break;
					}
					default: {
						throw "Incorrect return value: int required but method returns bool";
					}
				}
				break;
			}			
		}

		// 8. - 9. logical and numerical expressions
		std::shared_ptr<AbstractTreeGenerator::IExpression> leftOperand = operation->GetLeftOperand();
		std::shared_ptr<AbstractTreeGenerator::IExpression> rightOperand = operation->GetRightOperand();
		leftOperand->Accept( this );
		rightOperand->Accept( this );

	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CParenExpression * const expression)
	{
		expression->GetExpression()->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CPreconditionStatement * const condition)
	{
		// 5. if-while statement
			// a. exp is boolean
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = condition->GetExpression();
		state = LookingForBool;
		exp->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CPrintStatement * const statement)
	{
		// 6. print statement
			// a. exp is int
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = statement->GetExpression();
		state = LookingForInt;
		exp->Accept( this );
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
		CTable classes;
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
		std::shared_ptr<AbstractTreeGenerator::IType> vartype = varinfo.GetType();
		if( vartype->GetType() == "POD" ) {
			std::shared_ptr<AbstractTreeGenerator::CIdType> vartypebasic =
				std::dynamic_pointer_cast<AbstractTreeGenerator::CIdType>(vartype);
			int id = vartypebasic->GetIdExpression()->GetName();
			CTable classes;			
			if( lookingClass != classes.GetClass( id ) ) {
				throw "Incorrect return value: no such class";
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
		switch( state ) {
			case LookingForBool: {
				state = None;
				break;
			}
			case LookingForInt: {
				throw "Incorrect return value: int required but method returns bool";
				break;
			} 
			case LookingForIntList: {
				throw "Incorrect return value: int list required but method returns bool";
				break;
			}
			case LookingForCustom: {
				throw "Incorrect return value: custom class required but method returns bool";
				break;
			}
			default:
				break;
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CFalseExpression * const )
	{
		// Checking return value type
		switch( state ) {
			case LookingForBool: {
				state = None;
				break;
			}
			case LookingForInt: {
				throw "Incorrect return value: int required but method returns bool";
				break;
			}
			case LookingForIntList: {
				throw "Incorrect return value: int list required but method returns bool";
				break;
			}
			case LookingForCustom: {
				throw "Incorrect return value: custom class required but method returns bool";
				break;
			}
			default:
				break;
		}
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CGetFieldExpression * const expression)
	{
		int id = expression->GetIdExpression()->GetName();
		CVariableInfo varinfo;

		
		varinfo = currentClass->GetVarInfo( id );		
		std::shared_ptr<AbstractTreeGenerator::IType> vartype = varinfo.GetType();
		if( vartype->GetType() == "POD" ) {
			std::shared_ptr<AbstractTreeGenerator::CIdType> vartypebasic =
				std::dynamic_pointer_cast<AbstractTreeGenerator::CIdType>(vartype);
			int id = vartypebasic->GetIdExpression()->GetName();
			CTable classes;
			if( lookingClass != classes.GetClass( id ) ) {
				throw "Incorrect return value: no such class";
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
		state = LookingForBool;
		exp->Accept( this );
	}

	void CTypeCheckerVistor::visit( AbstractTreeGenerator::CThisExpression * const expression )
	{
		//expression
		// TODO: so complex case
	}
}