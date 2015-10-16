#include<list>
#include<vector>
#include<unordered_map>
#include<stack>
#include<queue>
#include<regex>
#include<algorithm>
#include<iostream>
#include<stdexcept>
#include"SPALog.h"
#include"CFGNode.h"
#include"Statement.h"
#include"StatementType.h"
using namespace std;
#ifndef CFG_H
#define CFG_H
class CFG
{
	const int TYPE_PROC = -1;
	const int TYPE_NORMAL = 0;
	const int TYPE_WHILE = 1;
	const int TYPE_THEN = 2;
	const int TYPE_ELSE = 3;

	vector<list<int>> _next;
	vector<list<int>> _nextTable;
	vector<list<int>> _beforeTable;
	unordered_map<int, CFGNode*> _nodeMap;

	list<Statement>::iterator _codeIterator;
	list<Statement> _codeLst;
	stack<pair<int,int>> _nodeInOperation;
	list<int> _statBuffer;
	int _nodeIndex;
	int _size;
public:
	CFG();
	void buildGraph(list<Statement>);
	list<int> getNextFirst(int);
	list<int> getNextSecond(int);
	bool isNextValid(int, int);
	list<int> getNextStarFirst(int);
	list<int> getNextStarSecond(int);
	bool isNextStarValid(int, int);
	void printGraph();
	void printNextTable();
	void printBeforeTable();
	void logNext();
	~CFG();
private:
	int extractBuffer();
	int createContainerNode(int);
	int createDummyNode();
	int getType(Statement);
	int countBrace(string);
	list<int> traverse(int, vector<list<int>>);
	void solveCode();
	void solveNode(int,int);
	void initializeStack();
	void updateVector(int, int);
	void updateVector(int, int, vector<list<int>>&);
	void storeNextTable();
	void storeNext(int);
	bool isContainer(Statement);
	bool isIfStmt(Statement);
	bool isWhileStmt(Statement);
	bool isProc(Statement);
};
#endif
