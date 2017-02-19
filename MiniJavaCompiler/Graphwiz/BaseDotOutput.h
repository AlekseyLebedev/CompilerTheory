#include <string>
#include <fstream>

namespace GraphvizOutput {

	class CBaseDotOutput {
	public:
		CBaseDotOutput( const std::wstring& _header ) : id( 0 ), header( _header )
		{
		}

		void Start( std::wstring filename )
		{
			dotFile.open( filename, std::ios_base::out | std::ios_base::trunc );
			dotFile << L"digraph G{" << std::endl;
			dotFile << L"\tlabel = \"" << header << "\"" << std::endl;
			id = 0;
		}


		void Close()
		{
			dotFile << L"}" << std::endl;
			dotFile.close();
		}


		virtual ~CBaseDotOutput()
		{
		}


	protected:
		size_t id;
		std::wofstream dotFile;
		const std::wstring& header;

		std::wstring stringToWstring( const std::string& value )
		{
			return std::wstring( value.begin(), value.end() );
		}

		size_t enterNode( const std::wstring& label )
		{
			++id;
			dotFile << L"\tn" << id << L"[label=\"" << label << L"\"]" << std::endl;
			return id;
		}

		size_t enterNode( const std::string& label )
		{
			return enterNode( stringToWstring( label ) );
		}


		void addSubNode( size_t id, const std::wstring& label, const std::wstring& postfix = L"v" )
		{
			dotFile << L"\tn" << id << postfix << L"[label=\"" << label << L"\"]" << std::endl;
			dotFile << L"\tn" << id << L" -> n" << id << postfix << L";" << std::endl;
		}


		void addSubNode( size_t id, const int label, const std::wstring& postfix = L"v" )
		{
			dotFile << L"\tn" << id << postfix << L"[label=\"" << label << L"\"]" << std::endl;
			dotFile << L"\tn" << id << L" -> n" << id << postfix << L";" << std::endl;
		}


		void addSubNode( size_t id, const std::string& label, const std::string& postfix = "v" )
		{
			addSubNode( id, stringToWstring( label ), stringToWstring( postfix ) );
		}


		void addSubNode( size_t id, const int label, const std::string& postfix )
		{
			addSubNode( id, label, stringToWstring( postfix ) );
		}


		void addArrow( const size_t from, const size_t to )
		{
			dotFile << L"\tn" << from << L" -> n" << to << L";" << std::endl;
		}


		void addChild( const size_t id, TNode * node )
		{
			size_t next = nextId();
			if( node == 0 ) {
				enterNode( L"nullptr" );
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