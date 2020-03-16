#pragma once
#include <string>

class Message {
public:
	virtual ~Message() {};
	std::string id = "BaseMessage";
};