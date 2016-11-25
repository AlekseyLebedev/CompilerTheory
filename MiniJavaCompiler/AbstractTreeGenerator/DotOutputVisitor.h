#pragma once
#include "IVisitor.h"
#include "AllNodes.h"
#include "INode.h"
#include <string>
#include <fstream>

namespace GraphvizOutput {

	class CDotOutputVisitor : public AbstractTreeGenerator::IVisitor {
	public:
		CDotOutputVisitor();
		void Start( std::string filename );
		void Close();
		virtual ~CDotOutputVisitor();

	private:
		std::ofstream dotFile;
		size_t id;

		size_t enterNode( const std::string & label );
		void addSubNode( size_t id, const std::string & label, const std::string & postfix = "v" );
		void addSubNode( size_t id, const int label, const std::string & postfix = "v" );
		//Эта штука может заработать, если будут реализован метод GetString у таблицы строк
		//void addSubNodeWithStringTable( size_t id, const size_t label, const std::string & postfix = "v" );
		void addArrow( const size_t from, const size_t to );
		void addChild( const size_t id, AbstractTreeGenerator::INode* node );
		void visitBinaryNode( const std::string& name, AbstractTreeGenerator::INode* left, AbstractTreeGenerator::INode* right );
		void visitUnaryNode( const std::string& name, AbstractTreeGenerator::INode* children );
		void visitTripleNode( const std::string& name, AbstractTreeGenerator::INode* left,
			AbstractTreeGenerator::INode* center, AbstractTreeGenerator::INode* right );
		void visitValueNode( const std::string& name, const std::string& value );
		void visitValueNode( const std::string& name, const int value );
		size_t nextId();

	public:
		// Унаследовано через IVisitor
		virtual void visit( AbstractTreeGenerator::CArgument * const ) override;
		virtual void visit( AbstractTreeGenerator::CArgumentList * const ) override;
		virtual void visit( AbstractTreeGenerator::CAssignmentListStatement * const ) override;
		virtual void visit( AbstractTreeGenerator::CAssignmentStatement * const ) override;
		virtual void visit( AbstractTreeGenerator::CClassDeclaration * const ) override;
		virtual void visit( AbstractTreeGenerator::CClassDeclarationList * const ) override;
		virtual void visit( AbstractTreeGenerator::CClassExtend * const ) override;
		virtual void visit( AbstractTreeGenerator::CCompoundStatement * const ) override;
		virtual void visit( AbstractTreeGenerator::CConstructorExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CExpressionList * const ) override;
		virtual void visit( AbstractTreeGenerator::CIdExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CIndexExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CLastExpressionList * const ) override;
		virtual void visit( AbstractTreeGenerator::CLengthExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CListConstructorExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CMainClass * const ) override;
		virtual void visit( AbstractTreeGenerator::CMethodDeclaration * const ) override;
		virtual void visit( AbstractTreeGenerator::CMethodDeclarationList * const ) override;
		virtual void visit( AbstractTreeGenerator::CNegationExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CNumberExpr * const ) override;
		virtual void visit( AbstractTreeGenerator::COperationExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CParenExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CPreconditionStatement * const ) override;
		virtual void visit( AbstractTreeGenerator::CPrintStatement * const ) override;
		virtual void visit( AbstractTreeGenerator::CProgram * const ) override;
		virtual void visit( AbstractTreeGenerator::CStatementList * const ) override;
		virtual void visit( AbstractTreeGenerator::CVarDeclaration * const ) override;
		virtual void visit( AbstractTreeGenerator::CVarDeclarationList * const ) override;
		virtual void visit( AbstractTreeGenerator::CTrueExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CFalseExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CGetFieldExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CConditionStatement * const ) override;
		virtual void visit( AbstractTreeGenerator::CThisExpression * const ) override;
		virtual void visit( AbstractTreeGenerator::CBasicType * const ) override;
		virtual void visit( AbstractTreeGenerator::CIdType * const ) override;
	};
}
