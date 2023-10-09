#include <iostream>
#include <thread>
#include <semaphore>
std::counting_semaphore<5> sem(5);
void worker(int id)
{
    sem.acquire();
    std::cout << "Worker " << id << " acquired semaphore" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sem.release();
    std::cout << "Worker " << id << " released semaphore" << std::endl;
}
int main()
{
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    t1.join();
    t2.join();
    t3.join();
}