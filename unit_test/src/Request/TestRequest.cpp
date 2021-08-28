#include "../../include/acutest.hpp"
#include "../../../src/Request/Request.hpp"
#include "../../../src/Exceptions/Exceptions.hpp"

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
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n";
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
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n";
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

void testParseSeveralRequest_1() {
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

void testParseSeveralRequest_2() {
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

void testParseSeveralRequest_3() {
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

void testParseSeveralRequest_4() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");

	req.resetRequest();
	req.addRequestChunk("POST /index.html HTTP/1.1\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
}

void testParseSeveralRequest_5() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:8000");

	req.resetRequest();
	req.addRequestChunk("POST /index.html HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
}

void testParseSeveralRequest_6() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:8000");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");

	req.resetRequest();
	req.addRequestChunk("POST /index.html HTTP/1.1\r\nHost: 127.0.0.1:5000\r\nContent-Type: text/plain\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
	TEST_CHECK(data.header["content-type"] == "text/plain");
}

void testParseSeveralRequest_7() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\nPOST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");
}

void testParseSeveralRequest_8() {
	Request 	req;
	std::string requestSrt = "POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
}

void testParseSeveralRequest_9() {
	Request 	req;
	std::string requestSrt = "POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345POST / HTTP/1.1\r\nContent-Type: text/html\r\nContent-length: 7\r\n\r\nHello!!";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/html");
	TEST_CHECK(data.header["content-length"] == "7");
	TEST_CHECK(data.body == "Hello!!");
}

void testParseSeveralRequest_10() {
	Request 	req;
	std::string requestSrt = "POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");
}

void testParseSeveralRequest_11() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\nPOST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");


	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	
	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");
}

void testParseSeveralRequest_12() {
	Request 	req;
	std::string requestSrt = "POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");


	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");
}

void testParseSeveralRequest_13() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\nPOST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");
}

void testParseSeveralRequest_14() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\nPOST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");
}

void testParseSeveralRequest_15() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\nPOST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");
}

void testParseSeveralRequest_16() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\nPOST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");
}

void testParseSeveralRequest_17() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\nGET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
}

void testParseSeveralRequest_18() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\nGET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
}

void testParseSeveralRequest_19() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\nPOST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");

	req.resetRequest();
	req.addRequestChunk("");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");
}

void testParseSeveralRequest_20() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");

	req.resetRequest();
	req.addRequestChunk("POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");
}

void testParseSeveralRequest_21() {
	Request 	req;
	std::string requestSrt = "POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");

	req.resetRequest();
	req.addRequestChunk("GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
}

void testParseSeveralRequest_22() {
	Request 	req;
	std::string requestSrt = "POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");

	req.resetRequest();
	req.addRequestChunk("POST / HTTP/1.1\r\nContent-Type: text/html\r\nContent-length: 7\r\n\r\nHello!!");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/html");
	TEST_CHECK(data.header["content-length"] == "7");
	TEST_CHECK(data.body == "Hello!!");
}

void testParseSeveralRequest_23() {
	Request 	req;
	std::string requestSrt = "POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");

	req.resetRequest();
	req.addRequestChunk("POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");
}

void testParseSeveralRequest_24() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");

	req.resetRequest();
	req.addRequestChunk("POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");
}

void testParseSeveralRequest_25() {
	Request 	req;
	std::string requestSrt = "POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");


	req.resetRequest();
	req.addRequestChunk("POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");
}

void testParseSeveralRequest_26() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");

	req.resetRequest();
	req.addRequestChunk("POST /index.html HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-length: 5\r\n\r\n12345");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "application/x-www-form-urlencoded");
	TEST_CHECK(data.header["content-length"] == "5");
	TEST_CHECK(data.body == "12345");
}

void testParseSeveralRequest_27() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");

	req.resetRequest();
	req.addRequestChunk("POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");
}

void testParseSeveralRequest_28() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");

	req.resetRequest();
	req.addRequestChunk("POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");
}

