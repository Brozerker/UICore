#pragma once

#include <Windows.h>
#include <fstream>


//define shorter way or referring to the instance so others can use LOGGER->Write instead of
//Logger::Instance()->Write
#define LOGGER Logger::Instance()

//log errors on the account

//the log file
static const char* logFile = "LOG_FILE.txt";

//this can safely be a singleton class since it will never be altered 
class Logger
{
public:
	static Logger* Instance();
	//open and close file
	inline void open() { LogStream.open(logFile); }
	inline void close() { LogStream.close(); }
	//write line to log and debug window, will end program if fatal
	void Write(LPCWSTR line, bool bFatal = false);
private:
	static Logger* Singleton;
	//private constructor
	Logger() {}
	//copy and assignment private
	Logger(Logger const&) {}
	Logger& operator=(Logger const&) {}
	//stream for log file info
	std::ofstream LogStream;
};

