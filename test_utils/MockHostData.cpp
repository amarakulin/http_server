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


MockHostData::MockHostData(){}

MockHostData::~MockHostData(){}

HostData *MockHostData::createDefaultHostDataRootTestFiles(){
	std::vector<ErrorPage*> vectorErrorPage;
	std::vector<Location*> vectorLocation;
	HostData *hostData = new HostData ();
	ErrorPage *errorPage = new ErrorPage();
	Location *location = new Location();
	location->root = "/test_files";
	location->autoindex = false;
	location->cgi = nullptr;
	location->httpMethods = std::vector<std::string>();
	location->index.push_back("index.html");
	location->index.push_back("index.css");
	location->index.push_back("index.js");
	location->uploadEnable = false;
	location->uploadPath = "";
	location->way = "/should_get_root_from_host";

	errorPage->errorPagePath = "/www/404error.html";//TODO may be fix
	errorPage->errorNbr = 404;
	vectorErrorPage.push_back(errorPage);
	vectorLocation.push_back(location);

	hostData->ip = "127.0.0.1";
	hostData->host = "127.0.0.1";
	hostData->serverName = "localhost";
	hostData->port = 8000;
	hostData->root = "/test_files";
	hostData->errorPage = vectorErrorPage;
	hostData->clientMaxBodySize = "214"; //FIXME Change to size_t
	hostData->location = vectorLocation;
	return hostData;
}

HostData *MockHostData::createDefaultHostDataRoot(){
	HostData *hostData = createDefaultHostDataRootTestFiles();
	hostData->root = "/";
	hostData->location[0]->index.push_back("root_file.html");
	return hostData;
}

HostData *MockHostData::createDefaultHostDataNestedDir(){
	HostData *hostData = createDefaultHostDataRootTestFiles();
	hostData->root = "/";
	hostData->location[0]->root = "/test_files";
	hostData->location[0]->way = "/nestedDir";
	hostData->location[0]->index.push_back("testNestesdIndex.html");
	return hostData;
}

HostData *MockHostData::createDefaultHostDataForDelete(){
	HostData *hostData = createDefaultHostDataRootTestFiles();
	hostData->root = "/test_files/forResponseDelete";
	hostData->location[0]->index.push_back("text_3MB.txt");
	return hostData;
//	std::vector<ErrorPage*> vectorErrorPage;
//	std::vector<Location*> vectorLocation;
//	HostData *hostData = new HostData ();
//	ErrorPage *errorPage = new ErrorPage();
//	Location *location = new Location();
//	location->root = "/";
//	location->autoindex = false;
//	location->cgi = nullptr;
//	location->httpMethods = std::vector<std::string>();
//	location->index.push_back("index.html");
//	location->index.push_back("index.css");
//	location->index.push_back("index.js");
//	location->index.push_back("text_3MB.txt");
//	location->uploadEnable = false;
//	location->uploadPath = "";
//	location->way = "/should_work_";
//
//	errorPage->errorPagePath = "/www/404error.html";//TODO may be fix
//	errorPage->errorNbr = 404;
//	vectorErrorPage.push_back(errorPage);
//	vectorLocation.push_back(location);
//
//	hostData->ip = "127.0.0.1";
//	hostData->host = "127.0.0.1";
//	hostData->serverName = "localhost";
//	hostData->port = 8000;
//	hostData->root = "/test_files/forResponseDelete";
//	hostData->errorPage = vectorErrorPage;
//	hostData->clientMaxBodySize = "214"; //FIXME Change to size_t
//	hostData->location = vectorLocation;
//	return hostData;
}

