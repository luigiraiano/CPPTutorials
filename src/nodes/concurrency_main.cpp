#include "../include/CPPTutorials/utils.h"
#include <thread>
#include <chrono>
#include <mutex>

static std::mutex lock;
// add lock

void task2()
{
    if( lock.try_lock() )
    {
        std::cout << "Task 2" << std::endl;
        uint64_t count = 0;
        while (count < 20)
        {
            std::cout << "[Task 2] Count: " << count << std::endl;
            count ++;
            std::this_thread::sleep_for(std::chrono::milliseconds(500) );
        }

        std::cout << "Task 2 has finished its job" << std::endl;
        lock.unlock();
    }

}

void task3(const std::string& msg)
{
    if( lock.try_lock() )
    {
        std::cout << "Task 3" << std::endl;
        std::cout << msg << std::endl;
        lock.lock();
    }

}

int main(int argc, char** argv)
{

    std::cout << "/ --- Concurrency Tutorials --- /" << std::endl;
    std::cout << "Task 1" << std::endl;

    std::thread t2(&task2);
    std::thread t3(&task3, "Thread 3");

    uint64_t count = 0;
    while (count < 20)
    {
        std::cout << "[Task 1] Count: " << count << std::endl;
        count ++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000) );
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

    return 0;
}
