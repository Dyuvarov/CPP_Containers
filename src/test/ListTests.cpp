#include "ListTests.hpp"
#include "TestUtils.hpp"
#include "Outputs.hpp"
#include "../../includes/list.hpp"
#include "TestClass.hpp"
#include <iostream>
#include <list>

/* Testit:
    not std allocator
    std::list<char> sa(0,0);
*/
template<class Container>
void test_list_size(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	out << "size: " << cnt.size() << std::endl;
	out.close();
}


template<class Container>
void test_iter_constructors(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	typename Container::iterator		sempty;
	typename Container::iterator sit  = cnt.begin();
	typename Container::iterator sit1(sit);
	out << *sit << std::endl;
	out << *sit1 << std::endl;
	out.close();
}

template<class Container>
void test_citer_constructors(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	typename Container::const_iterator		sempty;
	typename Container::const_iterator sit  = cnt.begin();
	typename Container::const_iterator sit1(sit);
	typename Container::iterator sit2 = cnt.begin();
	typename Container::const_iterator sit3(sit1);

	out << *sit << std::endl;
	out << *sit1 << std::endl;
	out << *sit2 << std::endl;
	out << *sit3 << std::endl;
	out.close();
}

template<class Container>
void test_const_iter_operators(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	typename Container::const_iterator sit  = cnt.begin();
	typename Container::const_iterator sit1(sit);
	out << (sit1==sit) << std::endl;
	typename Container::const_iterator sit2;
	sit2 = sit1 = sit;

	out << *sit2 << std::endl;
	typename Container::iterator sit0 = cnt.end();
	--sit0;
	sit2 = sit0;
	out << *sit2 << std::endl;
	typename Container::const_iterator sit02(sit0);
	out << (sit02 == sit) << std::endl;
	out << (*sit02 == *sit) << std::endl;

	--sit;
	--sit;
	out << *sit << std::endl;
	typename Container::const_iterator& sit3 = --sit;
	out << (*sit == *sit3) << std::endl;
	out << (*sit != *sit3) << std::endl;
	sit1 = sit--;
	out << (*sit1 == *sit) << std::endl;
	out << (*sit1 != *sit) << std::endl;

	sit2 = cnt.end();
	++sit2;
	++sit2;
	out << *sit2 << std::endl;
	sit3 = ++sit2;
	out << (*sit2 == *sit3) << std::endl;
	sit1 = sit2++;
	out << (*sit1 == *sit2) << std::endl;

	const typename Container::value_type* ptr = sit1.operator->();
	out << *ptr << std::endl;

	out.close();
	//empty list test
	Container empt;
	sit = empt.end();
	for (int i = 0; i < 10; i++)
		--sit;
	for (int i = 0; i < 10; i++)
		sit--;
	for (int i = 0; i < 15; i++)
		++sit;
	for (int i = 0; i < 15; i++)
		sit++;
}

template<class Container>
void test_iter_operators(Container& cnt, std::string filepath, typename Container::value_type replace)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	typename Container::iterator sit  = cnt.begin();
	typename Container::iterator sit1(sit);
	out << (sit1==sit) << std::endl;
	typename Container::iterator sit2;
	sit2 = sit1 = sit;
	out << *sit2 << std::endl;
	--sit;
	--sit;
	out << *sit << std::endl;
	typename Container::iterator& sit3 = --sit;
	out << (*sit == *sit3) << std::endl;
	out << (*sit != *sit3) << std::endl;
	sit1 = sit--;
	out << (*sit1 == *sit) << std::endl;
	out << (*sit1 != *sit) << std::endl;

	sit2 = cnt.end();
	++sit2;
	++sit2;
	out << *sit2 << std::endl;
	sit3 = ++sit2;
	out << (*sit2 == *sit3) << std::endl;
	sit1 = sit2++;
	out << (*sit1 == *sit2) << std::endl;

	const typename Container::value_type* ptr = sit1.operator->();
	out << *ptr << std::endl;

	typename Container::value_type tmp = *sit3;
	*sit3 = replace;
	out << *sit3 << std::endl;
	out << (*sit3==replace) << std::endl;
	*sit3 = tmp;

	out.close();
	//empty list test
	Container empt;
	sit = empt.end();
	for (int i = 0; i < 10; i++)
		--sit;
	for (int i = 0; i < 10; i++)
		sit--;
	for (int i = 0; i < 15; i++)
		++sit;
	for (int i = 0; i < 15; i++)
		sit++;
}

