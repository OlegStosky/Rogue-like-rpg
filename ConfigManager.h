#pragma once

#include <string>
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\error\error.h"
#include "rapidjson\error\en.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include "ParserExceptions.h"

class ConfigManager
{
public:
	static ConfigManager& getInstance();
	~ConfigManager();

	void init();
	void readConfig();

	int getIntegerValue(std::string field);
	std::string getStringValue(std::string field);
private:
	ConfigManager();

	std::string _fileName = "Config.json";
	FILE *_configFile = nullptr;
	rapidjson::Document _config;
};