#ifndef TESTSINGLETON_H
#define TESTSINGLETON_H

#include "utils.h"

/*
 * A singleton is a design pattern approach (a common solution to a common problem)
 * used to solve the problems of: common operations, common properties. It's a solution
 * to allow a single instance to be multiple accessed.
 * It's implemented with a private constructor and a public method of instantiation
 * defined to as static which returns a pointer to the class itself.
 * */

class TestSingleton
{
public:
    typedef std::shared_ptr<TestSingleton> Ptr;

    TestSingleton::Ptr operator=(const TestSingleton::Ptr &);
    TestSingleton::Ptr operator++(int)
    {
        TestSingleton::Ptr res;

        res->counts_ = this->counts_ + 1;

        return res;
    }
    // Overload + operator to add two Box objects.
    TestSingleton::Ptr operator+(const TestSingleton::Ptr& obj);

    static Ptr instance();
    ~TestSingleton();

public:
    void add();
    int getCounts();

private:
    TestSingleton();
    TestSingleton(const TestSingleton &);

private:
    std::string test_{""};

    int counts_{0};
};

#endif // TESTSINGLETON_H
