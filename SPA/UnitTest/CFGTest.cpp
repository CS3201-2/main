#include "stdafx.h"
#include "CppUnitTest.h"
#include "CFG.h"
#include "SPALog.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	TEST_CLASS(CFGTest)
	{
	public:
		TEST_METHOD(testNoNested) {
			//constructing CFG
			list<Statement> expectedList;
			Statement temp = Statement();
			temp.setNumber(-1);
			temp.setContent("procedureFirst{");
			temp.setType(procDeclarationStmt);
			expectedList.push_back(temp);

			temp.setNumber(1);
			temp.setContent("x=2;");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(2);
			temp.setContent("z=3;");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(3);
			temp.setContent("callSecond;}");
			temp.setType(procCallStmt);
			expectedList.push_back(temp);

			temp.setNumber(-1);
			temp.setContent("procedureSecond{");
			temp.setType(procDeclarationStmt);
			expectedList.push_back(temp);

			temp.setNumber(4);
			temp.setContent("x=0;");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(5);
			temp.setContent("i=5;");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(6);
			temp.setContent("whilei{");
			temp.setType(whileStmt);
			expectedList.push_back(temp);

			temp.setNumber(7);
			temp.setContent("x=(x+2)*y;");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(8);
			temp.setContent("callThird;");
			temp.setType(procCallStmt);
			expectedList.push_back(temp);

			temp.setNumber(9);
			temp.setContent("i=i-1;}");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(10);
			temp.setContent("ifxthen{");
			temp.setType(ifStmt);
			expectedList.push_back(temp);

			temp.setNumber(11);
			temp.setContent("x=x+1;}");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(10);
			temp.setContent("ifxthen{");
			temp.setType(elseStmt);
			expectedList.push_back(temp);

			temp.setNumber(12);
			temp.setContent("z=1;}");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(13);
			temp.setContent("z=z+(x+1);");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(14);
			temp.setContent("y=z+2;");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(15);
			temp.setContent("x=(x*y)+z;}");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(-1);
			temp.setContent("procedureThird{");
			temp.setType(procDeclarationStmt);
			expectedList.push_back(temp);

			temp.setNumber(16);
			temp.setContent("z=5;");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			temp.setNumber(17);
			temp.setContent("v=z;}");
			temp.setType(assignmentStmt);
			expectedList.push_back(temp);

			CFG cfg;
			list<int> result;
			cfg.buildGraph(expectedList);
			//test getNextFirst
			result = { 1 };
			Assert::AreEqual(result, cfg.getNextFirst(2));
			result = { 5,9 };
			Assert::AreEqual(result, cfg.getNextFirst(6));
			result = { 6 };
			Assert::AreEqual(result, cfg.getNextFirst(10));
			result = { 10 };
			Assert::AreEqual(result, cfg.getNextFirst(11));
			//test getNextSecond
			//test isNextValid
			
		}
	};
}