#ifndef MODULE05_LISTTEST_HPP
#define MODULE05_LISTTEST_HPP
#include <iostream>
#include <fstream>
template <class T>
void printList(T const & list, std::ofstream & os)
{
	os << "*****List: *****" << std::endl;
	os << "size: " << list.size() << std::endl;
	os << "first: " << list.front() << std::endl ;
	os << "last: " << list.back() << std::endl ;
	os << "*****************" << std::endl;
}
#endif //MODULE05_LISTTEST_HPP
