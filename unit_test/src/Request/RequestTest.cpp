#include "../../../src/Request/Request.hpp"
#include "../../include/acutest.hpp"
#include <iostream>

void testParseContentLengthWithSingleBodyParam(void) {
	Request request;
	std::string req = "post / http/1.1\ncontent-type: application/x-www-form-urlencoded\ncache-control: no-cache\npostman-token: c19176f3-da79-40ba-9909-1f3f526f3047\nuser-agent: postmanruntime/7.3.0\naccept: */*\nhost: 127.0.0.1:8000\naccept-encoding: gzip, deflate\ncontent-length: 10\nconnection: keep-alive\r\n\r\nkey: value";

	request.addRequestChunk(req);
	TEST_CHECK(request.getReadingData().contentLenght == 10);
}

void testParseContentLengthWithSeveralBodyParam(void) {
	Request request;
	std::string req = "post / http/1.1\ncontent-type: application/x-www-form-urlencoded\ncache-control: no-cache\npostman-token: c19176f3-da79-40ba-9909-1f3f526f3047\nuser-agent: postmanruntime/7.3.0\naccept: */*\nhost: 127.0.0.1:8000\naccept-encoding: gzip, deflate\ncontent-length: 21\nconnection: keep-alive\r\n\r\nkey: value\nname: ilya";

	request.addRequestChunk(req);
	TEST_CHECK(request.getReadingData().contentLenght == 21);
}

void testParseContentLengthWithNoBodyParam(void) {
	Request request;
	std::string req = "post / http/1.1\ncontent-type: application/x-www-form-urlencoded\ncache-control: no-cache\npostman-token: c19176f3-da79-40ba-9909-1f3f526f3047\nuser-agent: postmanruntime/7.3.0\naccept: */*\nhost: 127.0.0.1:8000\naccept-encoding: gzip, deflate\ncontent-length: 0\nconnection: keep-alive\r\n\r\n";

	request.addRequestChunk(req);
	TEST_CHECK(request.getReadingData().contentLenght == 0);
}

TEST_LIST = {
		{"Test parsing 'Content-length: 10' with single body param", testParseContentLengthWithSingleBodyParam},
		{"Test parsing 'Content-length: 21' with several body param", testParseContentLengthWithSeveralBodyParam},
		{"Test parsing 'Content-length: 0' with no body param", testParseContentLengthWithNoBodyParam},

		{ nullptr, nullptr }
};