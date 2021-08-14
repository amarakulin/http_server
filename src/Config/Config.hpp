#ifndef CONFIG
# define CONFIG

# include <vector>
# include "Host.hpp"

class Host;

class Config {
	private:
		std::vector<Host> _hosts;
	
	public:
		Config();
		Config(const Config& other);
		~Config();

		void	setNewHost(const Host& host);
};

#endif