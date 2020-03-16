#pragma once

#include <boost\thread.hpp>
#include "UpdateHandler.h"

class StargazerApplication
{
public:
	StargazerApplication(UpdateHandler *updateHandler);
	~StargazerApplication();
	void start();
	UpdateHandler *updateHandler;
private:
	void startUpdateHandlerThread();
	boost::thread updateThreadHandle;
	void stopEngine();
};