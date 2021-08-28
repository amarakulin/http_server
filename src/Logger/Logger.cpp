#include "Logger.hpp"

Logger::Logger() {
	_file.open("logs", std::ios::trunc);
}

Logger::~Logger() {
	_file.close();
}

void	Logger::printMessage(const std::string& message) {
	_file << message << std::endl;
}