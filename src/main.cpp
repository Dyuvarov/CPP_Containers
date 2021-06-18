
#include <vector>

#include "test/ListTests.hpp"

int main()
{
	std::vector<int> vec;
	vec.push_back(1);
	std::vector<int>::iterator it = vec.begin();
	--it;
	//testList();
	//while(1);
	return 0;
}