void testParseSeveralRequest_29() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");

	req.resetRequest();
	req.addRequestChunk("POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");
}

void testParseSeveralRequest_30() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------130962363752115593144698\r\ncontent-length: 291\r\n\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"key\"\r\n\r\nvalue\r\n----------------------------130962363752115593144698\r\nContent-Disposition: form-data; name=\"DEV\"; filename=\"example.txt\"\r\n\r\nTOOL\r\n----------------------------130962363752115593144698--\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "multipart/form-data; boundary=--------------------------130962363752115593144698");
	TEST_CHECK(data.header["content-length"] == "291");
	TEST_CHECK(data.body == "example.txt=TOOL ");

	req.resetRequest();
	req.addRequestChunk("GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
}

void testParseSeveralRequest_31() {
	Request 	req;
	std::string requestSrt = "POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");

	req.resetRequest();
	req.addRequestChunk("GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");
}

void testParseSeveralRequest_32() {
	Request 	req;
	std::string requestSrt = "GET / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["host"] == "127.0.0.1:5000");

	req.resetRequest();
	req.addRequestChunk("POST / HTTP/1.1\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\nF\r\nFrontend_Develo\r\n0\r\n\r\n");
	data = req.getData();

	TEST_CHECK(data.header["method"] == "post");
	TEST_CHECK(data.header["location"] == "/");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
	TEST_CHECK(data.header["content-type"] == "text/plain");
	TEST_CHECK(data.header["transfer-encoding"] == "chunked");
	TEST_CHECK(data.body == "Mozilla Frontend_Develo ");
}

void testNotAllowed_1() {
	Request 	req;
	std::string requestSrt = "GETA / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (NotAllowedException& e) {
		TEST_CHECK(true);
	}
}

void testNotAllowed_2() {
	Request 	req;
	std::string requestSrt = "PUTT / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (NotAllowedException& e) {
		TEST_CHECK(true);
	}
}

void testNotAllowed_3() {
	Request 	req;
	std::string requestSrt = "PPOST / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (NotAllowedException& e) {
		TEST_CHECK(true);
	}
}

void testNotAllowed_4() {
	Request 	req;
	std::string requestSrt = "DELETEE / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (NotAllowedException& e) {
		TEST_CHECK(true);
	}
}

void testNotAllowed_5() {
	Request 	req;
	std::string requestSrt = "GETTER        /          HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (NotAllowedException& e) {
		TEST_CHECK(true);
	}
}

void testNotAllowed_6() {
	Request 	req;
	std::string requestSrt = "ASD        /          HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (NotAllowedException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_1() {
	Request 	req;
	std::string requestSrt = " GET / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_2() {
	Request 	req;
	std::string requestSrt = "aas GET / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_3() {
	Request 	req;
	std::string requestSrt = "     aas GET / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_4() {
	Request 	req;
	std::string requestSrt = "      GET / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_5() {
	Request 	req;
	std::string requestSrt = "Asd / HTTP/1.1\r\nHost: 127.0.0.1:8000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_6() {
	Request 	req;
	std::string requestSrt = "aSD / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_7() {
	Request 	req;
	std::string requestSrt = "asd / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_8() {
	Request 	req;
	std::string requestSrt = "GET / HTTp/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_9() {
	Request 	req;
	std::string requestSrt = "GET / Http/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_10() {
	Request 	req;
	std::string requestSrt = "GET / HTtp/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_11() {
	Request 	req;
	std::string requestSrt = "  asd / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testBadRequest_12() {
	Request 	req;
	std::string requestSrt = "  ASD / HTTP/1.1\r\nHost: 127.0.0.1:5000\r\n\r\n";
	RequestData data;

	try {
		req.addRequestChunk(requestSrt);
		TEST_CHECK(false);
	} catch (BadRequestException& e) {
		TEST_CHECK(true);
	}
}

void testParsingUri_1() {
	Request 	req;
	std::string requestSrt = "GET / index.html HTTP/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/ index.html");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
}

