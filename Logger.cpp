#include "Logger.h"
#include "ConfigReader.h"
#include <mutex>

Logger* Logger::m_pInstance = nullptr;
once_flag Logger::initInstanceFlag;

Logger::Logger()
{
    configure();
    if (mStorage == StorageType::FILE)
    {
        mLogFileName.open(mFilepath);

        if (mLogFileName.fail())
        {
            throw std::iostream::failure("Cannot open file: " + mFilepath);
        }
    }
}
/*
Logger& Logger::operator=(Logger&& other)
{
    mLogFileName.close();
    mLogFileName = move(other.mLogFileName);
    return *this;
}

Logger::Logger(Logger&& other)
{
    mLogFileName.close();
    mLogFileName = move(other.mLogFileName);

}
*/
void Logger::Write(std::string content)
{ 
    lock_guard<mutex> lock(mMutex);

    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char timestamp[26];
    ctime_s(timestamp, sizeof timestamp, &now);

    string timestampWithoutEndl(timestamp);
    timestampWithoutEndl = timestampWithoutEndl.substr(0, 24);

    mLogFileName << timestampWithoutEndl << ": " << content << std::endl;
}

Logger* Logger::getInstance()
{
    call_once(initInstanceFlag, &Logger::initSingleLogger);

    return m_pInstance;
}
void Logger::initSingleLogger() {
    m_pInstance = new Logger();
}
void Logger::setStorage(string storageType)
{
    if (storageType == "CONSOLE")
        mStorage = StorageType::CONSOLE;
    else if (storageType == "FILE")
        mStorage = StorageType::FILE;
    else
        mStorage = StorageType::FILE;
}
void Logger::setLogLevel(string level)
{
    if (level == "INFO" )
        mLevel = LogLevel::INFO;
    else if (level == "DEBUG" )
        mLevel = LogLevel::DEBUG;
    else if (level == "WARN" )
        mLevel = LogLevel::WARN;
    else if (level == "ERROR" )
        mLevel = LogLevel::ERROR;
    else
        mLevel = LogLevel::INFO;
}
void Logger::setLogFilePath(string filepath)
{
    mFilepath = filepath;
}
void Logger::configure()
{
    ConfigReader* config = ConfigReader::getInstance();

    config->parseFile();

    string logLevel_str("INFO");
    string logType_str("FILE");
    string logFile_path("");

    config->getValue("logFile_path", logFile_path);
    setLogFilePath(logFile_path);

    config->getValue("log_level", logLevel_str);
    setLogLevel(logLevel_str);

    config->getValue("storage_type", logType_str);
    setStorage(logType_str);
}