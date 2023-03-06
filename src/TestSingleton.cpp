#include "../include/CPPTutorials/TestSingleton.h"

TestSingleton::TestSingleton()
{
    test_ = "Singleton Created!";

    counts_ = 0;

    std::cout << test_ << std::endl;
}

TestSingleton::~TestSingleton()
{
    test_ = "Singleton Destroyed";

    std::cout << test_ << std::endl;
}

TestSingleton::Ptr TestSingleton::instance()
{
    static TestSingleton::Ptr obj;

    obj.reset( new TestSingleton() );

    return obj;
}

void TestSingleton::add()
{
    counts_++;
}

int TestSingleton::getCounts()
{
    return counts_;
}

TestSingleton::Ptr TestSingleton::operator+(const TestSingleton::Ptr& obj) {
    TestSingleton::Ptr res = TestSingleton::instance();

    res->counts_ = this->counts_ + obj->counts_;
    return res;
}
