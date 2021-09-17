#ifndef RESPONSE
# define RESPONSE

# include <iostream>
#include <HostTypes.hpp>
# include "Request.hpp"

# include "ResponseTypes.hpp"
# include "utils.hpp"


class Response {
private:
	static const	t_response_process _arrProcessHeaders[];

	std::string		createHeadHeader();
	std::string		createRedirectHeader(const std::string &uri, HostData *hostData);
	std::string		processHeader(const std::string &headerName, const std::string &headerValue, HostData *hostData);
	static std::string getContentTypeHeader(std::string accept, HostData *hostData);
	static std::string getContentLengthHeader(std::string uri, HostData *hostData);

	//TODO Put method


protected:
	size_t		_leftBytesToSend;
	std::string	_dataToSend;
	int			_state;
	int			_status;

	void createHead(RequestData &requestData, HostData *hostData);
	virtual void createBody(const std::string &uri, HostData *hostData);
	void			changeContentLength(size_t valueContentLength);

	static std::string getFilePathFromHostData(const std::string &uri, HostData *hostData);
	static Location *getLocationByUri(const std::string &uri, std::vector<Location*> locations);

public:
	Response();
	Response(const Response& other);
	Response(RequestData &requestData, HostData *hostData);
	Response& operator=(const Response &assign);
	virtual ~Response();

	bool					isDone();
	void					countSendedData(int byteSended);

/*
** Getters
*/
	virtual size_t			getLeftBytesToSend() const;
	const std::string		&getDataToSend() const;
	virtual int				getStatus() const;

	int getState() const;

/*
** Setters
*/
};

#endif