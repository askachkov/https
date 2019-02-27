/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "tasks.h"
#include <thread>
#include <string.h>
#include <iostream>

int main(int argc, char *argv[])
{
    std::thread t1(default_Task, processClient, PORT_NO);
    std::thread t2(default_Task, processClientSSL, PORT_SSL_NO);
    t1.join();
    t2.join();
    return 0;
}