void testParsingUri_2() {
	Request 	req;
	std::string requestSrt = "GET / pic/photo.jpg HTTP/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/ pic/photo.jpg");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
}

void testParsingUri_3() {
	Request 	req;
	std::string requestSrt = "GET /pic/ photo.jpg HTTP/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/pic/ photo.jpg");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
}

void testParsingUri_4() {
	Request 	req;
	std::string requestSrt = "GET / pic / photo.jpg HTTP/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/ pic / photo.jpg");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
}

void testParsingUri_5() {
	Request 	req;
	std::string requestSrt = "GET / http/1.1\r\n\r\n";
	RequestData data;

	req.addRequestChunk(requestSrt);
	data = req.getData();

	TEST_CHECK(data.header["method"] == "get");
	TEST_CHECK(data.header["location"] == "/ http/1.1");
	TEST_CHECK(data.header["protocol"] == "http/1.1");
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

	{ "парсинг двух одновременных пустых запросов", testParseSeveralRequest_1 },
	{ "парсинг двух одновременных запросов с одним параметром", testParseSeveralRequest_2 },
	{ "парсинг двух одновременных запросов с несколькими параметрами", testParseSeveralRequest_3 },

	{ "парсинг двух последовательных запросов с несколькими параметрами", testParseSeveralRequest_4 },
	{ "парсинг двух последовательных запросов с одним параметром", testParseSeveralRequest_5 },
	{ "парсинг двух последовательных запросов с несколькими параметрами", testParseSeveralRequest_6 },

	{ "парсинг двух одновременных запросов (GET -> POST(CL)) с несколькими параметрами и body", testParseSeveralRequest_7 },
	{ "парсинг двух одновременных запросов (POST(CL) -> GET) с несколькими параметрами и body", testParseSeveralRequest_8 },
	{ "парсинг двух одновременных запросов (POST(CL) -> POST(CL)) с несколькими параметрами и body", testParseSeveralRequest_9 },

	{ "парсинг двух одновременных запросов (POST(CL) -> POST(CNUNKED)) с несколькими параметрами и body", testParseSeveralRequest_10 },
	{ "парсинг двух одновременных запросов (POST(CNUNKED) -> POST(CL)) с несколькими параметрами и body", testParseSeveralRequest_11 },

	{ "парсинг двух одновременных запросов (POST(CL) -> POST(BOUNDARY)) с несколькими параметрами и body", testParseSeveralRequest_12 },
	{ "парсинг двух одновременных запросов (POST(BOUNDARY) -> POST(CL)) с несколькими параметрами и body", testParseSeveralRequest_13 },

	{ "парсинг двух одновременных запросов (POST(BOUNDARY) -> POST(CNUNKED)) с несколькими параметрами и body", testParseSeveralRequest_14 },
	{ "парсинг двух одновременных запросов (POST(CNUNKED) -> POST(BOUNDARY)) с несколькими параметрами и body", testParseSeveralRequest_15 },

	{ "парсинг двух одновременных запросов (POST(BOUNDARY) -> POST(GET)) с несколькими параметрами и body", testParseSeveralRequest_16 },
	{ "парсинг двух одновременных запросов (POST(GET) -> POST(BOUNDARY)) с несколькими параметрами и body", testParseSeveralRequest_17 },
	
	{ "парсинг двух одновременных запросов (POST(CNUNKED) -> POST(GET)) с несколькими параметрами и body", testParseSeveralRequest_18 },
	{ "парсинг двух одновременных запросов (POST(GET) -> POST(CNUNKED)) с несколькими параметрами и body", testParseSeveralRequest_19 },

	{ "парсинг двух последовательных запросов (GET -> POST(CL)) с несколькими параметрами и body", testParseSeveralRequest_20 },
	{ "парсинг двух последовательных запросов (POST(CL) -> GET) с несколькими параметрами и body", testParseSeveralRequest_21 },
	{ "парсинг двух последовательных запросов (POST(CL) -> POST(CL)) с несколькими параметрами и body", testParseSeveralRequest_22 },

	{ "парсинг двух последовательных запросов (POST(CL) -> POST(CNUNKED)) с несколькими параметрами и body", testParseSeveralRequest_23 },
	{ "парсинг двух последовательных запросов (POST(CNUNKED) -> POST(CL)) с несколькими параметрами и body", testParseSeveralRequest_24 },

	{ "парсинг двух последовательных запросов (POST(CL) -> POST(BOUNDARY)) с несколькими параметрами и body", testParseSeveralRequest_25 },
	{ "парсинг двух последовательных запросов (POST(BOUNDARY) -> POST(CL)) с несколькими параметрами и body", testParseSeveralRequest_26 },

	{ "парсинг двух последовательных запросов (POST(BOUNDARY) -> POST(CNUNKED)) с несколькими параметрами и body", testParseSeveralRequest_27 },
	{ "парсинг двух последовательных запросов (POST(CNUNKED) -> POST(BOUNDARY)) с несколькими параметрами и body", testParseSeveralRequest_28 },

	{ "парсинг двух последовательных запросов (POST(BOUNDARY) -> POST(GET)) с несколькими параметрами и body", testParseSeveralRequest_29 },
	{ "парсинг двух последовательных запросов (POST(GET) -> POST(BOUNDARY)) с несколькими параметрами и body", testParseSeveralRequest_30 },

	{ "парсинг двух последовательных запросов (POST(CNUNKED) -> POST(GET)) с несколькими параметрами и body", testParseSeveralRequest_31 },
	{ "парсинг двух последовательных запросов (POST(GET) -> POST(CNUNKED)) с несколькими параметрами и body", testParseSeveralRequest_32 },

	{ "парсинг Not Allowed с несуществующим методом №1", testNotAllowed_1 },
	{ "парсинг Not Allowed с несуществующим методом №2", testNotAllowed_2 },
	{ "парсинг Not Allowed с несуществующим методом №3", testNotAllowed_3 },
	{ "парсинг Not Allowed с несуществующим методом №4", testNotAllowed_4 },
	{ "парсинг Not Allowed с несуществующим методом №5", testNotAllowed_5 },
	{ "парсинг Not Allowed с несуществующим методом №6", testNotAllowed_6 },
	{ "парсинг Bad Request с невалидными символами перед методом №1", testBadRequest_1 },
	{ "парсинг Bad Request с невалидными символами перед методом №2", testBadRequest_2 },
	{ "парсинг Bad Request с невалидными символами перед методом №3", testBadRequest_3 },
	{ "парсинг Bad Request с невалидными символами перед методом №4", testBadRequest_4 },
	{ "парсинг Bad Request с невалидными значением на месте метода №1", testBadRequest_5 },
	{ "парсинг Bad Request с невалидными значением на месте метода №2", testBadRequest_6 },
	{ "парсинг Bad Request с невалидными значением на месте метода №3", testBadRequest_7 },
	{ "парсинг Bad Request с невалидными значением на месте метода №4", testBadRequest_11 },
	{ "парсинг Bad Request с невалидными значением на месте метода №5", testBadRequest_12 },
	{ "парсинг Bad Request с невалидными значением на месте протокола №1", testBadRequest_8 },
	{ "парсинг Bad Request с невалидными значением на месте протокола №2", testBadRequest_9 },
	{ "парсинг Bad Request с невалидными значением на месте протокола №3", testBadRequest_10 },
	{ "парсинг запроса с составным uri №1", testParsingUri_1 },
	{ "парсинг запроса с составным uri №2", testParsingUri_2 },
	{ "парсинг запроса с составным uri №3", testParsingUri_3 },
	{ "парсинг запроса с составным uri №4", testParsingUri_4 },
	{ "парсинг запроса с составным uri, если протокол в нижнем регистре №4", testParsingUri_5 },

	{ nullptr, nullptr }
};