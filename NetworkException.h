#ifndef NETWORK_EXCEPTION
#define NETWORK_EXCEPTION

#include <string>

class NetworkException {
 	private:
 		std::string error;
	public:
		NetworkException(int id);
		
};

#endif // NETWORK_EXCEPTION