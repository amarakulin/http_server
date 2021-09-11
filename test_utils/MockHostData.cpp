/* **************************************************************************** */
/*                                                                      .       */
/*   MockHostData.cpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 9/8/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#include "MockHostData.hpp"

HostData *MockHostData::createDefaultHostData(){
	std::vector<ErrorPage*> vectorErrorPage;
	std::vector<Location*> vectorLocation;
	HostData *hostData = new HostData ();
	ErrorPage *errorPage = new ErrorPage();
	Location *location = new Location();//TODO gonna fill

	errorPage->errorPagePath = "/www/404error.html";//TODO may be fix
	errorPage->errorNbr = 404;
	vectorErrorPage.push_back(errorPage);
	vectorLocation.push_back(location);

	hostData->ip = "127.0.0.1";
	hostData->serverName = "localhost";
	hostData->port = 8000;
	hostData->root = "/www/";
	hostData->errorPage = vectorErrorPage;
	hostData->clientMaxBodySize = 214; //FIXME Change to size_t
	hostData->location = vectorLocation;
	return hostData;
}

MockHostData::MockHostData()
{

}

MockHostData::~MockHostData()
{

}

HostData *MockHostData::createDefaultHostDataNotStatic()
{
	std::vector<ErrorPage*> vectorErrorPage;
	std::vector<Location*> vectorLocation;
	HostData *hostData = new HostData ();
	ErrorPage *errorPage = new ErrorPage();
	Location *location = new Location();//TODO gonna fill

	errorPage->errorPagePath = "/www/404error.html";//TODO may be fix
	errorPage->errorNbr = 404;
	vectorErrorPage.push_back(errorPage);
	vectorLocation.push_back(location);

	hostData->ip = "127.0.0.1";
	hostData->serverName = "localhost";
	hostData->port = 8000;
	hostData->root = "/www/";
	hostData->errorPage = vectorErrorPage;
	hostData->clientMaxBodySize = 214; //FIXME Change to size_t
	hostData->location = vectorLocation;
	return hostData;
}
