/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "tasks.h"
#include <thread>

int main(int argc, char *argv[])
{
    std::thread t1(http_Task);
    std::thread t2(https_Task);
    t1.join();
    t2.join();
    return 0;
}
