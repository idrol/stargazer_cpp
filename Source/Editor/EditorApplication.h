#pragma once

#include <boost\thread.hpp>
#include "EditorUpdateHandler.h"

class EditorApplication {
public:
	EditorApplication(EditorUpdateHandler *updateHandler);
	void start();
	EditorUpdateHandler *updateHandler;

private:
	void startUpdateHandlerThread();
	boost::thread updateThreadHandle;
	void stopEngine();
};