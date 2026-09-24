#include "Logger.h"
#include "Exceptions.h"

Logger::Logger() : file(logName, std::ios::app)
{
	if (!file)
	{
		throw ip::FilterError("cannot open log file" + logName);
	}
}

void Logger::Start()
{
	startTime = std::chrono::steady_clock::now();
}

long long Logger::getElapsedTime() const
{
	auto endTime = std::chrono::steady_clock::now();

	return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
}

void Logger::writeLog(const std::string& filterName, const std::string& parameters, bool success, const std::string& errorMessage)
{
    file << "Filter: " << filterName << '\n';
    file << "Parameters: " << parameters << '\n';
    file << "Time: " << getElapsedTime() << " us\n";

    if (success)
    {
        file << "Result: success\n";
    }
    else
    {
        file << "Result: failure\n";
        file << "Error: " << errorMessage << '\n';
    }

    file << "--------------------\n";
}