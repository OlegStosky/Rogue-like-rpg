#define _CRT_SECURE_NO_WARNINGS

#include "ConfigManager.h"

using namespace rapidjson;

ConfigManager& ConfigManager::getInstance()
{
	static ConfigManager instance;
	return instance;
}

ConfigManager::ConfigManager()
{
	try
	{
		init();
		readConfig();
	}
	catch (FileOpeningError &err)
	{
		std::cout << err.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (JsonParseError &err)
	{
		std::cout << err.what() << std::endl;
		char c;
		std::cin >> c;
		exit(EXIT_FAILURE);
	}
}

ConfigManager::~ConfigManager()
{
	if (_configFile != nullptr)
	{
		fclose(_configFile);
	}
}

void ConfigManager::init()
{
	_configFile = fopen(_fileName.c_str(), "r");
	if (!_configFile)
	{
		throw FileOpeningError();
	}
}

void ConfigManager::readConfig()
{
	char readBuffer[65536];
	FileReadStream is(_configFile, readBuffer, sizeof(readBuffer));
	ParseResult error = _config.ParseStream(is);
	if (!error)
	{

		throw JsonParseError(strcat(strcat(const_cast<char*>(GetParseError_En(error.Code())), " "),
			std::to_string(error.Offset()).c_str()));
	}
}

int ConfigManager::getIntegerValue(std::string field)
{
	try
	{
		Type type = _config[field.c_str()].GetType();
		if (type != kNumberType)
		{
			throw GetIntValueError(field);
		}
	}
	catch (GetIntValueError &err)
	{
		std::cout << err.what();
		char c;
		std::cin >> c;
		exit(EXIT_FAILURE);
	}

	return _config[field.c_str()].GetInt();
}

std::string ConfigManager::getStringValue(std::string field)
{
	try
	{
		Type type = _config[field.c_str()].GetType();
		if (type != kStringType)
		{
			throw GetStringValueError(field);
		}
	}
	catch (GetStringValueError &err)
	{
		std::cout << err.what();
		char c;
		std::cin >> c;
		exit(EXIT_FAILURE);
	}

	return _config[field.c_str()].GetString();
}

