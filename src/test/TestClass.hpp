#ifndef FT_CONTAINERS_TESTCLASS_HPP
#define FT_CONTAINERS_TESTCLASS_HPP
#include <iostream>
#include <fstream>

class TestClass {
public:
    int intValue;
    char charValue;
    int *intArr;

    TestClass() {
        intValue = 0;
        charValue = ' ';
        intArr = new int[10];
    }

    TestClass(int i, char c) {
        intValue = i;
        charValue = c;
    }

    virtual ~TestClass()
    {
        delete[] intArr;
    }

    TestClass(TestClass &other)
    {
        intValue = other.intValue;
        charValue = other.charValue;
        intArr = new int[10];
        for(int i = 0; i < 10; i++)
            intArr[i] = other.intArr[i];
    }
	friend std::ostream& operator<<(std::ostream& os, const TestClass& t)
	{
		os << "intValue: " << t.intValue << "; charValue: " << t.charValue << std::endl;
		return os;
	}
	friend bool operator==(const TestClass &t1, const TestClass& t2)
	{
		return (t1.intValue == t2.intValue && t1.charValue == t2.charValue);
	}
	friend bool operator!=(const TestClass &t1, const TestClass& t2)
	{
		return (!(t1 == t2));
	}
};
#endif //FT_CONTAINERS_TESTCLASS_HPP
