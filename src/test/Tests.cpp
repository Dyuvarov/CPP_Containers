#include <iostream>
#include "Tests.hpp"

/*******LIST*******/

template<class Container>
void test_cnt_size(Container& cnt, std::string filepath)
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
	it = cnt.begin();
	while (it != cnt.end())
	{
		out << *it << std::endl;
		++it;
	}

	cnt.resize(0);
	it = cnt.begin();
	while (it != cnt.end())
	{
		out << *it << std::endl;
		++it;
	}
}

template<class Container>
void test_push_back(Container cnt, std::string filepath, typename Container::value_type value)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	cnt.push_back(value);
	typename Container::iterator it = cnt.begin();
	while (it != cnt.end())
	{
		out << *it << std::endl;
		++it;
	}
}

template<class Container>
void test_pop_back(Container cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	cnt.pop_back();
	typename Container::iterator it = cnt.begin();
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
		test_cnt_size(stdEmptyChar, stdFilePath);
		test_cnt_size(ftEmptyChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_cnt_size(stdEmptyInt, stdFilePath);
		test_cnt_size(ftEmptyInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_cnt_size(stdEmptyString, stdFilePath);
		test_cnt_size(ftEmptyString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tIterator:" << std::endl;
	{
		//constructors
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

	}

	std::cout << "\tConst Iterator:" << std::endl;
	{
		//constructors
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
	}

	std::cout << "\tReverse Iterator:" << std::endl;
	{
		//constructors
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
	}

	std::cout << "\tConst Reverse Iterator:" << std::endl;
	{
		//constructors
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

/*******VECTOR*******/
void testVector()
{
	std::string stdFilePath = "Vector_std.txt";
	std::string ftFilePath = "Vector_ft.txt";
	std::cout << "vector: " << std::endl;

	std::vector<char> stdEmptyChar;
	ft::vector<char> ftEmptyChar;

	std::vector<int> stdEmptyInt;
	ft::vector<int> ftEmptyInt;

	std::vector<std::string> stdEmptyString;
	ft::vector<std::string> ftEmptyString;

	std::vector<char> stdChar;
	stdChar.push_back('f');
	stdChar.push_back('g');
	stdChar.push_back('a');
	stdChar.push_back('b');

	ft::vector<char> ftChar;
	ftChar.push_back('f');
	ftChar.push_back('g');
	ftChar.push_back('a');
	ftChar.push_back('b');

	std::vector<int> stdInt;
	stdInt.push_back(42);
	stdInt.push_back(0);
	stdInt.push_back(-999);
	stdInt.push_back(999999999);

	ft::vector<int> ftInt;
	ftInt.push_back(42);
	ftInt.push_back(0);
	ftInt.push_back(-999);
	ftInt.push_back(999999999);

	std::vector<std::string> stdString;
	stdString.push_back("Hello!");
	stdString.push_back("");
	stdString.push_back("I am");
	stdString.push_back("String");
	stdString.push_back("List");

	ft::vector<std::string> ftString;
	ftString.push_back("Hello!");
	ftString.push_back("");
	ftString.push_back("I am");
	ftString.push_back("String");
	ftString.push_back("List");

	std::cout << "\tEmpty vector:" << std::endl;
	{
		std::cout << "\t\tsize:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_cnt_size(stdEmptyChar, stdFilePath);
		test_cnt_size(ftEmptyChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_cnt_size(stdEmptyInt, stdFilePath);
		test_cnt_size(ftEmptyInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_cnt_size(stdEmptyString, stdFilePath);
		test_cnt_size(ftEmptyString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tIterator:" << std::endl;
	{
		//constructors
		std::cout << "\t\t\tchar:";
		test_iter_constructors(stdChar, stdFilePath);
		test_iter_constructors(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_iter_constructors(stdInt, stdFilePath);
		test_iter_constructors(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_iter_constructors(stdString, stdFilePath);
		test_iter_constructors(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tConst Iterator:" << std::endl;
	{
		//constructors
		std::cout << "\t\t\tchar:";
		test_citer_constructors(stdChar, stdFilePath);
		test_citer_constructors(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_citer_constructors(stdInt, stdFilePath);
		test_citer_constructors(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_citer_constructors(stdString, stdFilePath);
		test_citer_constructors(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tReverse Iterator:" << std::endl;
	{
		//constructors
		std::cout << "\t\t\tchar:";
		test_riter_constructors(stdChar, stdFilePath);
		test_riter_constructors(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_riter_constructors(stdInt, stdFilePath);
		test_riter_constructors(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_riter_constructors(stdString, stdFilePath);
		test_riter_constructors(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tConst Reverse Iterator:" << std::endl;
	{
		//constructors
		std::cout << "\t\t\tchar:";
		test_rciter_constructors(stdChar, stdFilePath);
		test_rciter_constructors(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_rciter_constructors(stdInt, stdFilePath);
		test_rciter_constructors(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_rciter_constructors(stdString, stdFilePath);
		test_rciter_constructors(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\toperator=:" << std::endl;
	{
		std::cout << "\t\tchar:";
		test_assign_operator(stdChar, stdFilePath, 'p');
		test_assign_operator(ftChar, ftFilePath, 'p');
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_assign_operator(stdInt, stdFilePath, 21);
		test_assign_operator(ftInt, ftFilePath, 21);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_assign_operator(stdString, stdFilePath, "skrskrskr");
		test_assign_operator(ftString, ftFilePath, "skrskrskr");
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tpush back:" << std::endl;
	{
		std::cout << "\t\tchar:";
		test_push_back(stdChar, stdFilePath, 'q');
		test_push_back(ftChar, ftFilePath, 'q');
		compareFiles(stdFilePath, ftFilePath);

		std::cout << "\t\tint:";
		test_push_back(stdInt, stdFilePath, 42);
		test_push_back(ftInt, ftFilePath, 42);
		compareFiles(stdFilePath, ftFilePath);

		std::cout << "\t\tchar:";
		test_push_back(stdString, stdFilePath, "fortyTwo");
		test_push_back(ftString, ftFilePath, "fortyTwo");
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tpop_back:" << std::endl;
	{
		std::cout << "\t\tchar:";
		test_pop_back(stdChar, stdFilePath);
		test_pop_back(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);

		std::cout << "\t\tint:";
		test_pop_back(stdInt, stdFilePath);
		test_pop_back(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);

		std::cout << "\t\tchar:";
		test_pop_back(stdString, stdFilePath);
		test_pop_back(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tresize:" << std::endl;
	{
		std::vector<char> sChar(5, 'a');
		std::vector<int> sInt(5, 42);
		std::vector<std::string> sString(5, "asshole");

		ft::vector<char> ftChar(5, 'a');
		ft::vector<int> ftInt(5, 42);
		ft::vector<std::string> ftString (5, "asshole");

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

/*******STACK*******/
template<class Container>
void test_stack_top(Container cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	out << cnt.top() << std::endl;
	out.close();
}

template<class Container>
void test_stack_pop(Container cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");

	while (cnt.size() > 0)
	{
		out << cnt.top() << std::endl;
		cnt.pop();
	}
	out.close();
}

void testStack()
{
	std::string stdFilePath = "Vector_std.txt";
	std::string ftFilePath = "Vector_ft.txt";
	std::cout << "stack: " << std::endl;

	std::stack<char> stdEmptyChar;
	ft::stack<char> ftEmptyChar;

	std::stack<int> stdEmptyInt;
	ft::stack<int> ftEmptyInt;

	std::stack<std::string> stdEmptyString;
	ft::stack<std::string> ftEmptyString;

	std::stack<char> stdChar;
	stdChar.push('f');
	stdChar.push('g');
	stdChar.push('a');
	stdChar.push('b');

	ft::stack<char> ftChar;
	ftChar.push('f');
	ftChar.push('g');
	ftChar.push('a');
	ftChar.push('b');

	std::stack<int> stdInt;
	stdInt.push(42);
	stdInt.push(0);
	stdInt.push(-999);
	stdInt.push(999999999);

	ft::stack<int> ftInt;
	ftInt.push(42);
	ftInt.push(0);
	ftInt.push(-999);
	ftInt.push(999999999);

	std::stack<std::string> stdString;
	stdString.push("Hello!");
	stdString.push("");
	stdString.push("I am");
	stdString.push("String");
	stdString.push("List");

	ft::stack<std::string> ftString;
	ftString.push("Hello!");
	ftString.push("");
	ftString.push("I am");
	ftString.push("String");
	ftString.push("List");

	std::cout << "\tEmpty stack:" << std::endl;
	{
		std::cout << "\t\tchar:";
		test_cnt_size(stdEmptyChar, stdFilePath);
		test_cnt_size(ftEmptyChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_cnt_size(stdEmptyInt, stdFilePath);
		test_cnt_size(ftEmptyInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_cnt_size(stdEmptyString, stdFilePath);
		test_cnt_size(ftEmptyString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\ttop:" << std::endl;
	{
		std::cout << "\t\tchar:";
		test_stack_top(stdChar, stdFilePath);
		test_stack_top(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_stack_top(stdInt, stdFilePath);
		test_stack_top(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_stack_top(stdString, stdFilePath);
		test_stack_top(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tpop:" << std::endl;
	{
		std::cout << "\t\tchar:";
		test_stack_pop(stdChar, stdFilePath);
		test_stack_pop(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_stack_pop(stdInt, stdFilePath);
		test_stack_pop(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_stack_pop(stdString, stdFilePath);
		test_stack_pop(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}


}

/*******MAP*******/
template<class Container>
void print_map_ft(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	for (typename Container::iterator it = cnt.begin(); it != cnt.end(); it++)
		out << it->_first << it->_second;
	out.close();
}

template<class Container>
void print_map_std(Container& cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	for (typename Container::iterator it = cnt.begin(); it != cnt.end(); it++)
		out << it->first << it->second;
	out.close();
}

template<class Container>
void test_map_clear(Container cnt, std::string filepath)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	cnt.clear();
	out << cnt.size() << cnt.empty();
	out.close();
}

template<class Container>
void test_map_erase_ft(Container cnt, std::string filepath)
{
	typename Container::iterator bIt = cnt.begin();
	typename Container::iterator eIt = cnt.end();
	bIt++;
	eIt--;
	eIt--;
	cnt.erase(bIt, eIt);

	print_map_ft(cnt, filepath);
}

template<class Container>
void test_map_erase_std(Container cnt, std::string filepath)
{
	typename Container::iterator bIt = cnt.begin();
	typename Container::iterator eIt = cnt.end();
	bIt++;
	eIt--;
	eIt--;
	cnt.erase(bIt, eIt);

	print_map_std(cnt, filepath);
}

template<class Container>
void test_map_count(Container cnt, std::string filepath, typename Container::key_type key)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	out << cnt.count(key);
	out.close();
}

template<class Container>
void test_map_lower_bound_ft(Container cnt, std::string filepath, typename Container::key_type key)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	typename Container::iterator it = cnt.lower_bound(key);
	if (it != cnt.end())
		out << it->_first << it->_second;
	out.close();
}

template<class Container>
void test_map_lower_bound_std(Container cnt, std::string filepath, typename Container::key_type key)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	typename Container::iterator it = cnt.lower_bound(key);
	if (it != cnt.end())
		out << it->first << it->second;
	out.close();
}

template<class Container>
void test_map_upper_bound_ft(Container cnt, std::string filepath, typename Container::key_type key)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	typename Container::iterator it = cnt.upper_bound(key);
	if (it != cnt.end())
		out << it->_first << it->_second;
	out.close();
}

template<class Container>
void test_map_upper_bound_std(Container cnt, std::string filepath, typename Container::key_type key)
{
	std::ofstream out(filepath);
	if (!out.is_open())
		throw std::runtime_error("cant write in file!\n");
	typename Container::iterator it = cnt.upper_bound(key);
	if (it != cnt.end())
		out << it->first << it->second;
	out.close();
}


void testMap()
{
	std::string stdFilePath = "Map_std.txt";
	std::string ftFilePath = "Map_ft.txt";
	std::cout << "map: " << std::endl;

	std::map<char, char> stdEmptyChar;
	ft::map<char, char> ftEmptyChar;

	std::map<int, int> stdEmptyInt;
	ft::map<int, int> ftEmptyInt;

	std::map<std::string, std::string> stdEmptyString;
	ft::map<std::string, std::string> ftEmptyString;

	std::map<char, char> stdChar;
	stdChar.insert(std::make_pair('g', 'g'));
	stdChar.insert(std::make_pair('a', 'a'));
	stdChar.insert(std::make_pair('b', 'b'));
	stdChar.insert(std::make_pair('c', 'c'));

	ft::map<char, char> ftChar;
	ftChar.insert(ft::make_pair('g', 'g'));
	ftChar.insert(ft::make_pair('a', 'a'));
	ftChar.insert(ft::make_pair('b', 'b'));
	ftChar.insert(ft::make_pair('c', 'c'));

	std::map<int, int> stdInt;
	stdInt.insert(std::make_pair(19, 19));
	stdInt.insert(std::make_pair(7, 7));
	stdInt.insert(std::make_pair(99, 99));
	stdInt.insert(std::make_pair(0, 0));

	ft::map<int, int> ftInt;
	ftInt.insert(ft::make_pair(19, 19));
	ftInt.insert(ft::make_pair(7, 7));
	ftInt.insert(ft::make_pair(99, 99));
	ftInt.insert(ft::make_pair(0, 0));

	std::map<std::string, std::string> stdString;
	stdString.insert(std::make_pair("hello", "hello"));
	stdString.insert(std::make_pair("world", "world"));
	stdString.insert(std::make_pair("from", "from"));
	stdString.insert(std::make_pair("map", "map"));

	ft::map<std::string, std::string> ftString;
	ftString.insert(ft::make_pair("hello", "hello"));
	ftString.insert(ft::make_pair("world", "world"));
	ftString.insert(ft::make_pair("from", "from"));
	ftString.insert(ft::make_pair("map", "map"));

	std::cout << "\tEmpty map:" << std::endl;
	{
		std::cout << "\t\tsize:" << std::endl;
		std::cout << "\t\t\tchar:";
		test_cnt_size(stdEmptyChar, stdFilePath);
		test_cnt_size(ftEmptyChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_cnt_size(stdEmptyInt, stdFilePath);
		test_cnt_size(ftEmptyInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_cnt_size(stdEmptyString, stdFilePath);
		test_cnt_size(ftEmptyString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tIterator: ";
	{
		std::ofstream out_std(stdFilePath);
		std::ofstream out_ft(ftFilePath);
		if (!out_std.is_open() || !out_ft.is_open())
			throw std::runtime_error("cant write in file!\n");

		std::map<int,int> testStd;
		ft::map<int,int> testFt;
		for (int i = 0; i < 3; i++) {
			int rand1 = rand();
			std::pair<int, int> res(rand1, rand1);
			testStd.insert(res);
			ft::pair<int, int> resFT(rand1, rand1);
			testFt.insert(resFT);
		}
		std::map<int,int>::iterator it = testStd.begin();
		std::map<int,int>::iterator ite = testStd.end();
		ft::map<int,int>::iterator itm = testFt.begin();
		ft::map<int,int>::iterator item = testFt.end();
		while (it != ite) {
			out_std << it->first;
			out_std << it->second;
			it++;
		}
		while (itm != item) {
			out_ft << itm->_first;
			out_ft << itm->_second;
			itm++;
		}
		out_std.close();
		out_ft.close();
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tConst Iterator: ";
	{
		std::ofstream out_std(stdFilePath);
		std::ofstream out_ft(ftFilePath);
		if (!out_std.is_open() || !out_ft.is_open())
			throw std::runtime_error("cant write in file!\n");

		std::map<int,int> testStd;
		ft::map<int,int> testFt;
		for (int i = 0; i < 3; i++) {
			int rand1 = rand();
			std::pair<int, int> res(rand1, rand1);
			testStd.insert(res);
			ft::pair<int, int> resFT(rand1, rand1);
			testFt.insert(resFT);
		}
		std::map<int,int>::const_iterator it = testStd.begin();
		std::map<int,int>::const_iterator ite = testStd.end();
		ft::map<int,int>::const_iterator itm = testFt.begin();
		ft::map<int,int>::const_iterator item = testFt.end();
		while (it != ite) {
			out_std << it->first;
			out_std << it->second;
			it++;
		}
		while (itm != item) {
			out_ft << itm->_first;
			out_ft << itm->_second;
			itm++;
		}
		out_std.close();
		out_ft.close();
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tReverse Iterator: ";
	{
		std::ofstream out_std(stdFilePath);
		std::ofstream out_ft(ftFilePath);
		if (!out_std.is_open() || !out_ft.is_open())
			throw std::runtime_error("cant write in file!\n");

		std::map<int,int> testStd;
		ft::map<int,int> testFt;
		for (int i = 0; i < 3; i++) {
			int rand1 = rand();
			std::pair<int, int> res(rand1, rand1);
			testStd.insert(res);
			ft::pair<int, int> resFT(rand1, rand1);
			testFt.insert(resFT);
		}
		std::map<int,int>::reverse_iterator it = testStd.rbegin();
		std::map<int,int>::reverse_iterator ite = testStd.rend();
		ft::map<int,int>::reverse_iterator itm = testFt.rbegin();
		ft::map<int,int>::reverse_iterator item = testFt.rend();
		while (it != ite) {
			out_std << it->first;
			out_std << it->second;
			it++;
		}
		while (itm != item) {
			out_ft << itm->_first;
			out_ft << itm->_second;
			itm++;
		}
		out_std.close();
		out_ft.close();
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tConst Reverse Iterator: ";
	{
		std::ofstream out_std(stdFilePath);
		std::ofstream out_ft(ftFilePath);
		if (!out_std.is_open() || !out_ft.is_open())
			throw std::runtime_error("cant write in file!\n");

		std::map<int,int> testStd;
		ft::map<int,int> testFt;
		for (int i = 0; i < 3; i++) {
			int rand1 = rand();
			std::pair<int, int> res(rand1, rand1);
			testStd.insert(res);
			ft::pair<int, int> resFT(rand1, rand1);
			testFt.insert(resFT);
		}
		std::map<int,int>::const_reverse_iterator it = testStd.rbegin();
		std::map<int,int>::const_reverse_iterator ite = testStd.rend();
		ft::map<int,int>::const_reverse_iterator itm = testFt.rbegin();
		ft::map<int,int>::const_reverse_iterator item = testFt.rend();
		while (it != ite) {
			out_std << it->first;
			out_std << it->second;
			it++;
		}
		while (itm != item) {
			out_ft << itm->_first;
			out_ft << itm->_second;
			itm++;
		}
		out_std.close();
		out_ft.close();
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\toperator=:" << std::endl;
	{
		std::cout << "\t\tchar:";
		std::map<char, char> stdTmpCharMap = stdChar;
		ft::map<char, char> ftTmpCharMap = ftChar;
		print_map_std(stdTmpCharMap, stdFilePath);
		print_map_ft(ftTmpCharMap, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		std::map<int, int> stdTmpIntMap = stdInt;
		ft::map<int, int> ftTmpIntMap = ftInt;
		print_map_std(stdTmpIntMap, stdFilePath);
		print_map_ft(ftTmpIntMap, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		std::map<std::string, std::string> stdTmpStringMap = stdString;
		ft::map<std::string, std::string> ftTmpStringMap = ftString;
		print_map_std(stdTmpStringMap, stdFilePath);
		print_map_ft(ftTmpStringMap, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tinsert:" << std::endl;
	{
		std::cout << "\t\tchar:";
		print_map_std(stdChar, stdFilePath);
		print_map_ft(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		print_map_std(stdInt, stdFilePath);
		print_map_ft(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		print_map_std(stdString, stdFilePath);
		print_map_ft(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tsize:" << std::endl;
	{
		std::cout << "\t\t\tchar:";
		test_cnt_size(stdChar, stdFilePath);
		test_cnt_size(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_cnt_size(stdInt, stdFilePath);
		test_cnt_size(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_cnt_size(stdString, stdFilePath);
		test_cnt_size(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\terase:" << std::endl;
	{
		std::cout << "\t\t\tchar:";
		test_map_erase_std(stdChar, stdFilePath);
		test_map_erase_ft(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_map_erase_std(stdInt, stdFilePath);
		test_map_erase_ft(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_map_erase_std(stdString, stdFilePath);
		test_map_erase_ft(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tcount:" << std::endl;
	{
		std::cout << "\t\t\tchar:";
		test_map_count(stdChar, stdFilePath, 'a');
		test_map_count(stdChar, stdFilePath, '*');
		test_map_count(ftChar, ftFilePath, 'a');
		test_map_count(ftChar, ftFilePath, '*');
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_map_count(stdInt, stdFilePath, 0);
		test_map_count(stdInt, stdFilePath, 666);
		test_map_count(ftInt, ftFilePath, 0);
		test_map_count(ftInt, ftFilePath, 666);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_map_count(stdString, stdFilePath, "YO");
		test_map_count(stdString, stdFilePath, "hello");
		test_map_count(ftString, ftFilePath, "YO");
		test_map_count(ftString, ftFilePath, "hello");
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tlower_bound:" << std::endl;
	{
		std::cout << "\t\t\tchar:";
		test_map_lower_bound_std(stdChar, stdFilePath, 'a');
		test_map_lower_bound_std(stdChar, stdFilePath, '*');
		test_map_lower_bound_ft(ftChar, ftFilePath, 'a');
		test_map_lower_bound_ft(ftChar, ftFilePath, '*');
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_map_lower_bound_std(stdInt, stdFilePath, 0);
		test_map_lower_bound_std(stdInt, stdFilePath, 666);
		test_map_lower_bound_ft(ftInt, ftFilePath, 0);
		test_map_lower_bound_ft(ftInt, ftFilePath, 666);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_map_lower_bound_std(stdString, stdFilePath, "YO");
		test_map_lower_bound_std(stdString, stdFilePath, "hello");
		test_map_lower_bound_ft(ftString, ftFilePath, "YO");
		test_map_lower_bound_ft(ftString, ftFilePath, "hello");
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tupper_bound:" << std::endl;
	{
		std::cout << "\t\t\tchar:";
		test_map_upper_bound_std(stdChar, stdFilePath, 'a');
		test_map_upper_bound_std(stdChar, stdFilePath, '*');
		test_map_upper_bound_ft(ftChar, ftFilePath, 'a');
		test_map_upper_bound_ft(ftChar, ftFilePath, '*');
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_map_upper_bound_std(stdInt, stdFilePath, 0);
		test_map_upper_bound_std(stdInt, stdFilePath, 666);
		test_map_upper_bound_ft(ftInt, ftFilePath, 0);
		test_map_upper_bound_ft(ftInt, ftFilePath, 666);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_map_upper_bound_std(stdString, stdFilePath, "YO");
		test_map_upper_bound_std(stdString, stdFilePath, "hello");
		test_map_upper_bound_ft(ftString, ftFilePath, "YO");
		test_map_upper_bound_ft(ftString, ftFilePath, "hello");
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}

	std::cout << "\tclear:" << std::endl;
	{
		std::cout << "\t\t\tchar:";
		test_map_clear(stdChar, stdFilePath);
		test_map_clear(ftChar, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tint:";
		test_map_clear(stdInt, stdFilePath);
		test_map_clear(ftInt, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << "\tstring:";
		test_map_clear(stdString, stdFilePath);
		test_map_clear(ftString, ftFilePath);
		compareFiles(stdFilePath, ftFilePath);
		std::cout << std::endl;
	}
}

