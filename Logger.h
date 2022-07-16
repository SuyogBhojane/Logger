#pragma once
#include<iostream>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

enum class LogLevel
{
    INFO,
    DEBUG,
    WARN,
    ERROR
};

enum class StorageType
{
    CONSOLE,
    FILE,
    DB,
};

class Logger
{
     Logger();
     void configure();
     void setStorage(string storageType);
     void setLogLevel(string level);
     void setLogFilePath(string filepath);
     static void initSingleLogger();
public:
    Logger(const Logger&) = delete;
    Logger& operator= (const Logger&) = delete;
    Logger(Logger&& other)= delete;
    Logger& operator=(Logger&& other) = delete;
    static Logger* getInstance();
    string logLevel_to_string(LogLevel t);


    ~Logger()
    {
        mLogFileName.close();
    }

    void Write(std::string content);
private:

    static std::once_flag initInstanceFlag;
    static Logger* m_pInstance;
    string mFilepath;
    ofstream mLogFileName;
    mutex mMutex;
    StorageType mStorage;
    LogLevel mLevel;
};