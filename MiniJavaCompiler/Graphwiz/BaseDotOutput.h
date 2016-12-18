#pragma once
#include <string>
#include <fstream>

namespace GraphvizOutput {

	//template <typename TVistor, typename TNode>
	class CBaseDotOutput {
	public:
		CBaseDotOutput() : id( 0 )
		{
		}

		void Start( std::string filename )
		{
			dotFile.open( filename, std::ios_base::out | std::ios_base::trunc );
			dotFile << "digraph G{" << std::endl;
			id = 0;
		}


		void Close()
		{
			dotFile << "}" << std::endl;
			dotFile.close();
		}


		virtual ~CBaseDotOutput()
		{
		}


	protected:
		size_t id;
		std::ofstream dotFile;

		size_t enterNode( const std::string& label )
		{
			++id;
			dotFile << "\tn" << id << "[label=\"" << label << "\"]" << std::endl;
			return id;
		}


		void addSubNode( size_t id, const std::string& label, const std::string& postfix = "v" )
		{
			dotFile << "\tn" << id << postfix << "[label=\"" << label << "\"]" << std::endl;
			dotFile << "\tn" << id << " -> n" << id << postfix << ";" << std::endl;
		}


		void addSubNode( size_t id, const int label, const std::string& postfix = "v" )
		{
			dotFile << "\tn" << id << postfix << "[label=\"" << label << "\"]" << std::endl;
			dotFile << "\tn" << id << " -> n" << id << postfix << ";" << std::endl;
		}


		void addArrow( const size_t from, const size_t to )
		{
			dotFile << "\tn" << from << " -> n" << to << ";" << std::endl;
		}


		void addChild( const size_t id, TNode * node )
		{
			size_t next = nextId();
			if( node == 0 ) {
				enterNode( "nullptr" );
			} else {
				node->Accept( dynamic_cast<TVisitor*>(this) );
			}
			addArrow( id, next );
		}


		void visitBinaryNode( const std::string & name, TNode * left, TNode * right )
		{
			size_t current = enterNode( name );
			addChild( current, left );
			addChild( current, right );
		}


		void visitUnaryNode( const std::string & name, TNode * children )
		{
			size_t current = enterNode( name );
			addChild( current, children );

		}


		void visitTripleNode( const std::string & name, TNode * left, TNode * center, TNode * right )
		{
			size_t current = enterNode( name );
			addChild( current, left );
			addChild( current, center );
			addChild( current, right );
		}


		void visitValueNode( const std::string & name, const std::string & value )
		{
			size_t current = enterNode( name );
			addSubNode( current, value );
		}


		void visitValueNode( const std::string & name, const int value )
		{
			size_t current = enterNode( name );
			addSubNode( current, value );
		}


		size_t nextId()
		{
			return id + 1;
		}
	};
}