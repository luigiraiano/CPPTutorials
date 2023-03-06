#include <../include/CPPTutorials/TestSingleton.h>
#include <../include/CPPTutorials/Box.h>

typedef union
{
    uint32_t uint32;
    uint8_t uint8[sizeof(uint32_t)];
}uint32_u;

uint32_t invertEndianess(const uint32_t& x)
{
    uint32_t x_inv;
    // x = [a,b,c,d];

    uint32_u x_u, x_inv_u;

    x_u.uint32 = x;
    int k=sizeof(uint32_u)-1;
    for(int i=0; i<sizeof(uint32_u); i++)
    {
        x_inv_u.uint8[i] = x_u.uint8[k];
        k--;
    }
    x_inv = x_inv_u.uint32;

    std::cout << "Original: " << x << " - Inverted: " << x_inv << std::endl;

    return x_inv;
}

int main()
{
    TestSingleton::Ptr singleton;
    TestSingleton::Ptr singleton_2;

    Box b1(1,1,1);
    std::cout << "box use count: " << Box::getUseCounts() << std::endl;
    Box b2(1,1,1);
    std::cout << "box use count: " << Box::getUseCounts() << std::endl;
    Box b3;
    std::cout << "box use count: " << Box::getUseCounts() << std::endl;

    std::cout << "Singleton Example" << std::endl;

    singleton = TestSingleton::instance();
    singleton_2 = TestSingleton::instance();
    singleton->add();
    std::cout << "Counts: " << singleton->getCounts() << std::endl;

    singleton->add();
    std::cout << "Counts: " << singleton->getCounts() << std::endl;

    singleton->add();
    std::cout << "Counts: " << singleton->getCounts() << std::endl;

    singleton_2 = singleton;
    std::cout << "Counts: " << singleton_2->getCounts() << std::endl;


    // Add two boxes
    b3 = b1 + b2;
    std::cout << "Volume of the box sum: " << b3.getVolume() << std::endl;

    // Testing Invert Endianess
    uint32_t x_test=4278255360;
    uint32_t x_test_inv = invertEndianess(x_test);
    std::cout << "Endianess Inverted: " << x_test_inv << std::endl;

    return 0;
}
