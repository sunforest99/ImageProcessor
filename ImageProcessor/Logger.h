#pragma once

#include <string>
#include <chrono>
#include <fstream>

class Logger
{
private:
	std::string logName = "result.log";
	std::ofstream file;
	std::chrono::steady_clock::time_point startTime;
public:
	Logger();

	void Start();
	long long getElapsedTime() const;

	void writeLog(const std::string& filterName, const std::string& parameters, bool success, const std::string& errorMessage = "");
};