template<class Container>
void test_riter_constructors(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	typename Container::reverse_iterator		empty;
	typename Container::reverse_iterator sit  = cnt.rbegin();
	typename Container::reverse_iterator sit1(sit);
	out << *sit << std::endl;
	out << *sit1 << std::endl;
	out.close();
}

template<class Container>
void test_riter_operators(Container& cnt, std::string filepath, typename Container::value_type replace)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	typename Container::reverse_iterator sit  = cnt.rbegin();
	typename Container::reverse_iterator sit1(sit);
	out << (sit1==sit) << std::endl;
	typename Container::reverse_iterator sit2;
	sit2 = sit1 = sit;
	out << *sit2 << std::endl;
	--sit;
	--sit;
	out << *sit << std::endl;
	typename Container::reverse_iterator& sit3 = --sit;
	out << (*sit == *sit3) << std::endl;
	out << (*sit != *sit3) << std::endl;
	sit1 = sit--;
	out << (*sit1 == *sit) << std::endl;
	out << (*sit1 != *sit) << std::endl;

	sit2 = cnt.rend();
	++sit2;
	++sit2;
	out << *sit2 << std::endl;
	sit3 = ++sit2;
	out << (*sit2 == *sit3) << std::endl;
	sit1 = sit2++;
	out << (*sit1 == *sit2) << std::endl;

	const typename Container::value_type* ptr = sit1.operator->();
	out << *ptr << std::endl;

	typename Container::value_type tmp = *sit3;
	*sit3 = replace;
	out << *sit3 << std::endl;
	out << (*sit3==replace) << std::endl;
	*sit3 = tmp;

	out.close();
	//empty list test
	Container empt;
	sit = empt.rend();
	for (int i = 0; i < 10; i++)
		--sit;
	for (int i = 0; i < 10; i++)
		sit--;
	for (int i = 0; i < 15; i++)
		++sit;
	for (int i = 0; i < 15; i++)
		sit++;
}

template<class Container>
void test_rciter_constructors(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	typename Container::const_reverse_iterator		sempty;
	typename Container::const_reverse_iterator sit  = cnt.rbegin();
	typename Container::const_reverse_iterator sit1(sit);
	typename Container::reverse_iterator sit2 = cnt.rbegin();
	typename Container::const_reverse_iterator sit3(sit1);

	out << *sit << std::endl;
	out << *sit1 << std::endl;
	out << *sit2 << std::endl;
	out << *sit3 << std::endl;
	out.close();
}

template<class Container>
void test_rconst_iter_operators(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	typename Container::const_reverse_iterator sit  = cnt.rbegin();
	typename Container::const_reverse_iterator sit1(sit);
	out << (sit1==sit) << std::endl;
	typename Container::const_reverse_iterator sit2;
	sit2 = sit1 = sit;
	out << *sit2 << std::endl;

	typename Container::reverse_iterator sit0 = cnt.rend();
	++sit0;
	sit2 = sit0;
	out << *sit2 << std::endl;
	typename Container::const_reverse_iterator sit02(sit0);
	out << (sit02 == sit) << std::endl;
	out << (*sit02 == *sit) << std::endl;

	--sit;
	--sit;
	out << *sit << std::endl;
	typename Container::const_reverse_iterator& sit3 = --sit;
	out << (*sit == *sit3) << std::endl;
	out << (*sit != *sit3) << std::endl;
	sit1 = sit--;
	out << (*sit1 == *sit) << std::endl;
	out << (*sit1 != *sit) << std::endl;

	sit2 = cnt.rend();
	++sit2;
	++sit2;
	out << *sit2 << std::endl;
	sit3 = ++sit2;
	out << (*sit2 == *sit3) << std::endl;
	sit1 = sit2++;
	out << (*sit1 == *sit2) << std::endl;

	const typename Container::value_type* ptr = sit1.operator->();
	out << *ptr << std::endl;

	out.close();
	//empty list test
	Container empt;
	sit = empt.rend();
	for (int i = 0; i < 10; i++)
		--sit;
	for (int i = 0; i < 10; i++)
		sit--;
	for (int i = 0; i < 15; i++)
		++sit;
	for (int i = 0; i < 15; i++)
		sit++;
}

