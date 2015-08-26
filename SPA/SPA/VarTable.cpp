#include "VarTable.h"
#include <map>
#include <string>

using namespace std;

// construactor
VarTable::VarTable(void)
{
}

int VarTable::get_ID(string varName)
{
	return varTable.at(varName);
}

int VarTable::insert_Var(string varName)
{
	int id = varTable.size() + 1;
	varTable.insert( std::pair<string,int>( varName, id ) );
	return id;
}

int VarTable::get_size()
{
	return varTable.size();
}


