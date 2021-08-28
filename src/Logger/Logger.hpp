#ifndef LOGGER
# define LOGGER

# include <iostream>
# include <fstream>

class Logger {
	private:
		std::ofstream _file;

	public:
		Logger();
		~Logger();

		void	printMessage(const std::string& message);
};

#endif