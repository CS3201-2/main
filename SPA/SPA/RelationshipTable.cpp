#include "RelationshipTable.h"
#include <iostream>

RelationshipTable::RelationshipTable() {
	vector<string> arg1;
	vector<string> arg2;
	
	//ModifiesS (statements)
	 arg1 = { "assign", "while" };
	 arg2 = { "variable", "varName" };
	Relationship r(2, arg1, arg2);
	relTable["modifiess"] = r;
	arg1.clear();
	arg2.clear();
	//cout << relTable.find("modifies*")->second.arg1.at(0);
	
	//UsesS (statements)
	arg1 = { "assign", "while" };
	arg2 = { "variable", "varName" };
	Relationship r(2, arg1, arg2);
	relTable["usess"] = r;
	arg1.clear();
	arg2.clear();

	//Parent
	arg1 = { "while" };
	arg2 = { "stmt", "assign", "prog_line", "while" };
	Relationship r(2, arg1, arg2);
	relTable["parent"] = r;
	arg1.clear();
	arg2.clear();

	//Parent*
	arg1 = { "while" };
	arg2 = { "stmt", "assign", "prog_line", "while" };
	Relationship r(2, arg1, arg2);
	relTable["parentt"] = r;
	arg1.clear();
	arg2.clear();

	//Follows
	arg1 = { "stmt", "assign", "prog_line", "while" };
	arg2 = { "stmt", "assign", "prog_line", "while" };
	Relationship r(2, arg1, arg2);
	relTable["follows"] = r;
	arg1.clear();
	arg2.clear();

	//Followst
	arg1 = { "stmt", "assign", "prog_line", "while" };
	arg2 = { "stmt", "assign", "prog_line", "while" };
	Relationship r(2, arg1, arg2);
	relTable["followst"] = r;
	arg1.clear();
	arg2.clear();
}

bool RelationshipTable::hasRelationship(string rel) {
	auto it = relTable.find(rel);
	if (it == relTable.end()) { //relationship not found
		return false;
	}

	return true;
}

bool RelationshipTable::isNumOfArgsEqual(string rel, int num) {
	//add assert hasRelationship
	Relationship r = relTable.find(rel)->second;
	return (r.getNumOfArgs == num);
}

bool RelationshipTable::isArg1Valid(string rel, string dataType) {
	//add assert hasRelationship
	Relationship r = relTable.find(rel)->second;

	vector<string> arg1 = r.getArg1();
	vector<string>::const_iterator iterArg1 = arg1.begin();

	for (iterArg1; iterArg1 != arg1.end(); iterArg1++) {
		if (dataType.compare(*iterArg1) == 0) {
			return true;
		}
	}

	return false;
}

bool RelationshipTable::isArg2Valid(string rel, string dataType) {
	//add assert hasRelationship
	Relationship r = relTable.find(rel)->second;

	vector<string> arg2 = r.getArg2();
	vector<string>::const_iterator iterArg2 = arg2.begin();

	for (iterArg2; iterArg2 != arg2.end(); iterArg2++) {
		if (dataType.compare(*iterArg2) == 0) {
			return true;
		}
	}

	return false;
}
