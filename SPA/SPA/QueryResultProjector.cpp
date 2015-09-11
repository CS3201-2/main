#include "QueryResultProjector.h"
#include <vector>
#include <string>
#include <algorithm>
#include <list>

const int notApplicable = -1;
const int trueTable = 1;
const int falseTable = 0;

//constructor
QueryResultProjector::QueryResultProjector(list<ResultTable> resultList) {
	_resultList = resultList;
	_isWholeTrue = -1;
}

void QueryResultProjector::mergeTable() {
	vector<string> resultHeader;
	vector<vector<int>> result;

	for (list<ResultTable>::iterator it = _resultList.begin(); it != _resultList.end(); ++it) {
		if ((*it).getIsWholeTrue == notApplicable) {
			//if resultHeader and result is initialy empty,
			if (!resultHeader.empty() && !result.empty()) {
				if ((*it).getResult().empty()) {
					break;
					result.clear();
				}
				else {
					createResultHeader(resultHeader, (*it).getHeader());
					createResultTable(result, (*it).getResult());
					list<std::pair<int, int>> commonPairList = getCommonPair(resultHeader);
					vector<int> indexToRemove = getIndexToRemove(commonPairList);
					trimResultHeader(resultHeader, indexToRemove);
					trimResultTable(result, commonPairList, indexToRemove);
				}
			}
			else {
				resultHeader = (*it).getHeader();
				result = (*it).getResult();
			}
		}
		else if ((*it).getIsWholeTrue == trueTable) {
			continue;
		}
		else if ((*it).getIsWholeTrue == falseTable) {
			_isWholeTrue = 0;
			resultHeader.clear();
			result.clear();
			break;
		}
	}

	_resultTable = ResultTable(_isWholeTrue, resultHeader, result);
	//make the resultTable object
}

void QueryResultProjector::createResultHeader(vector<string>& resultHeader, vector<string> header) {
	resultHeader.insert(resultHeader.end(), header.begin(), header.end());
}

void QueryResultProjector::createResultTable(vector<vector<int>>& result, vector<vector<int>> table) {
	vector<vector<int>> newResultTable;

	for (vector<vector <int>>::size_type i = 0; i < result.size(); ++i) {
		for (vector<vector <int>>::size_type j = 0; j < table.size(); ++j) {
			vector<int> tempVector = result[i];
			tempVector.insert(tempVector.end(), table[j].begin(), table[j].end());
			newResultTable.push_back(tempVector);
			tempVector.clear();
		}
	}

	result = newResultTable;
}

list<std::pair<int, int>> QueryResultProjector::getCommonPair(vector<string> header) {
	list<std::pair<int, int>> commonPairList;
	for (vector<string>::size_type i = 0; i < header.size(); ++i) {
		for (vector<string>::size_type j = i + 1; j < header.size(); ++j) {
			if (header[i] == header[j]) {
				pair<int, int> tempPair = make_pair(i, j);
				commonPairList.push_back(tempPair);
			}
		}
	}
	return commonPairList;
}

vector<int> QueryResultProjector::getIndexToRemove(list<std::pair<int, int>> commonPairList) {
	vector<int> indexToRemove;
	for (list<std::pair<int, int>>::iterator lstIt = commonPairList.begin(); lstIt != commonPairList.end(); ++lstIt) {
		indexToRemove.push_back(max((*lstIt).first, (*lstIt).second));
	}
	sort(indexToRemove.begin(), indexToRemove.end());
	reverse(indexToRemove.begin(), indexToRemove.end());
	return indexToRemove;
}

void QueryResultProjector::trimResultTable(vector<vector<int>>& result, list<std::pair<int, int>> commonPairList, vector<int> indexToRemove) {
	for (vector<vector<int>>::iterator tableIt = result.begin(); tableIt != result.end(); ) {
		bool isEntryToBeRemoved = false;

		for (list<std::pair<int, int>>::iterator lstIt = commonPairList.begin(); lstIt != commonPairList.end(); ++lstIt) {
			if ((*tableIt)[(*lstIt).first] != (*tableIt)[(*lstIt).second]) {
				isEntryToBeRemoved = true;
				break;
			}
		}

		if (isEntryToBeRemoved) {
			tableIt = result.erase(tableIt);
		}
		else {
			++tableIt;
		}
	}

	for (vector<vector <int>>::size_type i = 0; i < result.size(); ++i) {
		vector<int>::iterator it = result[i].begin();
		for (vector<int>::size_type j = 0; j < indexToRemove.size(); ++j) {
			result[i].erase(it + indexToRemove[j]);
		}
	}
}

void QueryResultProjector::trimResultHeader(vector<string>& resultHeader, vector<int> indexToRemove) {
	for (vector<string>::size_type j = 0; j < indexToRemove.size(); ++j) {
		resultHeader.erase(resultHeader.begin() + indexToRemove[j]);
	}
}

//assumption: there will always be an index to return
int QueryResultProjector::getIndexOf(vector<string> header, string str) {
	for (vector<string>::size_type i = 0; i < header.size(); ++i) {
		if (header.at(i) == str) {
			return i;
		}
	}
}