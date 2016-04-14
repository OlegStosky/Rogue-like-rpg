#pragma once

#pragma warning(disable:4996)

#include <iostream>
#include <string.h>
#include <exception>
#include <string>

class FileOpeningError : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Coudn`t open config file";
	}
};

class JsonParseError : public std::exception
{
public:
	JsonParseError(std::string message) : 
		_message(message)
		{
		}

	virtual const char* what() const throw()
	{
		return strcat("Json parse error : ", _message.c_str());
	}
private:
	std::string _message;
};

class GetIntValueError : public std::exception
{
public:
	GetIntValueError(std::string field) : 
		_field(field)
		{
		}

	virtual const char* what() const throw()
	{
		return strcat(strcat("Value of",_field.c_str()), "is not of integer type");
	}

private:
	std::string _field;
};

class GetStringValueError : public std::exception
{
public:
	GetStringValueError(std::string field) : 
		_field(field)
		{
		}

	virtual const char* what() const throw()
	{
		return strcat(strcat("Value of", _field.c_str()), "is not of string type");
	}

private:
	std::string _field;
};