#include "Logger.h"
#include <thread>

void Function1()
{
    for (int i = 0; i < 100; i++)
    {
        Logger::getInstance()->Write(" From Function1 : " + to_string(i));
    }
}

void Function2()
{
    for (int i = 0; i < 100; i++)
    {
        Logger::getInstance()->Write(" From Function2 : "+ to_string(i));
    }
}

int main(int argc, char* argv[])
{
    Logger* logger = Logger::getInstance();
    logger->Write("Hello");

    thread t1(Function1);
    thread t2(Function2);

    t1.join();
    t2.join();

    return 0;
}