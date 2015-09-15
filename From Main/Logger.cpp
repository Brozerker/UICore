#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>

#include "Logger.h"


Logger* Logger::Singleton = NULL;

Logger* Logger::Instance()
{
	if (!Singleton)//only allow one instance to be generated
		Singleton = new Logger;
	return Singleton;
}

void Logger::Write(LPCWSTR line, bool bFatal)
{
	//start each line with system date/time
	time_t currentTime = time(0);
	char* buffer = "";
	strftime(buffer, 25, "%Y-%m-%d %H:%M:%S ", localtime(&currentTime));
	LogStream << buffer << line << std::endl;
	//write it to error window too, making it highly visible so it's easy to see against
	//all the other spam in that window
	OutputDebugString(L"*********************************************************");
	OutputDebugString(line);
	//if it's fatal, stop the program
	if (bFatal)
		PostQuitMessage(0);
}


