#include "../../include/acutest.hpp"
#include "../../../src/Request/Request.hpp"

void testParseGetRequest_1() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
}

void testParseGetRequest_2() {
	Request 	req;
	std::string requestSrt = "GET /127.0.0.1 HTTP/1.1\r\nHost: 127.0.0.1:8000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/127.0.0.1");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:8000");
}

void testParseGetRequest_3() {
	Request 	req;
	std::string requestSrt = "GET /favicon.ico HTTP/1.1\r\nHost: 127.0.0.1:8000\r\nConnection: keep-alive\r\nPragma: no-cache\r\nCache-Control: no-cache\r\n\r\n";

	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/favicon.ico");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:8000");
	TEST_CHECK(data.header["connection"] == "keep-alive");
	TEST_CHECK(data.header["pragma"] == "no-cache");
	TEST_CHECK(data.header["cache-control"] == "no-cache");
}

void testParsePostRequest_1() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
}

void testParsePostRequest_2() {
	Request 	req;
	std::string requestSrt = "POST /127.0.0.1 HTTP/1.1\r\nContent-Length: 9\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nvalue=key ";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/127.0.0.1");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-length"] == "9");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.body == "value=key");
}

void testParsePostRequest_3() {
	Request 	req;
	std::string requestSrt = "POST /127.0.0.1 HTTP/1.1\r\nContent-Length: 9\r\n\r\nvalue=key ";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/127.0.0.1");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-length"] == "9");
	TEST_CHECK(data.body == "value=key");
}

void testParsePostRequest_4() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\0\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");
}

void testParsePostRequest_5() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");
}

void testParseSeveralGetRequest_1() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\n\r\nPOST /index.html HTTP/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
}

void testParseSeveralGetRequest_2() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\n\r\nPOST /index.html HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:8000");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
}

void testParseSeveralGetRequest_3() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nPOST /index.html HTTP/1.1\r\nHost: 127.0.0.1:5000\r\nContent-Type: text/plain\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:8000");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
	TEST_CHECK(data.header["content-type"] == "text/plain");
}


TEST_LIST = {
	{ "парсинг GET запроса без параметров", testParseGetRequest_1 },
	{ "парсинг GET запроса без с одним параметром", testParseGetRequest_2 },
	{ "парсинг GET запроса без с несколькими параметрами", testParseGetRequest_3 },
	{ "парсинг POST запроса без параметров", testParsePostRequest_1 },
	{ "парсинг POST запроса с одним параметром в body (CL + CT)", testParsePostRequest_2 },
	{ "парсинг POST запроса с одним параметром в body (без Content-Type)", testParsePostRequest_3 },
	{ "парсинг CHUNKED POST запрос", testParsePostRequest_4 },
	{ "парсинг BOUNDARY POST запрос", testParsePostRequest_5 },
	{ "парсинг двух одновременных пустых GET запросов", testParseSeveralGetRequest_1 },
	{ "парсинг двух одновременных GET запросов с одним параметром", testParseSeveralGetRequest_2 },
	{ "парсинг двух одновременных GET запросов с несколькими параметрами", testParseSeveralGetRequest_3 },

	{ nullptr, nullptr }
};