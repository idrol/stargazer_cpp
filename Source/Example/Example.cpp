#include "Example.h"
#include "ExampleLevel.h"
#include "../Engine/StargazerEngine.h"
#include "../Engine/StargazerApplication.h"
#include "../Engine/UpdateHandler.h"
#include <iostream>
#include <btBulletDynamicsCommon.h>
#include <stdio.h>  /* defines FILENAME_MAX */
#include <string>
#include <windows.h>

int main() {
	freopen("log.txt","w",stdout);

	StargazerEngine::getInstance().addLevel("exampleLevel", new ExampleLevel());
	StargazerEngine::getInstance().setDefaultLevel(StargazerEngine::getInstance().getLevel("exampleLevel"));
	new StargazerApplication(new UpdateHandler());
}