template<class Container>
void test_assign_operator(Container& cnt, std::string filepath, typename Container::value_type element)
{
    std::ofstream out(filepath);
    if (!out.is_open())
        throw std::runtime_error("cant write in file!\n");

    Container other;
    for(int i = 0; i < 20; i++)
        other.push_back(element);
    other = cnt;
    typename Container::iterator it = other.begin();
    while (it != other.end())
    {
        out << *it << std::endl;
        ++it;
    }

    Container other2;
    other = other2;
    it = other.begin();
    while (it != other.end())
    {
        out << *it << std::endl;
        ++it;
    }

    Container other3;
    other = other3;
    it = other.begin();
    while (it != other.end())
    {
        out << *it << std::endl;
        ++it;
    }

    Container other4;
    for(int i = 0; i < 21; i++)
        other4.push_back(element);
    other = other4;
    it = other.begin();
    while (it != other.end())
    {
        out << *it << std::endl;
        ++it;
    }
}

template<class Container>
void test_resize(Container& cnt, std::string filepath, typename Container::value_type element)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	cnt.resize(3);
	typename Container::iterator it = cnt.begin();
	while (it != cnt.end())
	{
		out << *it << std::endl;
		++it;
	}

	cnt.resize(100, element);
	it = cnt.begin();
	while (it != cnt.end())
	{
		out << *it << std::endl;
		++it;
	}

	cnt.resize(1);
	it = cnt.begin();
	while (it != cnt.end())
	{
		out << *it << std::endl;
		++it;
	}

	cnt.resize(1000);
	while (it != cnt.end())
	{
		out << *it << std::endl;
		++it;
	}

	cnt.resize(0);
	while (it != cnt.end())
	{
		out << *it << std::endl;
		++it;
	}
}

