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
public:
    Logger(const Logger&) = delete;
    Logger& operator= (const Logger&) = delete;
    Logger(Logger&& other);
    Logger& operator=(Logger&& other);
    void configure();
    static Logger* getInstance(std::string fileName);

    ~Logger()
    {
        mLogFileName.close();
    }

    void Write(std::string content);
    void setStorage(StorageType storageType) { this->mStorage = storageType; }
    void setLogLevel(LogLevel level) { this->mLevel = level; }
    //void setLogFile(string filepath) { this->mLogFileName = filepath; }

private:
    static Logger* m_pInstance;
    Logger(std::string fileName);
    Logger() = default;
    ofstream mLogFileName;
    mutex mMutex;
    StorageType mStorage;
    LogLevel mLevel;
};