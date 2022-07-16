#pragma once
#include<string>
#include<map>
#include <thread>
#include <mutex>

using namespace std;
class ConfigReader
{
private:
    map<string, string> m_ConfigSettingMap;
    static ConfigReader* m_pInstance;
    ConfigReader();
    ~ConfigReader();
    static void initSingleConfig();
    static once_flag initSingleConfigFlag;

public:
    static ConfigReader* getInstance();
    bool parseFile(string fileName = "config.txt");
    bool getValue(string tag, string& value);
    
};