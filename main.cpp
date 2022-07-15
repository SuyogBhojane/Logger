#include "Logger.h"


int main(int argc, char* argv[])
{

    Logger* logger1 = Logger::getInstance(R"(d:\Logfile.txt)");
    logger1->Write("Hello");
 
    return 0;
}