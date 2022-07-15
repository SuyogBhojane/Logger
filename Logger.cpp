#include "Logger.h"
#include "ConfigReader.h"
#include <mutex>

Logger* Logger::m_pInstance = nullptr;
Logger::Logger(std::string fileName)
{
    configure();
    mStorage = StorageType::FILE;
    if (mStorage == StorageType::FILE)
    {
        mLogFileName.open(fileName);

        if (mLogFileName.fail())
        {
            throw std::iostream::failure("Cannot open file: " + fileName);
        }
    }
    else
    {
        cout << "Storage Type not implemented" << endl;
    }
}

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

void Logger::Write(std::string content)
{ 
    std::lock_guard<mutex> lock(mMutex);

    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char timestamp[26];
    ctime_s(timestamp, sizeof timestamp, &now);

    std::string timestampWithoutEndl(timestamp);
    timestampWithoutEndl = timestampWithoutEndl.substr(0, 24);

    mLogFileName << timestampWithoutEndl << ": " << content << std::endl;
}

Logger * Logger::getInstance(std::string fileName)
{
    if (!m_pInstance)
    {
        m_pInstance = new Logger(fileName);
    }
    return m_pInstance;
}
void Logger::configure()
{
    ConfigReader* config = ConfigReader::getInstance();

    config->parseFile();

    LogLevel logLevel;
    StorageType logType;

    string logLevel_str;
    string logType_str;

    // Configuring the log level
    if (config->getValue("log_level", logLevel_str))
    {
        if (logLevel_str == "INFO" || logLevel_str == "1")
            logLevel = LogLevel::INFO;

        else if (logLevel_str == "DEBUG" || logLevel_str == "2")
            logLevel = LogLevel::DEBUG;

        else if (logLevel_str == "WARN" || logLevel_str == "3")
            logLevel = LogLevel::WARN;

        else if (logLevel_str == "ERROR" || logLevel_str == "4")
            logLevel = LogLevel::ERROR;
        else
            logLevel = LogLevel::INFO;
    }

    else
        logLevel = LogLevel::INFO;


    // Configuring the log type
    if (config->getValue("log_type", logType_str))
    {
        if (logType_str == "CONSOLE" || logType_str == "1")
            logType = StorageType::CONSOLE;

        else if (logType_str == "FILE" || logType_str == "2")
            logType = StorageType::FILE;

        else
            logType = StorageType::FILE;
    }

    else
        logType = StorageType::FILE;

    // Setting the parameters
    mLevel = logLevel;
    mStorage= logType;

}