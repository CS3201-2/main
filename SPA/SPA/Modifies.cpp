#include "Modifies.h"


// constructor
Modifies::Modifies()
{
}

//key is the stmtLine
//first stmtLine, second varID

//set modifies need to see parser to decided
void Modifies::setModifies(int first, list<int> second) {
	if (modifiesMap.find(first) == modifiesMap.end()) {
		modifiesMap[first] = second;
	}
	else {
		list<int> existingModifiesList = modifiesMap.at(first);
		existingModifiesList.insert(existingModifiesList.end(), second.begin(), second.end());
		modifiesMap[first] = existingModifiesList;
	}
}

list<int> Modifies::getModifiesFirst(int second) {
	list<int> resultList;
	for (map<int, list<int>>::iterator it = modifiesMap.begin(); it != modifiesMap.end(); ++it) {
		if (find((*it).second.begin(), (*it).second.end(), second) != (*it).second.end()) {
			resultList.push_back((*it).first);
		}
	}

	return resultList;
}

list<int> Modifies::getModifiesSecond(int first) {
	if (modifiesMap.find(first) == modifiesMap.end()) {
		return list<int>();
	}
	else {
		return modifiesMap.at(first);
	}
}

bool Modifies::isModifiesValid(int first, int second) {
	if (modifiesMap.find(first) == modifiesMap.end()) {
		return false;
	}
	else {
		list<int> modifiesList = modifiesMap.at(first);
		return find(modifiesList.begin(), modifiesList.end(), second) != modifiesList.end();
	}
}

void Modifies::printAllModifies() {
	cout << "modifies table" << endl;
	for (map<int, list<int>>::iterator it = modifiesMap.begin(); it != modifiesMap.end(); ++it) {

		cout << (*it).first;
		cout << ":";
		for (list<int>::iterator listIt = (*it).second.begin(); listIt != (*it).second.end(); ++listIt) {
			cout << *listIt;
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}


/*void Modifies::sortMap() {
	for (map<int, std::list<int>>::iterator it = modifiesMap.begin(); it != modifiesMap.end(); ++it) {
		(*it).second.sort();
	}
}*/