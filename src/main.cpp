#include "test/TestUtils.hpp"
#include "test/Outputs.hpp"
#include "test/ListTests.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <list>

#include "../includes/list.hpp"


class testClass
{
public:
	int intValue;
	std::string stringValue;
	char charValue;
	bool boolValue;

	testClass()
	{
		intValue  = rand() % 100;
		stringValue = "Iam string";
		charValue = 42;
		boolValue = true;
		std::cout << "Test class constructed" << std::endl;
	}

	~testClass()
	{
		std::cout << "Test class destructed" << std::endl;
	}
};

int main()
{

	testList();

//	while(1);
	return 0;
}
