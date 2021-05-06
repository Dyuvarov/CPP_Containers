#include <list>
#include <iostream>
#include "includes/list.hpp"

int main()
{
	std::list<char> sa;
	sa.push_back('a');
	sa.push_back('b');
	sa.push_back('c');
	sa.push_back('d');

	sa.assign(-1, '*');
	ft::list<char> ft;
//	ft.push_back('a');
//	ft.push_back('b');
//	ft.push_back('c');
//	ft.push_back('d');
//	ft::list<char> ft2;
//	ft2.push_back('z');
//	ft2.push_back('y');
//	ft2.push_back('x');
//	ft2.push_back('w');
//
//	ft = ft2;
//	while(1);
}

