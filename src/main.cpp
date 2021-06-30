
#include <map>

#include "test/Tests.hpp"

int main()
{
	std::map<int, char> sMap;
	sMap.insert(std::make_pair(5,'a'));
	sMap.insert(std::make_pair(4,'b'));
	sMap.insert(std::make_pair(99,'c'));
	sMap.insert(std::make_pair(0,'d'));

	auto its = sMap.equal_range(-1);
	std::cout << sMap[4] << std::endl;
//	testList();
//	testVector();
//	testStack();
//	while(1);
	return 0;
}
