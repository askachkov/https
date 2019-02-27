/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "tasks.h"
#include <thread>
#include <zlib.h>
#include <string.h>
#include <iostream>

void printBuffer(char * buffer, int size)
{
    using namespace std;
    cout << "pr:" << endl;
    for ( int i = 0; i < size;  ){
        for ( int j = 0; j < 10 && i < size; j++, i++ ){
            cout << hex << (int)buffer[i];
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    std::thread t1(http_Task);
    std::thread t2(https_Task);
    t1.join();
    t2.join();


//    uLong size = 1024;
//    char buffer[size];
//    char * str1 = "qwertyuiop[]";
//    char * str2 = "asdfghjkl;'4";
//    char * str3 = "zxcvbnm,./34";

//    ::compress((Bytef*)buffer, &size, (Bytef*)str1, strlen(str1));
//    printBuffer(buffer, size);
//    ::compress((Bytef*)buffer, &size, (Bytef*)str2, strlen(str2));
//    printBuffer(buffer, size);
//    ::compress((Bytef*)buffer, &size, (Bytef*)str3, strlen(str3));
//    printBuffer(buffer, size);
    return 0;
}
