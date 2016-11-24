#include <string>
#include <sstream>


namespace SymbolTable {
	class CTypeException : std::exception {
	public:
		virtual char const* what() const override;
		CTypeException( int col, int row, std::string msg );
	private:
		std::stringstream message;
	};
}