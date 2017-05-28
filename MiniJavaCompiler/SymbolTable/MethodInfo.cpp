#include <memory>
#include <cassert>
#include "MethodInfo.h"
#include "TypeException.h"
#include "..\AbstractTreeGenerator\StringTable.h"

extern std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;

namespace SymbolTable {
	CMethodInfo::CMethodInfo()
	{
	}

	int CMethodInfo::GetReturnType() const
	{
		return returnType;
	}

	void CMethodInfo::SetReturnType( const int id )
	{
		returnType = id;
	}

	const CVariableInfo & CMethodInfo::GetVarInfo( const int id, const AbstractTreeGenerator::INode* brokenNode ) const
	{
		auto info = vars.find( id );
		if( info == vars.end() ) {
			assert( brokenNode != 0 );
			throw new CTypeException( brokenNode->GetCol(), brokenNode->GetRow(), "Variable not declarated" );
		} else {
			return info->second;
		}
	}

	void CMethodInfo::AddVariableInfo( const int id, const CVariableInfo & info )
	{
		varsCount++;
		vars[id] = info;
	}

	const CVariableInfo & CMethodInfo::GetArgInfo( const int id, const AbstractTreeGenerator::INode* brokenNode ) const
	{
		auto info = args.find( id );
		if( info == args.end() ) {
			assert( brokenNode != 0 );
			throw new CTypeException( brokenNode->GetCol(), brokenNode->GetRow(), "Variable not declarated" );
		} else {
			return info->second;
		}
	}

	void CMethodInfo::AddArgInfo( const int id, const CVariableInfo & info )
	{
		argsTypes.push_back( info.GetType() );
		args[id] = info;
	}

	int CMethodInfo::GetUniqueArgsCount() const
	{
		return args.size();
	}

	int CMethodInfo::GetUniqueVarsCount() const
	{
		return varsCount;
	}

	int CMethodInfo::GetAllArgsCount() const
	{
		return argsTypes.size();
	}

	int CMethodInfo::GetAllVarsCount() const
	{
		return vars.size();
	}

	int CMethodInfo::GetArgType( const int num ) const
	{
		return argsTypes[num];
	}

	std::shared_ptr<IRTree::Label> CMethodInfo::GetLabel() const
	{
		if( label == 0 ) {
			assert( false );
			++methodCount;
			label = std::make_shared<IRTree::Label>( -methodCount, glabalStringTable->wfind( name ) );
		}
		return label;
	}

	void CMethodInfo::SetName( int _name )
	{
		name = _name;
		++methodCount;
		label = std::make_shared<IRTree::Label>( -methodCount, glabalStringTable->wfind( name ) );
	}

	int CMethodInfo::methodCount = 0;
}