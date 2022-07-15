#pragma once
#include<string>
#include<map>

class ConfigReader
{
private:
    std::map<std::string, std::string> m_ConfigSettingMap;
    static ConfigReader* m_pInstance;
    ConfigReader();
    ~ConfigReader();

public:
    static ConfigReader* getInstance();
    bool parseFile(std::string fileName = "config.txt");
    bool getValue(std::string tag, std::string& value);
    
};