void testList()
{
	std::string stdFilePath = "List_std.txt";
	std::string ftFilePath = "List_ft.txt";
	std::cout << "list: " << std::endl;

	std::list<char> stdEmptyChar;
	ft::list<char> ftEmptyChar;

	std::list<int> stdEmptyInt;
	ft::list<int> ftEmptyInt;

	std::list<std::string> stdEmptyString;
	ft::list<std::string> ftEmptyString;


	std::list<char> sList;
	sList.push_back('f');
	sList.push_back('g');
	sList.push_back('a');
	sList.push_back('b');

	ft::list<char> ftList;
	ftList.push_back('f');
	ftList.push_back('g');
	ftList.push_back('a');
	ftList.push_back('b');

	std::list<int> sIntList;
	sIntList.push_back(42);
	sIntList.push_back(0);
	sIntList.push_back(-999);
	sIntList.push_back(999999999);

	ft::list<int> ftIntList;
	ftIntList.push_back(42);
	ftIntList.push_back(0);
	ftIntList.push_back(-999);
	ftIntList.push_back(999999999);

	std::list<std::string> sStringList;
	sStringList.push_back("Hello!");
	sStringList.push_back("");
	sStringList.push_back("I am");
	sStringList.push_back("String");
	sStringList.push_back("List");

	ft::list<std::string> ftStringList;
	ftStringList.push_back("Hello!");
	ftStringList.push_back("");
	ftStringList.push_back("I am");
	ftStringList.push_back("String");
	ftStringList.push_back("List");


	std::cout << "\tEmpty list:" << std::endl;
	{
		std::cout << "\t\tsize:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_list_size(stdEmptyChar, stdFilePath);
		test_list_size(ftEmptyChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_list_size(stdEmptyInt, stdFilePath);
		test_list_size(ftEmptyInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_list_size(stdEmptyString, stdFilePath);
		test_list_size(ftEmptyString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tIterator:" << std::endl;
	{
		//constructors
		std::cout << "\t\tconstructors:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_iter_constructors(sList, stdFilePath);
		test_iter_constructors(ftList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_iter_constructors(sIntList, stdFilePath);
		test_iter_constructors(ftIntList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_iter_constructors(sStringList, stdFilePath);
		test_iter_constructors(ftStringList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
		//operators
		std::cout << "\t\toperators:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_iter_operators<std::list<char> >(sList, stdFilePath, 'q');
		test_iter_operators<ft::list<char> >(ftList, ftFilePath,'q');
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_iter_operators<std::list<int> >(sIntList, stdFilePath, 10);
		test_iter_operators<ft::list<int> >(ftIntList, ftFilePath, 10);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_iter_operators<std::list<std::string> >(sStringList, stdFilePath, "ft");
		test_iter_operators<ft::list<std::string> >(ftStringList, ftFilePath, "ft");
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tConst Iterator:" << std::endl;
	{
		//constructors
		std::cout << "\t\tconstructors:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_citer_constructors(sList, stdFilePath);
		test_citer_constructors(ftList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_citer_constructors(sIntList, stdFilePath);
		test_citer_constructors(ftIntList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_citer_constructors(sStringList, stdFilePath);
		test_citer_constructors(ftStringList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
		//operators
		std::cout << "\t\toperators:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_const_iter_operators<std::list<char> >(sList, stdFilePath);
		test_const_iter_operators<ft::list<char> >(ftList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_const_iter_operators<std::list<int> >(sIntList, stdFilePath);
		test_const_iter_operators<ft::list<int> >(ftIntList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_const_iter_operators<std::list<std::string> >(sStringList, stdFilePath);
		test_const_iter_operators<ft::list<std::string> >(ftStringList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tReverse Iterator:" << std::endl;
	{
		//constructors
		std::cout << "\t\tconstructors:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_riter_constructors(sList, stdFilePath);
		test_riter_constructors(ftList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_riter_constructors(sIntList, stdFilePath);
		test_riter_constructors(ftIntList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_riter_constructors(sStringList, stdFilePath);
		test_riter_constructors(ftStringList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
		//operators
		std::cout << "\t\toperators:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_riter_operators<std::list<char> >(sList, stdFilePath, 'q');
		test_riter_operators<ft::list<char> >(ftList, ftFilePath,'q');
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_riter_operators<std::list<int> >(sIntList, stdFilePath, 10);
		test_riter_operators<ft::list<int> >(ftIntList, ftFilePath, 10);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_riter_operators<std::list<std::string> >(sStringList, stdFilePath, "ft");
		test_riter_operators<ft::list<std::string> >(ftStringList, ftFilePath, "ft");
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tConst Reverse Iterator:" << std::endl;
	{
		//constructors
		std::cout << "\t\tconstructors:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_rciter_constructors(sList, stdFilePath);
		test_rciter_constructors(ftList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_rciter_constructors(sIntList, stdFilePath);
		test_rciter_constructors(ftIntList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_rciter_constructors(sStringList, stdFilePath);
		test_rciter_constructors(ftStringList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
		//operators
		std::cout << "\t\toperators:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_rconst_iter_operators<std::list<char> >(sList, stdFilePath);
		test_rconst_iter_operators<ft::list<char> >(ftList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_rconst_iter_operators<std::list<int> >(sIntList, stdFilePath);
		test_rconst_iter_operators<ft::list<int> >(ftIntList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_rconst_iter_operators<std::list<std::string> >(sStringList, stdFilePath);
		test_rconst_iter_operators<ft::list<std::string> >(ftStringList, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

    std::cout << "\toperator=:" << std::endl;
    {
        std::cout << "\t\tchar:";
        test_assign_operator(sList, stdFilePath, 'p');
        test_assign_operator(ftList, ftFilePath, 'p');
        compareFiles(stdFilePath, ftFilePath);
        std::cout << "\tint:";
        test_assign_operator(sIntList, stdFilePath, 21);
        test_assign_operator(ftIntList, ftFilePath, 21);
        compareFiles(stdFilePath, ftFilePath);
        std::cout << "\tstring:";
        test_assign_operator(sStringList, stdFilePath, "skrskrskr");
        test_assign_operator(ftStringList, ftFilePath, "skrskrskr");
        compareFiles(stdFilePath, ftFilePath);
        std::cout << std::endl;
    }

	std::cout << "\tresize:" << std::endl;
	{
		std::list<char> sChar(5, 'a');
		std::list<int> sInt(5, 42);
		std::list<std::string> sString(5, "asshole");

		ft::list<char> ftChar(5, 'a');
		ft::list<int> ftInt(5, 42);
		ft::list<std::string> ftString (5, "asshole");

		std::cout << "\t\tchar:";
		test_resize(sChar, stdFilePath, 'q');
		test_resize(ftChar, ftFilePath, 'q');
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\t\tint:";
		test_resize(sInt, stdFilePath, 42);
		test_resize(ftInt, ftFilePath, 42);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\t\tstring:";
		test_resize(sString, stdFilePath, "not asshole");
		test_resize(ftString, ftFilePath, "not asshole");
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}
}