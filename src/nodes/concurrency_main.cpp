#include "../include/CPPTutorials/utils.h"
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

#define CORRECT_THREAD_MANAGEMENT
//#define REDUCE_THREAD_PRIORITY

static std::mutex lock_t_main;
static std::mutex lock_t_3;
static std::mutex _filling_lock;

static std::vector<int> _list;

static int _count_shared;

void task3(const std::string& msg)
{
    std::lock_guard<std::mutex> lock_guard(lock_t_3);

    std::cout << "Task 3" << std::endl;
    std::cout << msg << std::endl;
}

template<class T>
void fillVector(const T& val, const int& num_el)
{
    std::lock_guard<std::mutex> lg(_filling_lock);

    std::cout << "*/ --- Fill a list --- */" << std::endl;
    std::cout << "Current Size: " << _list.size() << std::endl;

    for (size_t i=0; i<num_el; i++)
    {
        _list.push_back(val);
    }

    std::cout << "List Filled - New Size: " << _list.size() << std::endl;

    std::cout << "Here you go the list:" << std::endl;
    for(size_t i=0; i<_list.size(); i++)
    {
        std::cout << "Element " << i << ": " << _list.at(i) << std::endl;
    }
    std::cout << std::endl;
}

void mainTask(uint64_t& x)
{
#ifdef REDUCE_THREAD_PRIORITY
    std::this_thread::yield();
#else
    std::lock_guard<std::mutex> lock_guard(lock_t_main);
#endif

    std::cout << "[Main Task] Count: " << x << std::endl;
    x ++;

    std::cout << "[Main Task] Shared Count: " << _count_shared << std::endl;
    _count_shared++;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000) );
}

void task2()
{
#ifdef CORRECT_THREAD_MANAGEMENT
    // In this way, this thread takes the control until its completion. Therefore,
    // _count_shared will be updated also by this topic, starting from the value that it assumed
    // when this thread started.

    std::lock_guard<std::mutex> lock_guard(lock_t_main);
    std::cout << "Task 2" << std::endl;
    uint64_t count = 0;
    while (count < 20)
    {
        std::cout << "[Task 2] Count: " << count << std::endl;
        count ++;

        std::cout << "[Task 2] Shared Count: " << _count_shared << std::endl;
        _count_shared++;

        std::this_thread::sleep_for(std::chrono::milliseconds(500) );
    }

    std::cout << "Task 2 has finished its job" << std::endl;

#else
    // In this way, this thread never runs because the main thread has higher priority
    // and when the try_lock is called, it returns false. Therefore, _count_shared will be
    // only updated by mainTask().

    if(lock_t_main.try_lock())
    {
        std::cout << "Task 2" << std::endl;
        uint64_t count = 0;
        while (count < 20)
        {
            std::cout << "[Task 2] Count: " << count << std::endl;
            count ++;

            std::cout << "[Task 2] Shared Count: " << _count_shared << std::endl;
            _count_shared++;

            std::this_thread::sleep_for(std::chrono::milliseconds(500) );
        }

        std::cout << "Task 2 has finished its job" << std::endl;
        lock_t_main.unlock();
    }
#endif

}

int main(int argc, char** argv)
{

    std::vector<int> list;

    _count_shared = 0;

    std::cout << "/ --- Concurrency Tutorials --- /" << std::endl;
    std::cout << "Task 1" << std::endl;

    std::thread t2(&task2);
    std::thread t3(&task3, "Thread 3");

    std::thread t_fill_1(&fillVector<int>, 10, 5);
    std::thread t_fill_2(&fillVector<int>, 3, 10);

    uint64_t count = 0;
    while (count < 20)
    {
        mainTask(count);
    }

    std::cout << "Task 1 has finished its job" << std::endl;

    // Prevent Shutdown
    if(t2.joinable())
    {
        t2.join();
        std::cout << "Thread " << t2.get_id() << " has finished." << std::endl;
    }

    if(t3.joinable() )
    {
        t3.join();
        std::cout << "Thread " << t3.get_id() << " has finished." << std::endl;
    }

    if(t_fill_1.joinable() )
    {
        t_fill_1.join();
        std::cout << "Thread " << t_fill_1.get_id() << " has finished." << std::endl;
    }

    if(t_fill_2.joinable() )
    {
        t_fill_2.join();
        std::cout << "Thread " << t_fill_2.get_id() << " has finished." << std::endl;
    }

    return 0;
}
