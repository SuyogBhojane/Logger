#include "ConfigReader.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>


using namespace std;

ConfigReader::ConfigReader() {}
ConfigReader::~ConfigReader() {};

ConfigReader* ConfigReader::m_pInstance = nullptr;
once_flag ConfigReader::initSingleConfigFlag;

ConfigReader* ConfigReader::getInstance()
{
    call_once(initSingleConfigFlag, &ConfigReader::initSingleConfig);

    return m_pInstance;
}
void ConfigReader::initSingleConfig() {
    m_pInstance = new ConfigReader();
}

bool ConfigReader::getValue(string tag, string& value)
{
    map<string, string>::iterator it;
    it = m_ConfigSettingMap.find(tag);
    if (it != m_ConfigSettingMap.end())
    {
        value = it->second;
        return true;
    }
    return false;
}

bool ConfigReader::parseFile(string fileName)
{
    ifstream inputFile;
    inputFile.open(fileName);
    string delimeter = "=";
    int initPos = 0;

    if (!inputFile.is_open())
    {
        cout << "Unable to find defaultConfig file" << endl;
        return false;
    }

    string line;
    while (getline(inputFile, line))
    {

        unsigned int length = line.find(delimeter);
        string tag, value;

        if (length != string::npos)
        {
            tag = line.substr(initPos, length);
            value = line.substr(length + 1);
        }

        tag.erase(remove(tag.begin(), tag.end(), ' '), tag.end());
        value.erase(remove(value.begin(), value.end(), ' '), value.end());

        if (tag.empty() || value.empty())
            continue;

        map<string, string>::iterator itr = m_ConfigSettingMap.find(tag);
        if (itr != m_ConfigSettingMap.end())
        {
            m_ConfigSettingMap.erase(tag);
        }

        m_ConfigSettingMap.insert(pair<string, string>(tag, value));
    }
    return true;
}